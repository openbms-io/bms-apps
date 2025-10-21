/**
 * BacnetMetadata interface matching ControllerPoint format.
 *
 * This format matches what bacpypes3 library produces after processing.
 * Ensures consistency between discovery (bacnet_config) and monitoring (controller_points).
 */
export interface BacnetMetadata {
  // Core BACnet properties
  objectIdentifier?: [string, number]
  objectName?: string
  presentValue?: number | string | boolean
  objectType?: string
  description?: string

  // Health monitoring (matching ControllerPoint)
  statusFlags?: number[] // [0, 0, 0, 0]
  eventState?: string
  outOfService?: boolean // boolean not 0/1
  reliability?: string

  // Value limits
  units?: string
  minPresValue?: number
  maxPresValue?: number
  highLimit?: number
  lowLimit?: number
  resolution?: number
  covIncrement?: number
  deadband?: number

  // Control properties (matching ControllerPoint - extracted values)
  priorityArray?: Array<number | null> // [0.0, null, 50.0, ...]
  relinquishDefault?: number | string

  // Notification configuration (matching ControllerPoint)
  timeDelay?: number
  timeDelayNormal?: number
  notifyType?: string
  notificationClass?: number
  limitEnable?: {
    lowLimitEnable: boolean
    highLimitEnable: boolean
  } | null

  // Event properties (matching ControllerPoint - extracted strings)
  eventEnable?: {
    toFault: boolean
    toNormal: boolean
    toOffnormal: boolean
  } | null
  ackedTransitions?: {
    toFault: boolean
    toNormal: boolean
    toOffnormal: boolean
  } | null
  eventTimeStamps?: Array<string | null> // ["2025-10-21T12:02:44", null, null]
  eventMessageTexts?: string[] | null
  eventMessageTextsConfig?: string[] | null

  // Algorithm control (matching ControllerPoint)
  eventDetectionEnable?: boolean // boolean not 0/1
  eventAlgorithmInhibitRef?: {
    objectIdentifier: string
    propertyIdentifier: string
    arrayIndex: number | null
  } | null
  eventAlgorithmInhibit?: boolean // boolean not 0/1
  reliabilityEvaluationInhibit?: boolean // boolean not 0/1

  // Binary/multistate specific
  activeText?: string
  inactiveText?: string
  numberOfStates?: number
  stateText?: string[]
}
