/**
 * G36 VAV Reheat Node Type Tests
 *
 * Tests cover acceptance criteria from Story 1B.1:
 *   AC1: g36-vav-reheat node type added to Designer node registry
 *   AC2: Node data uses generated types from @/domains/control-sequence
 *   AC5: Node type registration tests pass
 */

import { nodeTypes } from '@/components/nodes'
import { NodeType, NodeCategory } from '@/types/infrastructure'
import type { G36VavReheatNodeData } from '@/types/node-data-types'
import type { ControlSequenceNodeData } from '@/types/node-data-types'
import { G36_VAV_REHEAT_NODE_TYPE } from './types'
import {
  REHEAT_ALL_INPUTS,
  REHEAT_ALL_OUTPUTS,
  REHEAT_REQUIRED_INPUTS,
  type InputCategory,
  type OutputCategory,
  type ControlSequenceInputHandle,
  type ControlSequenceOutputHandle,
} from './index'

const mockInputCategories: Record<InputCategory, ControlSequenceInputHandle[]> =
  {
    zoneTemperature: ['zoneTemperature', 'coolingSetpoint', 'heatingSetpoint'],
    zoneAirQuality: ['co2Concentration', 'co2Setpoint'],
    zoneSensors: ['occupancyStatus', 'windowStatus'],
    vavTerminal: ['dischargeAirTemperature', 'primaryAirflow'],
    ahu: ['supplyAirTemperature', 'supplyAirTemperatureSetpoint', 'fanStatus'],
    plant: ['hotWaterPlantStatus'],
    control: [
      'operationMode',
      'heatingOff',
      'overrideDamperPosition',
      'overrideFlowSetpoint',
    ],
  }

const mockOutputCategories: Record<
  OutputCategory,
  ControlSequenceOutputHandle[]
> = {
  vavControl: ['damperPosition', 'valvePosition', 'airflowSetpoint'],
  ahuRequests: [
    'heatingValveRequest',
    'zonePressureRequest',
    'zoneTempRequest',
  ],
  plantRequests: ['hotWaterPlantRequest'],
  alarms: [
    'flowSensorAlarm',
    'leakingDamperAlarm',
    'leakingValveAlarm',
    'lowFlowAlarm',
    'lowTempAlarm',
  ],
  ventilationInfo: [
    'minOutdoorAirflow',
    'adjAreaBreathingZoneFlow',
    'adjPopBreathingZoneFlow',
  ],
}

