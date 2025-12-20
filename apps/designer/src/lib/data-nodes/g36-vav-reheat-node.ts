import { NodeType } from '@/types/infrastructure'
import {
  BaseControlSequenceNode,
  BaseControlSequenceMetadata,
  ControlSequenceHandles,
} from './base-control-sequence-node'
import {
  SequenceTypeMap,
  type ControlSequenceInputHandle,
  type ControlSequenceOutputHandle,
  type InputCategory,
  type OutputCategory,
} from '@/domains/control-sequence'
import {
  ALL_INPUTS,
  ALL_OUTPUTS,
  REQUIRED_INPUTS,
  type ReheatInputHandle,
  type ReheatOutputHandle,
} from '@/domains/control-sequence/terminal-units/reheat'
import {
  createInstance,
  stepInstance,
} from '@/domains/control-sequence/api/client'
import type {
  ReheatInputsDto,
  ReheatOutputsDto,
} from '@/domains/control-sequence/api/generated/types.gen'

const DEFAULT_VISIBLE_OUTPUTS: ReheatOutputHandle[] = [
  'damperPosition',
  'valvePosition',
  'airflowSetpoint',
]

export class G36VavReheatNode extends BaseControlSequenceNode {
  readonly type = NodeType.G36_VAV_REHEAT
  readonly sequenceType = SequenceTypeMap.VAV_REHEAT

  static async create(params: {
    instanceId?: string
    label: string
    visibleInputs?: ControlSequenceInputHandle[]
    visibleOutputs?: ControlSequenceOutputHandle[]
    id?: string
  }): Promise<G36VavReheatNode> {
    const instanceId = params.instanceId ?? crypto.randomUUID()
    const response = await createInstance({ instance_id: instanceId })

    const parameterControlledInputs = Object.values(
      response.parameterToRequiredInputs
    ).flat() as ControlSequenceInputHandle[]

    const handles: ControlSequenceHandles = {
      allInputs: ALL_INPUTS,
      allOutputs: ALL_OUTPUTS,
      requiredInputs: REQUIRED_INPUTS,
      visibleInputs: params.visibleInputs ?? [...REQUIRED_INPUTS],
      visibleOutputs: params.visibleOutputs ?? DEFAULT_VISIBLE_OUTPUTS,
      parameterControlledInputs,
      inputCategories: response.inputCategories as Record<
        InputCategory,
        ControlSequenceInputHandle[]
      >,
      outputCategories: response.outputCategories as Record<
        OutputCategory,
        ControlSequenceOutputHandle[]
      >,
    }

    const config: BaseControlSequenceMetadata = {
      instanceId,
      label: params.label,
      handles,
    }
    return new G36VavReheatNode(config, params.id)
  }

  protected async executeStepApi(
    inputs: Record<string, unknown>
  ): Promise<ReheatOutputsDto> {
    const response = await stepInstance(this.instanceId, {
      stepSize: this.stepSize,
      inputs: inputs as ReheatInputsDto,
    })
    return response.outputs
  }
}
