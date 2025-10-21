import {
  BehaviorSubject,
  Observable,
  ReplaySubject,
  Subject,
  filter,
  map,
  shareReplay,
  throwError,
  EMPTY,
  of,
} from 'rxjs'
import { takeUntil, catchError } from 'rxjs/operators'
import {
  CommandNameEnum,
  type PointBulkPayload,
  type ControllerPoint,
} from 'mqtt-topics'
import {
  MqttBusCore,
  type ConnectionStatus,
  type SupervisorConfig,
} from './mqtt-bus-core'

export class MqttBusManager {
  private currentBus?: MqttBusCore

  // Creating subjects to proxy the streams from the current bus.
  // Allowing us to swap out the underlying bus without changing the exposed observables.
  private _connectionStatus$ = new BehaviorSubject<ConnectionStatus>(
    'unavailable'
  )
  private _heartbeat$ = new ReplaySubject<unknown>(1)
  private _pointBulk$ = new Subject<PointBulkPayload>()
  private stop$ = new Subject<void>()

  start({ config }: { config: SupervisorConfig }): void {
    this.stop$.next()
    this.stop$ = new Subject<void>()

    this.currentBus?.dispose()
    this.currentBus = new MqttBusCore(config)

    this.currentBus.connectionStatus$
      .pipe(
        catchError((err) => {
          console.error('ConnectionStatus stream error:', err)
          return of('error' as ConnectionStatus)
        }),
        takeUntil(this.stop$)
      )
      .subscribe((status) => this._connectionStatus$.next(status))

    this.currentBus.heartbeatStream$
      .pipe(
        catchError((err) => {
          console.error('Heartbeat stream error:', err)
          return EMPTY
        }),
        takeUntil(this.stop$)
      )
      .subscribe((hb) => this._heartbeat$.next(hb))

    this.currentBus.pointBulkStream$
      .pipe(
        catchError((err) => {
          console.error('PointBulk stream error:', err)
          return EMPTY
        }),
        takeUntil(this.stop$)
      )
      .subscribe((bulk) => this._pointBulk$.next(bulk))
  }

  stop(): void {
    this.stop$.next()
    this._connectionStatus$.next('unavailable')
    this.currentBus?.dispose()
    this.currentBus = undefined
  }

  get connectionStatus$(): Observable<ConnectionStatus> {
    return this._connectionStatus$.asObservable()
  }

  get heartbeatStream$(): Observable<unknown> {
    return this._heartbeat$.asObservable()
  }

  get pointBulkStream$(): Observable<PointBulkPayload> {
    return this._pointBulk$.asObservable()
  }

  streamForPoint(ids: {
    controllerId: string
    pointId: string
  }): Observable<ControllerPoint> {
    if (!ids.controllerId || !ids.pointId) {
      return throwError(
        () =>
          new Error(
            `Invalid point IDs: controllerId=${ids.controllerId}, pointId=${ids.pointId}`
          )
      )
    }

    return this._pointBulk$.pipe(
      map((bulk) => {
        const point = bulk.points?.find(
          (p) =>
            p.controllerId === ids.controllerId &&
            p.iotDevicePointId === ids.pointId
        )
        if (!point) {
          console.warn(
            `Point ${ids.pointId} not found in bulk message for controller ${ids.controllerId}`
          )
        }
        return point
      }),
      filter((point): point is ControllerPoint => !!point),
      shareReplay({ bufferSize: 1, refCount: true })
    )
  }

  request<T = unknown>(
    command: CommandNameEnum,
    payload: unknown,
    timeoutMs = 30000
  ): Observable<T> {
    if (!this.currentBus) {
      return throwError(() => new Error('MQTT unavailable'))
    }
    return this.currentBus.request<T>(command, payload, timeoutMs)
  }
}

let _busManager: MqttBusManager | undefined
export function getMqttBus(): MqttBusManager {
  if (!_busManager) _busManager = new MqttBusManager()
  return _busManager
}
