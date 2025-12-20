import { G36VavReheatNode } from './g36-vav-reheat-node'
import { serializeNodeData, deserializeNodeData } from '@/lib/node-serializer'
import factory from './factory'
import { NodeType, NodeCategory, ComputeValue } from '@/types/infrastructure'
import {
  SequenceTypeMap,
  type ControlSequenceInputHandle,
  type ControlSequenceOutputHandle,
} from '@/domains/control-sequence'
import {
  ALL_INPUTS,
  ALL_OUTPUTS,
  REQUIRED_INPUTS,
} from '@/domains/control-sequence/terminal-units/reheat'
import * as client from '@/domains/control-sequence/api/client'
import { Message, SendCallback } from '@/lib/message-system/types'

jest.mock('@/domains/control-sequence/api/client', () => ({
  createInstance: jest.fn(),
  deleteInstance: jest.fn(),
  stepInstance: jest.fn(),
}))

const mockCreateInstance = client.createInstance as jest.Mock
const mockStepInstance = client.stepInstance as jest.Mock

const mockCreateInstanceResponse = {
  instanceId: 'mock-instance',
  parameters: {},
  categories: {},
  parameterToRequiredInputs: {
    hasCO2Sensor: ['co2Concentration', 'co2Setpoint'],
    hasHotWaterCoil: ['hotWaterPlantStatus'],
    hasOccupancySensor: ['occupancyStatus'],
    hasWindowSensor: ['windowStatus'],
  },
}

