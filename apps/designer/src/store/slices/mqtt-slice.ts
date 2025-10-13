import { StateCreator } from 'zustand'
import { Subject, interval } from 'rxjs'
import { takeUntil } from 'rxjs/operators'
import { getMqttBus } from '@/lib/mqtt/mqtt-bus'
import { CommandNameEnum } from 'mqtt-topics'
import type { GetConfigPayload } from '@/lib/api/get-config-payload'

export interface HeartbeatPayload {
  cpu_usage_percent: number | null
  memory_usage_percent: number | null
  disk_usage_percent: number | null
  temperature_celsius: number | null
  uptime_seconds: number | null
  load_average: number | null
  monitoring_status: string | null
  mqtt_connection_status: string | null
  bacnet_connection_status: string | null
  bacnet_devices_connected: number | null
  bacnet_points_monitored: number | null
  timestamp: number
  organization_id: string
  site_id: string
  iot_device_id: string
}

export interface BrokerHealth {
  status: 'unknown' | 'healthy' | 'unhealthy'
  lastHeartbeat?: HeartbeatPayload
  lastHeartbeatTimestamp?: number
}

export interface MQTTSlice {
  connectionStatus: 'disconnected' | 'connecting' | 'connected' | 'error'
  brokerHealth: BrokerHealth
  lastError?: string
  startMqtt: ({
    organizationId,
    siteId,
    iotDeviceId,
  }: {
    organizationId: string
    siteId: string
    iotDeviceId: string
  }) => void
  stopMqtt: () => void
  sendCommand: ({
    command,
    payload,
  }: {
    command: CommandNameEnum
    payload: unknown
  }) => Promise<unknown>
}

export function buildConfigUploadPayload(payload: GetConfigPayload) {
  return {
    urlToUploadConfig: payload.urlToUploadConfig,
    jwtToken: payload.jwtToken,
    iotDeviceControllers: payload.iotDeviceControllers.map((controller) => ({
      id: controller.id,
      ipAddress: controller.ipAddress,
      port: controller.port,
      controllerDeviceId: controller.controllerDeviceId,
    })),
    bacnetReaders: payload.bacnetReaders.map((reader) => ({
      id: reader.id,
      ip_address: reader.ipAddress,
      port: reader.port,
      bacnet_device_id: reader.deviceId,
      subnet_mask: reader.subnetMask,
      bbmd_enabled: reader.bbmdEnabled,
      bbmd_server_ip: reader.bbmdServerIp,
      is_active: reader.isActive,
    })),
  }
}

function deriveHealthStatus(
  heartbeat: HeartbeatPayload
): 'healthy' | 'unhealthy' {
  if (heartbeat.mqtt_connection_status === 'error') return 'unhealthy'
  if (heartbeat.bacnet_connection_status === 'error') return 'unhealthy'
  return 'healthy'
}

export const createMQTTSlice: StateCreator<MQTTSlice> = (set, get) => {
  let mqttStop$: Subject<void> | undefined

  const internalStop = () => {
    getMqttBus().stop()
    if (mqttStop$) {
      mqttStop$.next()
      mqttStop$.complete()
      mqttStop$ = undefined
    }
    set({
      connectionStatus: 'disconnected',
      brokerHealth: { status: 'unknown' },
      lastError: undefined,
    })
  }

  return {
    connectionStatus: 'disconnected',
    brokerHealth: { status: 'unknown' },

    startMqtt: ({ organizationId, siteId, iotDeviceId }) => {
      internalStop()
      const bus = getMqttBus()
      bus.start({
        config: {
          organizationId,
          siteId,
          iotDeviceId,
        },
      })

      mqttStop$ = new Subject<void>()

      bus.connectionStatus$.pipe(takeUntil(mqttStop$)).subscribe((s) => {
        set({ connectionStatus: s })
      })

      bus.heartbeatStream$.pipe(takeUntil(mqttStop$)).subscribe({
        next: (hb) =>
          set({
            brokerHealth: {
              status: deriveHealthStatus(hb as HeartbeatPayload),
              lastHeartbeat: hb as HeartbeatPayload,
              lastHeartbeatTimestamp: Date.now(),
            },
          }),
        error: (e) =>
          set({
            brokerHealth: { ...get().brokerHealth, status: 'unhealthy' },
            lastError: String(e),
          }),
      })

      const HEARTBEAT_THRESHOLD_MS = 60_000
      interval(5_000)
        .pipe(takeUntil(mqttStop$))
        .subscribe(() => {
          const { brokerHealth } = get()
          console.log('heartbeat check', brokerHealth)

          if (!brokerHealth.lastHeartbeatTimestamp) return
          const silentFor = Date.now() - brokerHealth.lastHeartbeatTimestamp
          if (
            silentFor > HEARTBEAT_THRESHOLD_MS &&
            brokerHealth.status !== 'unhealthy'
          ) {
            set({ brokerHealth: { ...brokerHealth, status: 'unhealthy' } })
          } else if (
            silentFor <= HEARTBEAT_THRESHOLD_MS &&
            brokerHealth.status === 'unhealthy' &&
            brokerHealth.lastHeartbeat
          ) {
            const derivedStatus = deriveHealthStatus(brokerHealth.lastHeartbeat)
            if (derivedStatus !== brokerHealth.status) {
              set({ brokerHealth: { ...brokerHealth, status: derivedStatus } })
            }
          }
        })
    },

    stopMqtt: () => {
      internalStop()
    },

    sendCommand: async ({
      command,
      payload,
    }: {
      command: CommandNameEnum
      payload: unknown
    }) => {
      const bus = getMqttBus()
      console.log('Sending command', command, payload)
      const response = await bus.request(command, payload).toPromise()
      console.log('Command Response', command, response)
      return response
    },
  }
}
