/**
 * Control Sequence Domain - Public Types
 *
 * Domain-specific types not from generated API client.
 * Add custom type extensions here as needed.
 *
 * @module control-sequence/types
 */

import type { Node } from '@xyflow/react'
import type {
  ReheatInputsDto,
  ReheatOutputsDto,
} from './api/generated/types.gen'
import type { G36VavReheatNodeData } from '@/types/node-data-types'

export type {
  ReheatParameters,
  ReheatInputsDto,
  ReheatOutputsDto,
  StepRequest,
  StepResponse,
  InstanceResponseWithCategoriesReheatParameters,
  DeleteInstanceResponse,
  ErrorResponse,
  TemperatureUnit,
  AirflowUnit,
  ParameterCategory,
} from './api/generated/types.gen'

export type { G36VavReheatNodeData } from '@/types/node-data-types'

export type G36VavReheatNode = Node<G36VavReheatNodeData, 'g36-vav-reheat'>

export const G36_VAV_REHEAT_NODE_TYPE = 'g36-vav-reheat' as const

export type G36VavReheatInputHandle = keyof ReheatInputsDto
export type G36VavReheatOutputHandle = keyof ReheatOutputsDto