describe('G36VavReheatNode', () => {
  beforeEach(() => {
    jest.clearAllMocks()
    mockCreateInstance.mockResolvedValue(mockCreateInstanceResponse)
  })

  describe('static create', () => {
    it('creates node with default handles', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Test VAV Reheat',
        id: 'test-id',
      })

      expect(node.id).toBe('test-id')
      expect(node.label).toBe('Test VAV Reheat')
      expect(node.type).toBe(NodeType.G36_VAV_REHEAT)
      expect(node.category).toBe(NodeCategory.CONTROL_SEQUENCE)
      expect(node.sequenceType).toBe(SequenceTypeMap.VAV_REHEAT)
      expect(client.createInstance).toHaveBeenCalled()
    })

    it('creates node with provided instanceId', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'custom-instance-id',
        label: 'Custom Instance',
        id: 'node-id',
      })

      expect(node.instanceId).toBe('custom-instance-id')
      expect(client.createInstance).toHaveBeenCalledWith({
        instance_id: 'custom-instance-id',
      })
    })

    it('creates node with custom visible handles', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Custom Handles',
        visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
        visibleOutputs: ['damperPosition'],
        id: 'node-id',
      })

      expect(node.handles.visibleInputs).toEqual([
        'zoneTemperature',
        'coolingSetpoint',
      ])
      expect(node.handles.visibleOutputs).toEqual(['damperPosition'])
    })

    it('uses default visible inputs from REQUIRED_INPUTS', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Default Inputs',
        id: 'node-id',
      })

      expect(node.handles.visibleInputs).toEqual([...REQUIRED_INPUTS])
    })

    it('always includes allInputs and allOutputs from constants', async () => {
      const node = await G36VavReheatNode.create({
        label: 'All Handles',
        id: 'node-id',
      })

      expect(node.handles.allInputs).toEqual(ALL_INPUTS)
      expect(node.handles.allOutputs).toEqual(ALL_OUTPUTS)
      expect(node.handles.requiredInputs).toEqual(REQUIRED_INPUTS)
    })
  })

  describe('serialization', () => {
    it('serializes to correct format', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'test-instance-id',
        label: 'Serializable Node',
        visibleInputs: ['zoneTemperature'],
        visibleOutputs: ['damperPosition'],
        id: 'serialize-test-id',
      })

      const serialized = node.toSerializable()

      expect(serialized).toEqual({
        id: 'serialize-test-id',
        type: NodeType.G36_VAV_REHEAT,
        category: NodeCategory.CONTROL_SEQUENCE,
        label: 'Serializable Node',
        metadata: {
          instanceId: 'test-instance-id',
          visibleInputs: ['zoneTemperature'],
          visibleOutputs: ['damperPosition'],
        },
      })
    })

    it('serializes via serializeNodeData', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'instance-123',
        label: 'Test Node',
        visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
        visibleOutputs: ['damperPosition', 'valvePosition'],
        id: 'node-123',
      })

      const result = serializeNodeData(node)

      expect(result.nodeType).toBe(NodeType.G36_VAV_REHEAT)
      expect(result.serializedData.id).toBe('node-123')
      expect(result.serializedData.metadata).toEqual({
        instanceId: 'instance-123',
        visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
        visibleOutputs: ['damperPosition', 'valvePosition'],
      })
    })
  })

  describe('factory creation', () => {
    it('creates via factory', async () => {
      const node = await factory.createG36VavReheatNode({
        instanceId: 'factory-instance',
        label: 'Factory Node',
        visibleInputs: ['zoneTemperature'],
        visibleOutputs: ['damperPosition'],
        id: 'factory-id',
      })

      expect(node.id).toBe('factory-id')
      expect(node.label).toBe('Factory Node')
      expect(node.instanceId).toBe('factory-instance')
    })
  })

  describe('deserialization', () => {
    it('deserializes correctly via nodeFactory', async () => {
      const serializedData = {
        id: 'deserialized-node',
        type: NodeType.G36_VAV_REHEAT,
        category: NodeCategory.CONTROL_SEQUENCE,
        label: 'Restored Node',
        metadata: {
          instanceId: 'restored-instance',
          visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
          visibleOutputs: ['damperPosition'],
        },
      }

      const nodeFactory = async (
        nodeType: string,
        data: Record<string, unknown>
      ) => {
        if (nodeType === NodeType.G36_VAV_REHEAT) {
          const metadata = data.metadata as {
            instanceId: string
            visibleInputs: ControlSequenceInputHandle[]
            visibleOutputs: ControlSequenceOutputHandle[]
          }
          return factory.createG36VavReheatNode({
            instanceId: metadata.instanceId,
            label: data.label as string,
            visibleInputs: metadata.visibleInputs,
            visibleOutputs: metadata.visibleOutputs,
            id: data.id as string,
          })
        }
        throw new Error(`Unknown node type: ${nodeType}`)
      }

      const result = (await deserializeNodeData({
        nodeType: NodeType.G36_VAV_REHEAT,
        serializedData,
        nodeFactory,
      })) as G36VavReheatNode

      expect(result.id).toBe('deserialized-node')
      expect(result.label).toBe('Restored Node')
      expect(result.instanceId).toBe('restored-instance')
      expect(result.handles.visibleInputs).toEqual([
        'zoneTemperature',
        'coolingSetpoint',
      ])
      expect(result.handles.visibleOutputs).toEqual(['damperPosition'])
    })
  })

  describe('round-trip serialization', () => {
    it('preserves all properties through serialize/deserialize cycle', async () => {
      const original = await G36VavReheatNode.create({
        instanceId: 'round-trip-instance',
        label: 'Round Trip Node',
        visibleInputs: ['zoneTemperature', 'heatingSetpoint', 'primaryAirflow'],
        visibleOutputs: ['damperPosition', 'valvePosition'],
        id: 'round-trip-id',
      })

      const serialized = serializeNodeData(original)

      const nodeFactory = async (
        nodeType: string,
        data: Record<string, unknown>
      ) => {
        if (nodeType === NodeType.G36_VAV_REHEAT) {
          const metadata = data.metadata as {
            instanceId: string
            visibleInputs: ControlSequenceInputHandle[]
            visibleOutputs: ControlSequenceOutputHandle[]
          }
          return factory.createG36VavReheatNode({
            instanceId: metadata.instanceId,
            label: data.label as string,
            visibleInputs: metadata.visibleInputs,
            visibleOutputs: metadata.visibleOutputs,
            id: data.id as string,
          })
        }
        throw new Error(`Unknown node type: ${nodeType}`)
      }

      const restored = (await deserializeNodeData({
        nodeType: serialized.nodeType as NodeType,
        serializedData: serialized.serializedData,
        nodeFactory,
      })) as G36VavReheatNode

      expect(restored.id).toBe(original.id)
      expect(restored.type).toBe(original.type)
      expect(restored.label).toBe(original.label)
      expect(restored.category).toBe(original.category)
      expect(restored.instanceId).toBe(original.instanceId)
      expect(restored.handles.visibleInputs).toEqual(
        original.handles.visibleInputs
      )
      expect(restored.handles.visibleOutputs).toEqual(
        original.handles.visibleOutputs
      )
      expect(restored.handles.allInputs).toEqual(ALL_INPUTS)
      expect(restored.handles.allOutputs).toEqual(ALL_OUTPUTS)
    })
  })

  describe('handle operations', () => {
    it('provides all input handles for React Flow registration', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Handle Test',
        visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
        id: 'handle-test-id',
      })

      expect(node.getInputHandles()).toEqual(ALL_INPUTS)
    })

    it('provides all output handles for React Flow registration', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Handle Test',
        visibleOutputs: ['damperPosition', 'airflowSetpoint'],
        id: 'handle-test-id',
      })

      expect(node.getOutputHandles()).toEqual(ALL_OUTPUTS)
    })

    it('tracks visible inputs separately from all inputs', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Visible Test',
        visibleInputs: ['zoneTemperature', 'coolingSetpoint'],
        id: 'visible-test-id',
      })

      expect(node.handles.visibleInputs).toEqual([
        'zoneTemperature',
        'coolingSetpoint',
      ])
      expect(node.handles.allInputs).toEqual(ALL_INPUTS)
    })

    it('tracks visible outputs separately from all outputs', async () => {
      const node = await G36VavReheatNode.create({
        label: 'Visible Test',
        visibleOutputs: ['damperPosition'],
        id: 'visible-test-id',
      })

      expect(node.handles.visibleOutputs).toEqual(['damperPosition'])
      expect(node.handles.allOutputs).toEqual(ALL_OUTPUTS)
    })
  })

  describe('step execution flow', () => {
    const mockStepResponse = {
      instance_id: 'test-instance',
      outputs: {
        damperPosition: 0.75,
        valvePosition: 0.3,
        airflowSetpoint: 0.5,
        minOutdoorAirflow: 0.1,
        adjAreaBreathingZoneFlow: 0.05,
        adjPopBreathingZoneFlow: 0.05,
        flowSensorAlarm: 0,
        heatingValveRequest: 0,
        hotWaterPlantRequest: 0,
        leakingDamperAlarm: 0,
        leakingValveAlarm: 0,
        lowFlowAlarm: 0,
        lowTempAlarm: 0,
        zonePressureRequest: 0,
        zoneTempRequest: 1,
      },
    }

    function createMessage(value: unknown): Message {
      return {
        payload: { value, type: 'number' } as ComputeValue,
        _msgid: 'test-msg-id',
        timestamp: Date.now(),
        metadata: { source: 'test-source', type: 'test' },
      }
    }

    beforeEach(() => {
      mockStepInstance.mockResolvedValue(mockStepResponse)
    })

    it('buffers inputs until all required inputs are received', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'buffer-test',
        label: 'Buffer Test',
        id: 'buffer-test-id',
      })

      await node.receive(createMessage(22.0), 'zoneTemperature', 'source-1')
      await node.receive(createMessage(24.0), 'coolingSetpoint', 'source-2')

      expect(mockStepInstance).not.toHaveBeenCalled()
    })

    it('calls step API when all required inputs are received', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'step-test',
        label: 'Step Test',
        id: 'step-test-id',
      })

      await node.receive(createMessage(22.0), 'zoneTemperature', 'source-1')
      await node.receive(createMessage(24.0), 'coolingSetpoint', 'source-2')
      await node.receive(createMessage(20.0), 'heatingSetpoint', 'source-3')
      await node.receive(
        createMessage(16.0),
        'dischargeAirTemperature',
        'source-4'
      )
      await node.receive(createMessage(0.3), 'primaryAirflow', 'source-5')
      await node.receive(
        createMessage(13.0),
        'supplyAirTemperature',
        'source-6'
      )
      await node.receive(
        createMessage(12.0),
        'supplyAirTemperatureSetpoint',
        'source-7'
      )
      await node.receive(createMessage(true), 'fanStatus', 'source-8')
      await node.receive(createMessage('occupied'), 'operationMode', 'source-9')

      expect(mockStepInstance).toHaveBeenCalledTimes(1)
      expect(mockStepInstance).toHaveBeenCalledWith('step-test', {
        stepSize: 1.0,
        inputs: {
          zoneTemperature: 22.0,
          coolingSetpoint: 24.0,
          heatingSetpoint: 20.0,
          dischargeAirTemperature: 16.0,
          primaryAirflow: 0.3,
          supplyAirTemperature: 13.0,
          supplyAirTemperatureSetpoint: 12.0,
          fanStatus: true,
          operationMode: 'occupied',
        },
      })
    })

    it('emits outputs via send callback after step execution', async () => {
      const sentMessages: Array<{ message: Message; handle: string }> = []

      const sendCallback: SendCallback<ControlSequenceOutputHandle> = async (
        message,
        _nodeId,
        handle
      ) => {
        sentMessages.push({ message, handle })
      }

      const node = await G36VavReheatNode.create({
        instanceId: 'emit-test',
        label: 'Emit Test',
        id: 'emit-test-id',
      })
      node.setSendCallback(sendCallback)

      for (const [handle, value] of [
        ['zoneTemperature', 22.0],
        ['coolingSetpoint', 24.0],
        ['heatingSetpoint', 20.0],
        ['dischargeAirTemperature', 16.0],
        ['primaryAirflow', 0.3],
        ['supplyAirTemperature', 13.0],
        ['supplyAirTemperatureSetpoint', 12.0],
        ['fanStatus', true],
        ['operationMode', 'occupied'],
      ] as const) {
        await node.receive(createMessage(value), handle, 'source')
      }

      expect(sentMessages.length).toBeGreaterThan(0)
      const damperMsg = sentMessages.find((m) => m.handle === 'damperPosition')
      expect(damperMsg).toBeDefined()
      expect((damperMsg?.message.payload as ComputeValue).value).toBe(0.75)
    })

    it('stores computed outputs in metadata after step execution', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'metadata-test',
        label: 'Metadata Test',
        id: 'metadata-test-id',
      })

      for (const [handle, value] of [
        ['zoneTemperature', 22.0],
        ['coolingSetpoint', 24.0],
        ['heatingSetpoint', 20.0],
        ['dischargeAirTemperature', 16.0],
        ['primaryAirflow', 0.3],
        ['supplyAirTemperature', 13.0],
        ['supplyAirTemperatureSetpoint', 12.0],
        ['fanStatus', true],
        ['operationMode', 'occupied'],
      ] as const) {
        await node.receive(createMessage(value), handle, 'source')
      }

      const metadata = node.metadata
      expect(metadata.computedOutputs).toBeDefined()
      expect(metadata.computedOutputs?.damperPosition).toEqual({
        value: 0.75,
        type: 'number',
      })
    })

    it('clears message buffer after step execution', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'clear-test',
        label: 'Clear Test',
        id: 'clear-test-id',
      })

      for (const [handle, value] of [
        ['zoneTemperature', 22.0],
        ['coolingSetpoint', 24.0],
        ['heatingSetpoint', 20.0],
        ['dischargeAirTemperature', 16.0],
        ['primaryAirflow', 0.3],
        ['supplyAirTemperature', 13.0],
        ['supplyAirTemperatureSetpoint', 12.0],
        ['fanStatus', true],
        ['operationMode', 'occupied'],
      ] as const) {
        await node.receive(createMessage(value), handle, 'source')
      }

      expect(mockStepInstance).toHaveBeenCalledTimes(1)
      mockStepInstance.mockClear()

      await node.receive(createMessage(23.0), 'zoneTemperature', 'source')

      expect(mockStepInstance).not.toHaveBeenCalled()
    })

    it('reset clears the message buffer', async () => {
      const node = await G36VavReheatNode.create({
        instanceId: 'reset-test',
        label: 'Reset Test',
        id: 'reset-test-id',
      })

      await node.receive(createMessage(22.0), 'zoneTemperature', 'source')
      await node.receive(createMessage(24.0), 'coolingSetpoint', 'source')

      node.reset()

      for (const [handle, value] of [
        ['zoneTemperature', 22.0],
        ['coolingSetpoint', 24.0],
        ['heatingSetpoint', 20.0],
        ['dischargeAirTemperature', 16.0],
        ['primaryAirflow', 0.3],
        ['supplyAirTemperature', 13.0],
        ['supplyAirTemperatureSetpoint', 12.0],
        ['fanStatus', true],
        ['operationMode', 'occupied'],
      ] as const) {
        await node.receive(createMessage(value), handle, 'source')
      }

      expect(mockStepInstance).toHaveBeenCalledTimes(1)
    })
  })
})
