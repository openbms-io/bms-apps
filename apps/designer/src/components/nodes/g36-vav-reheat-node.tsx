import { createControlSequenceNodeUI } from './control-sequence-node-ui'
import { SequenceTypeMap } from '@/domains/control-sequence'

export const G36VavReheatNode = createControlSequenceNodeUI({
  sequenceType: SequenceTypeMap.VAV_REHEAT,
})
