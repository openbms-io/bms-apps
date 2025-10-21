import { BacnetObjectType } from './infrastructure'

// Define all possible property value types
export type PropertyValue = number | boolean | string | null
export type PresentValue = number | boolean | string

// All possible BACnet properties with their types
export interface BacnetProperties {
  presentValue?: PresentValue

  // Metadata properties
  objectIdentifier?: [string, number]
  objectName?: string
  objectType?: string

  // Individual status flag properties
  inAlarm?: boolean
  fault?: boolean
  overridden?: boolean
  outOfService?: boolean

  eventState?: string
  reliability?: string
  units?: string
  description?: string
  minPresValue?: number
  maxPresValue?: number
  resolution?: number
  covIncrement?: number
  timeDelay?: number
  timeDelayNormal?: number
  highLimit?: number
  lowLimit?: number
  deadband?: number
  priorityArray?: Array<number | null>
  relinquishDefault?: number | boolean | string

  // Binary BacnetType
  activeText?: string
  inactiveText?: string

  // Event/Alarm properties
  notifyType?: string
  notificationClass?: number
  limitEnable?: { lowLimitEnable: boolean; highLimitEnable: boolean } | null
  eventEnable?: {
    toFault: boolean
    toNormal: boolean
    toOffnormal: boolean
  } | null
  eventAlgorithmInhibit?: boolean
  eventDetectionEnable?: boolean
  reliabilityEvaluationInhibit?: boolean
  ackedTransitions?: {
    toFault: boolean
    toNormal: boolean
    toOffnormal: boolean
  } | null
  eventTimeStamps?: Array<string | null>
  eventMessageTexts?: string[] | null
  eventMessageTextsConfig?: string[] | null

  // Multistate-specific properties
  numberOfStates?: number
  stateText?: (string | null)[]
}

// Type-safe multistate check
const MULTISTATE_TYPES = new Set<BacnetObjectType>([
  'multi-state-input',
  'multi-state-output',
  'multi-state-value',
] as const)

export function isMultistateObjectType(objectType: BacnetObjectType): boolean {
  return MULTISTATE_TYPES.has(objectType)
}

// Property metadata interface
export interface PropertyMetadata {
  name: string
  readable: boolean
  writable: boolean
}

// Properties that are metadata/info (read-only, diagnostic)
const METADATA_INFO: Record<string, PropertyMetadata> = {
  objectIdentifier: {
    name: 'Object Identifier',
    readable: true,
    writable: false,
  },
  objectName: { name: 'Object Name', readable: true, writable: false },
  objectType: { name: 'Object Type', readable: true, writable: false },
}

// Event/alarm diagnostic properties (read-only)
const EVENT_ALARM_PROPERTIES: Record<string, PropertyMetadata> = {
  timeDelayNormal: {
    name: 'Time Delay Normal',
    readable: true,
    writable: false,
  },
  notifyType: { name: 'Notify Type', readable: true, writable: false },
  notificationClass: {
    name: 'Notification Class',
    readable: true,
    writable: false,
  },
  limitEnable: { name: 'Limit Enable', readable: true, writable: false },
  eventEnable: { name: 'Event Enable', readable: true, writable: false },
  eventAlgorithmInhibit: {
    name: 'Event Algorithm Inhibit',
    readable: true,
    writable: false,
  },
  eventDetectionEnable: {
    name: 'Event Detection Enable',
    readable: true,
    writable: false,
  },
  reliabilityEvaluationInhibit: {
    name: 'Reliability Evaluation Inhibit',
    readable: true,
    writable: false,
  },
  ackedTransitions: {
    name: 'Acked Transitions',
    readable: true,
    writable: false,
  },
  eventTimeStamps: {
    name: 'Event Time Stamps',
    readable: true,
    writable: false,
  },
  eventMessageTexts: {
    name: 'Event Message Texts',
    readable: true,
    writable: false,
  },
  eventMessageTextsConfig: {
    name: 'Event Message Texts Config',
    readable: true,
    writable: false,
  },
}

