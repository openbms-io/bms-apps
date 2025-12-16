/**
 * Control Sequence Domain - Public API
 *
 * This is the ONLY file external modules should import from.
 * All implementation details (api, generated) are internal.
 *
 * @module control-sequence
 */

export type {
  ReheatParameters,
  ReheatInputsDto,
  ReheatOutputsDto,
  StepRequest,
  StepResponse,
  CreateInstanceRequestReheatParameters,
  InstanceResponseWithCategoriesReheatParameters,
  DeleteInstanceResponse,
  ErrorResponse,
  HealthResponse,
  ValidationRequest,
  ValidationResponse,
  TemperatureUnit,
  AirflowUnit,
  ParameterCategory,
  InputCategory,
  OutputCategory,
  ReheatInputName,
  ReheatOutputName,
} from './api/generated/types.gen'

export type {
  G36VavReheatNodeData,
  G36VavReheatNode,
  G36VavReheatInputHandle,
  G36VavReheatOutputHandle,
} from './types'

export { G36_VAV_REHEAT_NODE_TYPE } from './types'

export {
  REQUIRED_INPUTS as REHEAT_REQUIRED_INPUTS,
  OPTIONAL_INPUTS as REHEAT_OPTIONAL_INPUTS,
  ALL_INPUTS as REHEAT_ALL_INPUTS,
  ALL_OUTPUTS as REHEAT_ALL_OUTPUTS,
  REHEAT_ENUM_FIELDS,
  type ReheatInputHandle,
  type ReheatOutputHandle,
} from './terminal-units/reheat'

export {
  SequenceTypeMap,
  SEQUENCE_DROPDOWN_FIELDS,
  type SequenceType,
  type SequenceHandleConfig,
  type ControlSequenceInputHandle,
  type ControlSequenceOutputHandle,
  type ControlSequenceHandleConfig,
  type DropdownFieldsMap,
} from './sequence-types'
