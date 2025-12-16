/**
 * Control Sequence Type Definitions
 *
 * Defines the discriminated union for all G36 control sequence types.
 * Each sequence type maps to specific input/output handle types.
 */

import type {
  ReheatInputHandle,
  ReheatOutputHandle,
} from './terminal-units/reheat'
import {
  REHEAT_ENUM_FIELDS,
  type DropdownOption,
} from './terminal-units/reheat'

export type { SequenceType } from './api/generated/types.gen'
import type { SequenceType } from './api/generated/types.gen'

// SequenceType is generated as a type alias (not an enum), so we create a
// const object for accessing values like SequenceTypeMap.VAV_REHEAT
export const SequenceTypeMap = {
  VAV_REHEAT: 'vav-reheat',
  AHU: 'ahu',
} as const satisfies Record<string, SequenceType>

export type ControlSequenceInputHandle = ReheatInputHandle

export type ControlSequenceOutputHandle = ReheatOutputHandle

export interface SequenceHandleConfig<
  TInput extends ControlSequenceInputHandle = ControlSequenceInputHandle,
  TOutput extends ControlSequenceOutputHandle = ControlSequenceOutputHandle,
> {
  sequenceType: SequenceType
  allInputs: readonly TInput[]
  allOutputs: readonly TOutput[]
  requiredInputs: readonly TInput[]
  defaultVisibleInputs: readonly TInput[]
  defaultVisibleOutputs: readonly TOutput[]
}

export type ControlSequenceHandleConfig = SequenceHandleConfig

export type DropdownFieldsMap = Record<
  string,
  readonly DropdownOption<number | boolean>[]
>

export const SEQUENCE_DROPDOWN_FIELDS: Partial<
  Record<SequenceType, DropdownFieldsMap>
> = {
  [SequenceTypeMap.VAV_REHEAT]: REHEAT_ENUM_FIELDS,
}