// Properties that are ALWAYS read-only regardless of object type
const ALWAYS_READONLY: Record<string, PropertyMetadata> = {
  inAlarm: { name: 'In Alarm', readable: true, writable: false },
  fault: { name: 'Fault', readable: true, writable: false },
  overridden: { name: 'Overridden', readable: true, writable: false },
  eventState: { name: 'Event State', readable: true, writable: false },
  reliability: { name: 'Reliability', readable: true, writable: false },
  units: { name: 'Units', readable: true, writable: false },
  description: { name: 'Description', readable: true, writable: false },
  resolution: { name: 'Resolution', readable: true, writable: false },
}

// Properties that are ALWAYS writable regardless of object type
const ALWAYS_WRITABLE: Record<string, PropertyMetadata> = {
  outOfService: { name: 'Out of Service', readable: true, writable: true },
  covIncrement: { name: 'COV Increment', readable: true, writable: true },
  timeDelay: { name: 'Time Delay', readable: true, writable: true },
  deadband: { name: 'Deadband', readable: true, writable: true },
}

// Properties that are display-only (no handles, just status display)
const DISPLAY_ONLY: Record<string, PropertyMetadata> = {
  priorityArray: { name: 'Priority Array', readable: false, writable: false },
}

// Properties specific to analog objects only
const ANALOG_ONLY: Record<string, PropertyMetadata> = {
  minPresValue: { name: 'Min Present Value', readable: true, writable: true },
  maxPresValue: { name: 'Max Present Value', readable: true, writable: true },
  highLimit: { name: 'High Limit', readable: true, writable: true },
  lowLimit: { name: 'Low Limit', readable: true, writable: true },
}

// Properties specific to multistate objects only
const MULTISTATE_PROPERTIES: Record<string, PropertyMetadata> = {
  numberOfStates: { name: 'Number of States', readable: true, writable: false },
  stateText: { name: 'State Text', readable: true, writable: false },
}

// Object-type-specific metadata for special cases
const OBJECT_TYPE_METADATA: Record<
  BacnetObjectType,
  Record<string, PropertyMetadata>
> = {
  'analog-input': {
    presentValue: { name: 'Present Value', readable: true, writable: false },
    ...ANALOG_ONLY,
  },
  'analog-output': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
    ...ANALOG_ONLY,
  },
  'analog-value': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
    ...ANALOG_ONLY,
  },
  'binary-input': {
    presentValue: { name: 'Present Value', readable: true, writable: false },
  },
  'binary-output': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
  },
  'binary-value': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
  },
  'multi-state-input': {
    presentValue: { name: 'Present Value', readable: true, writable: false },

    ...MULTISTATE_PROPERTIES,
  },
  'multi-state-output': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
    ...MULTISTATE_PROPERTIES,
  },
  'multi-state-value': {
    presentValue: { name: 'Present Value', readable: true, writable: true },
    relinquishDefault: {
      name: 'Relinquish Default',
      readable: true,
      writable: true,
    },
    ...MULTISTATE_PROPERTIES,
  },
}

// Simple function - no string checks, just lookups
export function getPropertyMetadata(
  objectType: BacnetObjectType,
  propertyName: keyof BacnetProperties
): PropertyMetadata | undefined {
  const propName = propertyName as string

  // Check display-only first (no handles)
  if (DISPLAY_ONLY[propName]) {
    return DISPLAY_ONLY[propName]
  }

  // Check object-type-specific
  if (OBJECT_TYPE_METADATA[objectType]?.[propName]) {
    return OBJECT_TYPE_METADATA[objectType][propName]
  }

  // Check metadata/info properties
  if (METADATA_INFO[propName]) {
    return METADATA_INFO[propName]
  }

  // Check event/alarm properties
  if (EVENT_ALARM_PROPERTIES[propName]) {
    return EVENT_ALARM_PROPERTIES[propName]
  }

  // Then check always-readonly
  if (ALWAYS_READONLY[propName]) {
    return ALWAYS_READONLY[propName]
  }

  // Then check always-writable
  if (ALWAYS_WRITABLE[propName]) {
    return ALWAYS_WRITABLE[propName]
  }

  // Property not supported for this object type
  return undefined
}
