'use client'

import { useState, useEffect } from 'react'
import {
  CheckCircle,
  XCircle,
  AlertCircle,
  Edit,
  Save,
  X,
  Activity,
  Wifi,
  WifiOff,
  Clock,
  Plus,
  Settings,
} from 'lucide-react'
import { cn } from '@/lib/utils'
import { useProject, useUpdateProject } from '@/hooks/use-projects'
import {
  useIotDevice,
  useCreateIotDeviceForProject,
} from '@/hooks/use-iot-device'
import { useFlowStore } from '@/store/use-flow-store'
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card'
import { Badge } from '@/components/ui/badge'
import { Button } from '@/components/ui/button'
import { useBacnetReaders } from '@/hooks/use-bacnet-readers'
import { BacnetReadersModal } from '@/components/modals/bacnet-readers-modal'

interface SupervisorsTabProps {
  orgId: string
  siteId: string
  projectId: string
}

export function SupervisorsTab({
  orgId,
  siteId,
  projectId,
}: SupervisorsTabProps) {
  const { data: project, isLoading: isLoadingProject } = useProject({
    orgId,
    siteId,
    projectId,
  })
  const { data: iotDevice, isLoading: isLoadingDevice } = useIotDevice(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId ?? undefined
  )
  const updateProjectMutation = useUpdateProject()
  const createIotDeviceMutation = useCreateIotDeviceForProject()

  const [isCreating, setIsCreating] = useState(false)
  const [formName, setFormName] = useState('')
  const [formDescription, setFormDescription] = useState('')
  const [readersModalOpen, setReadersModalOpen] = useState(false)

  const { data: readers } = useBacnetReaders(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId
  )

  const isLoading = isLoadingProject || isLoadingDevice

  const connectionStatus = useFlowStore((s) => s.connectionStatus)
  const brokerHealth = useFlowStore((s) => s.brokerHealth)
  const lastError = useFlowStore((s) => s.lastError)

  const hasConfig = !!iotDevice
  const readersCount = readers?.length ?? 0

  const handleCreate = async () => {
    if (!formName.trim()) return

    await createIotDeviceMutation.mutateAsync({
      orgId,
      siteId,
      projectId,
      name: formName.trim(),
      description: formDescription.trim() || undefined,
    })

    setIsCreating(false)
    setFormName('')
    setFormDescription('')
  }

  const handleCancel = () => {
    setIsCreating(false)
    setFormName('')
    setFormDescription('')
  }

  const getStatus = () => {
    if (isLoading) return 'loading'
    if (!hasConfig) return 'not-configured'
    return 'configured'
  }

  const getStatusIcon = (status: string) => {
    switch (status) {
      case 'configured':
        return <CheckCircle className="w-4 h-4 text-green-500" />
      case 'not-configured':
        return <XCircle className="w-4 h-4 text-red-500" />
      default:
        return <AlertCircle className="w-4 h-4 text-gray-400" />
    }
  }

  const getStatusColor = (status: string) => {
    switch (status) {
      case 'configured':
        return 'text-green-600 bg-green-50 border-green-200'
      case 'not-configured':
        return 'text-red-600 bg-red-50 border-red-200'
      default:
        return 'text-gray-600 bg-gray-50 border-gray-200'
    }
  }

  const getConnectionStatusColor = () => {
    switch (connectionStatus) {
      case 'connected':
        return 'bg-green-500'
      case 'connecting':
        return 'bg-yellow-500'
      case 'error':
        return 'bg-red-500'
      default:
        return 'bg-gray-400'
    }
  }

  const getBrokerHealthIcon = () => {
    if (brokerHealth.status === 'healthy') {
      return <Activity className="w-4 h-4 text-green-500" />
    }
    return <Activity className="w-4 h-4 text-red-500" />
  }

  const formatUptime = (ms: number) => {
    const seconds = Math.floor(ms / 1000)
    const minutes = Math.floor(seconds / 60)
    const hours = Math.floor(minutes / 60)
    const days = Math.floor(hours / 24)

    if (days > 0) return `${days}d ${hours % 24}h`
    if (hours > 0) return `${hours}h ${minutes % 60}m`
    if (minutes > 0) return `${minutes}m ${seconds % 60}s`
    return `${seconds}s`
  }

  const formatTimestamp = (ts: number) => {
    const date = new Date(ts * 1000)
    return date.toLocaleTimeString()
  }

  const status = getStatus()

  if (isLoading) {
    return (
      <div className="h-full flex flex-col">
        <div className="p-3 border-b">
          <h3 className="text-sm font-medium">Supervisors</h3>
        </div>
        <div className="flex-1 flex items-center justify-center">
          <div className="text-sm text-muted-foreground">Loading...</div>
        </div>
      </div>
    )
  }

  return (
    <div className="h-full flex flex-col">
      {/* Header */}
      <div className="p-3 border-b">
        <div className="flex items-center justify-between">
          <h3 className="text-sm font-medium">Supervisors</h3>
          {!hasConfig && !isCreating && (
            <button
              onClick={() => setIsCreating(true)}
              className="p-1 rounded hover:bg-muted transition-colors"
              title="Add supervisor"
            >
              <Plus className="w-4 h-4" />
            </button>
          )}
        </div>
      </div>

      {/* Configuration Display */}
      <div className="flex-1 p-3">
        {isCreating ? (
          <div className="space-y-4">
            <div className="p-3 border rounded-lg bg-card">
              <h4 className="text-sm font-medium mb-3">Create Supervisor</h4>

              <div className="space-y-3">
                <div>
                  <label className="text-xs font-medium text-muted-foreground">
                    Name *
                  </label>
                  <input
                    type="text"
                    value={formName}
                    onChange={(e) => setFormName(e.target.value)}
                    className="w-full px-2 py-1 text-sm border rounded mt-1"
                    placeholder="Enter supervisor name"
                    autoFocus
                  />
                </div>

                <div>
                  <label className="text-xs font-medium text-muted-foreground">
                    Description
                  </label>
                  <textarea
                    value={formDescription}
                    onChange={(e) => setFormDescription(e.target.value)}
                    className="w-full px-2 py-1 text-sm border rounded mt-1"
                    placeholder="Enter description (optional)"
                    rows={3}
                  />
                </div>

                <div className="flex gap-2 pt-2">
                  <button
                    onClick={handleCreate}
                    disabled={
                      !formName.trim() || createIotDeviceMutation.isPending
                    }
                    className="flex-1 px-3 py-1.5 text-xs font-medium bg-primary text-primary-foreground rounded hover:bg-primary/90 disabled:opacity-50 disabled:cursor-not-allowed"
                  >
                    {createIotDeviceMutation.isPending
                      ? 'Creating...'
                      : 'Create'}
                  </button>
                  <button
                    onClick={handleCancel}
                    disabled={createIotDeviceMutation.isPending}
                    className="flex-1 px-3 py-1.5 text-xs font-medium border rounded hover:bg-muted disabled:opacity-50 disabled:cursor-not-allowed"
                  >
                    Cancel
                  </button>
                </div>

                {createIotDeviceMutation.isError && (
                  <div className="text-xs text-red-600">
                    {createIotDeviceMutation.error.message}
                  </div>
                )}
              </div>
            </div>
          </div>
        ) : !hasConfig ? (
          <div className="space-y-4">
            <div className="text-center py-8">
              <AlertCircle className="w-12 h-12 text-muted-foreground mx-auto mb-4" />
              <h4 className="text-sm font-medium mb-2">No IoT Device Linked</h4>
              <p className="text-xs text-muted-foreground mb-4">
                Link an IoT device to this project to enable MQTT communication.
              </p>
            </div>
          </div>
        ) : (
          <div className="space-y-4">
            <div className="p-3 border rounded-lg bg-card">
              <div className="flex items-start justify-between mb-2">
                <div className="flex items-center gap-2">
                  {getStatusIcon(status)}
                  <div>
                    <div className="text-sm font-medium">
                      Supervisor Configured
                    </div>
                    <div className="text-xs text-muted-foreground">
                      Ready for MQTT communication
                    </div>
                  </div>
                </div>
              </div>

              <div className="space-y-2 mt-3">
                <div>
                  <span className="text-xs font-medium text-muted-foreground">
                    Device Name:
                  </span>
                  <span className="text-xs ml-2">{iotDevice.name}</span>
                </div>
                {iotDevice.description && (
                  <div>
                    <span className="text-xs font-medium text-muted-foreground">
                      Description:
                    </span>
                    <span className="text-xs ml-2">
                      {iotDevice.description}
                    </span>
                  </div>
                )}
                <div>
                  <span className="text-xs font-medium text-muted-foreground">
                    Organization:
                  </span>
                  <span className="text-xs ml-2">{iotDevice.siteId}</span>
                </div>
                <div>
                  <span className="text-xs font-medium text-muted-foreground">
                    Site:
                  </span>
                  <span className="text-xs ml-2">{iotDevice.siteId}</span>
                </div>
                <div>
                  <span className="text-xs font-medium text-muted-foreground">
                    Device ID:
                  </span>
                  <span className="text-xs ml-2">{iotDevice.id}</span>
                </div>
              </div>

              <div className="flex items-center justify-between mt-3">
                <span
                  className={cn(
                    'px-2 py-1 text-xs rounded-full border',
                    getStatusColor(status)
                  )}
                >
                  {status === 'configured' ? 'Configured' : 'Not Configured'}
                </span>
              </div>
            </div>

            {/* BACnet Readers Configuration */}
            {hasConfig && (
              <div className="p-3 border rounded-lg bg-card">
                <div className="flex items-center justify-between mb-2">
                  <div className="flex items-center gap-2">
                    <Settings className="w-4 h-4" />
                    <div>
                      <div className="text-sm font-medium">
                        BACnet Reader Network Interface
                      </div>
                      <div className="text-xs text-muted-foreground">
                        Configure Ethernet/WiFi interface settings
                      </div>
                    </div>
                  </div>
                  <Badge variant="secondary">{readersCount}</Badge>
                </div>

                <div className="mt-3">
                  <Button
                    size="sm"
                    variant="outline"
                    onClick={() => setReadersModalOpen(true)}
                    className="w-full"
                  >
                    <Settings className="w-4 h-4 mr-2" />
                    Configure Interfaces
                  </Button>
                </div>
              </div>
            )}

            {/* MQTT Connection Status */}
            {hasConfig && (
              <Card className="mt-3">
                <CardHeader className="p-3 pb-2">
                  <div className="flex items-center gap-2">
                    {connectionStatus === 'connected' ? (
                      <Wifi className="w-4 h-4 text-green-500" />
                    ) : (
                      <WifiOff className="w-4 h-4 text-gray-400" />
                    )}
                    <CardTitle className="text-sm">MQTT Connection</CardTitle>
                    <div
                      className={cn(
                        'w-2 h-2 rounded-full ml-auto',
                        getConnectionStatusColor()
                      )}
                    />
                  </div>
                </CardHeader>

                <CardContent className="p-3 pt-0 space-y-2">
                  <div className="flex items-center justify-between">
                    <span className="text-xs text-muted-foreground">
                      Status:
                    </span>
                    <Badge variant="outline" className="capitalize text-xs">
                      {connectionStatus}
                    </Badge>
                  </div>

                  {connectionStatus === 'connected' && (
                    <>
                      <div className="flex items-center justify-between">
                        <span className="text-xs text-muted-foreground">
                          Broker Health:
                        </span>
                        <div className="flex items-center gap-1">
                          {getBrokerHealthIcon()}
                          <Badge
                            variant={
                              brokerHealth.status === 'healthy'
                                ? 'default'
                                : 'destructive'
                            }
                            className="capitalize text-xs"
                          >
                            {brokerHealth.status}
                          </Badge>
                        </div>
                      </div>

                      {brokerHealth.lastHeartbeat ? (
                        <>
                          {brokerHealth.lastHeartbeat.uptime_seconds !==
                            null && (
                            <div className="flex items-center justify-between">
                              <span className="text-xs text-muted-foreground">
                                Uptime:
                              </span>
                              <span className="text-xs">
                                {formatUptime(
                                  brokerHealth.lastHeartbeat.uptime_seconds *
                                    1000
                                )}
                              </span>
                            </div>
                          )}

                          {brokerHealth.lastHeartbeat.monitoring_status && (
                            <div className="flex items-center justify-between">
                              <span className="text-xs text-muted-foreground">
                                Status:
                              </span>
                              <Badge
                                variant="secondary"
                                className="text-xs capitalize"
                              >
                                {brokerHealth.lastHeartbeat.monitoring_status}
                              </Badge>
                            </div>
                          )}

                          <div className="flex items-center justify-between">
                            <span className="text-xs text-muted-foreground">
                              Last Heartbeat:
                            </span>
                            <div className="flex items-center gap-1">
                              <Clock className="w-3 h-3" />
                              <span className="text-xs">
                                {formatTimestamp(
                                  brokerHealth.lastHeartbeat.timestamp
                                )}
                              </span>
                            </div>
                          </div>
                        </>
                      ) : (
                        <div className="pt-2 pb-2 text-center">
                          <div className="flex items-center justify-center gap-2 text-muted-foreground">
                            <Clock className="w-4 h-4 animate-pulse" />
                            <span className="text-xs">
                              Waiting for heartbeat from supervisor...
                            </span>
                          </div>
                          <p className="text-xs text-muted-foreground mt-2">
                            Check that BMS IoT App is running with matching
                            configuration
                          </p>
                        </div>
                      )}
                    </>
                  )}

                  {lastError && (
                    <div className="pt-2 border-t">
                      <div className="flex items-start gap-1">
                        <AlertCircle className="w-3 h-3 text-red-500 mt-0.5" />
                        <div className="flex-1">
                          <div className="text-xs font-medium text-red-600">
                            Error
                          </div>
                          <div className="text-xs text-muted-foreground break-words">
                            {lastError}
                          </div>
                        </div>
                      </div>
                    </div>
                  )}
                </CardContent>
              </Card>
            )}
          </div>
        )}
      </div>

      {/* Footer Info */}
      <div className="p-3 border-t bg-muted/30">
        <div className="text-xs text-muted-foreground">
          Supervisors manage IoT controllers and execute visual programming
          flows via MQTT.
        </div>
      </div>

      {/* BACnet Readers Modal */}
      {iotDevice && (
        <BacnetReadersModal
          open={readersModalOpen}
          onOpenChange={setReadersModalOpen}
          orgId={orgId}
          siteId={siteId}
          projectId={projectId}
          iotDeviceId={iotDevice.id}
        />
      )}
    </div>
  )
}
