import { createControlSequenceNodeUI } from './control-sequence-node-ui'
import {
  REHEAT_ALL_INPUTS,
  REHEAT_ALL_OUTPUTS,
  REHEAT_REQUIRED_INPUTS,
  SequenceTypeMap,
} from '@/domains/control-sequence'

export const G36VavReheatNode = createControlSequenceNodeUI({
  sequenceType: SequenceTypeMap.VAV_REHEAT,
  badgeLabel: 'G36',
  defaultLabel: 'VAV Reheat',
  allInputs: REHEAT_ALL_INPUTS,
  allOutputs: REHEAT_ALL_OUTPUTS,
  requiredInputs: REHEAT_REQUIRED_INPUTS,
})
