export interface BacnetMetadata {
  // Core BACnet properties (camelCase from Python API)
  objectIdentifier?: [string, number]
  objectName?: string
  presentValue?: number | string | boolean
  objectType?: string
  description?: string
  statusFlags?: string // "[0, 0, 0, 0]" format
  units?: string

  // Analog properties
  minPresValue?: number
  maxPresValue?: number
  highLimit?: number
  lowLimit?: number
  resolution?: number
  covIncrement?: number
  deadband?: number

  // Priority and control
  priorityArray?: Array<{ type: string; value: number }>
  relinquishDefault?: number
  outOfService?: number // 0 or 1

  // Event and alarm properties
  eventState?: string
  reliability?: string
  timeDelay?: number
  timeDelayNormal?: number
  notifyType?: string
  notificationClass?: number
  limitEnable?: number[]
  eventEnable?: number[]
  eventAlgorithmInhibit?: number
  eventDetectionEnable?: number
  reliabilityEvaluationInhibit?: number
  ackedTransitions?: number[]
  eventTimeStamps?: Array<{ type: string; value: string }>
  eventMessageTexts?: string[]
  eventMessageTextsConfig?: string[]

  // Allow any additional properties from Python
  [key: string]: unknown
}