describe('G36 VAV Reheat Node Type Registration', () => {
  const nodeTypeKey = `${NodeCategory.CONTROL_SEQUENCE}.${NodeType.G36_VAV_REHEAT}`

  describe('node type registry (AC: #1)', () => {
    it('g36-vav-reheat is registered in nodeTypes', () => {
      expect(nodeTypeKey in nodeTypes).toBe(true)
      expect(nodeTypes[nodeTypeKey]).toBeDefined()
    })

    it('NodeType enum contains G36_VAV_REHEAT', () => {
      expect(NodeType.G36_VAV_REHEAT).toBe('g36-vav-reheat')
    })

    it('NodeCategory enum contains CONTROL_SEQUENCE', () => {
      expect(NodeCategory.CONTROL_SEQUENCE).toBe('control-sequence')
    })

    it('G36_VAV_REHEAT_NODE_TYPE constant matches NodeType enum', () => {
      expect(G36_VAV_REHEAT_NODE_TYPE).toBe(NodeType.G36_VAV_REHEAT)
    })
  })

  describe('node data type compatibility (AC: #2)', () => {
    it('G36VavReheatNodeData has required type field', () => {
      const nodeData: G36VavReheatNodeData = {
        label: 'Test VAV Reheat',
        category: NodeCategory.CONTROL_SEQUENCE,
        type: NodeType.G36_VAV_REHEAT,
        sequenceType: 'terminal-reheat',
        metadata: {
          instanceId: 'test-instance-id',
          label: 'Test VAV Reheat',
          handles: {
            allInputs: REHEAT_ALL_INPUTS,
            allOutputs: REHEAT_ALL_OUTPUTS,
            requiredInputs: REHEAT_REQUIRED_INPUTS,
            visibleInputs: [...REHEAT_REQUIRED_INPUTS],
            visibleOutputs: [
              'damperPosition',
              'valvePosition',
              'airflowSetpoint',
            ],
            parameterControlledInputs: [],
            inputCategories: mockInputCategories,
            outputCategories: mockOutputCategories,
          },
        },
        handles: {
          allInputs: REHEAT_ALL_INPUTS,
          allOutputs: REHEAT_ALL_OUTPUTS,
          requiredInputs: REHEAT_REQUIRED_INPUTS,
          visibleInputs: [...REHEAT_REQUIRED_INPUTS],
          visibleOutputs: [
            'damperPosition',
            'valvePosition',
            'airflowSetpoint',
          ],
          parameterControlledInputs: [],
          inputCategories: mockInputCategories,
          outputCategories: mockOutputCategories,
        },
      }

      expect(nodeData.type).toBe(NodeType.G36_VAV_REHEAT)
      expect(nodeData.category).toBe(NodeCategory.CONTROL_SEQUENCE)
    })

    it('G36VavReheatNodeData extends ControlSequenceNodeData', () => {
      const baseData: ControlSequenceNodeData = {
        label: 'Test',
        category: NodeCategory.CONTROL_SEQUENCE,
        sequenceType: 'terminal-reheat',
        metadata: {
          instanceId: 'test-id',
          label: 'Test',
          handles: {
            allInputs: REHEAT_ALL_INPUTS,
            allOutputs: REHEAT_ALL_OUTPUTS,
            requiredInputs: REHEAT_REQUIRED_INPUTS,
            visibleInputs: [...REHEAT_REQUIRED_INPUTS],
            visibleOutputs: ['damperPosition'],
            parameterControlledInputs: [],
            inputCategories: mockInputCategories,
            outputCategories: mockOutputCategories,
          },
        },
        handles: {
          allInputs: REHEAT_ALL_INPUTS,
          allOutputs: REHEAT_ALL_OUTPUTS,
          requiredInputs: REHEAT_REQUIRED_INPUTS,
          visibleInputs: [...REHEAT_REQUIRED_INPUTS],
          visibleOutputs: ['damperPosition'],
          parameterControlledInputs: [],
          inputCategories: mockInputCategories,
          outputCategories: mockOutputCategories,
        },
      }

      expect(baseData.category).toBe(NodeCategory.CONTROL_SEQUENCE)
      expect(baseData.sequenceType).toBe('terminal-reheat')
    })

    it('node data requires instanceId in metadata', () => {
      const nodeData: G36VavReheatNodeData = {
        label: 'Test',
        category: NodeCategory.CONTROL_SEQUENCE,
        type: NodeType.G36_VAV_REHEAT,
        sequenceType: 'terminal-reheat',
        metadata: {
          instanceId: 'frontend-generated-uuid',
          label: 'Test',
          handles: {
            allInputs: REHEAT_ALL_INPUTS,
            allOutputs: REHEAT_ALL_OUTPUTS,
            requiredInputs: REHEAT_REQUIRED_INPUTS,
            visibleInputs: [...REHEAT_REQUIRED_INPUTS],
            visibleOutputs: ['damperPosition'],
            parameterControlledInputs: [],
            inputCategories: mockInputCategories,
            outputCategories: mockOutputCategories,
          },
        },
        handles: {
          allInputs: REHEAT_ALL_INPUTS,
          allOutputs: REHEAT_ALL_OUTPUTS,
          requiredInputs: REHEAT_REQUIRED_INPUTS,
          visibleInputs: [...REHEAT_REQUIRED_INPUTS],
          visibleOutputs: ['damperPosition'],
          parameterControlledInputs: [],
          inputCategories: mockInputCategories,
          outputCategories: mockOutputCategories,
        },
      }

      expect(nodeData.metadata.instanceId).toBe('frontend-generated-uuid')
    })
  })

  describe('handle definitions match generated types (AC: #3, #4)', () => {
    it('REHEAT_ALL_INPUTS has 17 total inputs (unit preferences moved to ReheatParameters)', () => {
      expect(REHEAT_ALL_INPUTS.length).toBe(17)
    })

    it('REHEAT_REQUIRED_INPUTS has 9 required inputs', () => {
      expect(REHEAT_REQUIRED_INPUTS.length).toBe(9)
    })

    it('REHEAT_ALL_OUTPUTS has 15 outputs', () => {
      expect(REHEAT_ALL_OUTPUTS.length).toBe(15)
    })

    it('required inputs include core temperature and airflow inputs', () => {
      expect(REHEAT_REQUIRED_INPUTS).toContain('zoneTemperature')
      expect(REHEAT_REQUIRED_INPUTS).toContain('coolingSetpoint')
      expect(REHEAT_REQUIRED_INPUTS).toContain('heatingSetpoint')
      expect(REHEAT_REQUIRED_INPUTS).toContain('primaryAirflow')
      expect(REHEAT_REQUIRED_INPUTS).toContain('fanStatus')
      expect(REHEAT_REQUIRED_INPUTS).toContain('operationMode')
    })

    it('outputs include damper, valve, and airflow setpoint', () => {
      expect(REHEAT_ALL_OUTPUTS).toContain('damperPosition')
      expect(REHEAT_ALL_OUTPUTS).toContain('valvePosition')
      expect(REHEAT_ALL_OUTPUTS).toContain('airflowSetpoint')
    })
  })
})
