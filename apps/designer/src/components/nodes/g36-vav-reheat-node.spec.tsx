import { screen, fireEvent, within } from '@testing-library/react'
import userEvent from '@testing-library/user-event'
import { renderWithProviders as render } from '@test-utils/render'
import { G36VavReheatNode } from './g36-vav-reheat-node'
import { useFlowStore } from '@/store/use-flow-store'
import { NodeCategory, NodeType } from '@/types/infrastructure'
import {
  SequenceTypeMap,
  REHEAT_ALL_INPUTS,
  REHEAT_ALL_OUTPUTS,
  REHEAT_REQUIRED_INPUTS,
} from '@/domains/control-sequence'

jest.mock('@/store/use-flow-store')
jest.mock('@xyflow/react', () => ({
  Handle: ({
    id,
    type,
    position,
  }: {
    id: string
    type: string
    position: string
  }) => <div data-testid={`handle-${type}-${id}`} data-position={position} />,
  Position: {
    Left: 'left',
    Right: 'right',
  },
  useUpdateNodeInternals: () => jest.fn(),
}))

const mockUseFlowStore = useFlowStore as unknown as jest.Mock

const createMockHandles = (overrides = {}) => ({
  allInputs: REHEAT_ALL_INPUTS,
  allOutputs: REHEAT_ALL_OUTPUTS,
  requiredInputs: REHEAT_REQUIRED_INPUTS,
  visibleInputs: [...REHEAT_REQUIRED_INPUTS],
  visibleOutputs: ['damperPosition', 'valvePosition', 'airflowSetpoint'],
  parameterControlledInputs: [],
  inputCategories: {
    core: ['zoneTemperature', 'coolingSetpoint', 'heatingSetpoint'],
    discharge: ['dischargeAirTemperature', 'primaryAirflow'],
    supply: ['supplyAirTemperature', 'supplyAirTemperatureSetpoint'],
    system: ['fanStatus', 'operationMode'],
    optional: ['co2Concentration', 'co2Setpoint', 'hotWaterPlantStatus'],
  },
  outputCategories: {
    primary: ['damperPosition', 'valvePosition', 'airflowSetpoint'],
    secondary: ['minOutdoorAirflow', 'flowSensorAlarm'],
  },
  ...overrides,
})

const createNodeProps = (dataOverrides = {}) => ({
  id: 'test-node-1',
  data: {
    category: NodeCategory.CONTROL_SEQUENCE,
    sequenceType: SequenceTypeMap.VAV_REHEAT,
    type: NodeType.G36_VAV_REHEAT,
    label: 'Test VAV',
    handles: createMockHandles(),
    metadata: {
      instanceId: 'test-instance-12345678',
      label: 'Test VAV',
      handles: createMockHandles(),
    },
    ...dataOverrides,
  },
  type: 'g36-vav-reheat',
  selected: false,
  isConnectable: true,
  positionAbsoluteX: 0,
  positionAbsoluteY: 0,
  zIndex: 1,
  dragging: false,
  targetPosition: undefined,
  sourcePosition: undefined,
})

describe('G36VavReheatNode', () => {
  const mockUpdateNode = jest.fn()
  const mockSaveProject = jest.fn()

  beforeEach(() => {
    jest.clearAllMocks()
    mockUseFlowStore.mockImplementation((selector) => {
      const state = {
        nodes: [
          {
            id: 'test-node-1',
            data: {
              handles: createMockHandles(),
              metadata: {
                computedOutputs: {},
                inputValues: {},
              },
            },
          },
        ],
        updateNode: mockUpdateNode,
        saveProject: mockSaveProject,
      }
      return selector(state)
    })
  })

  describe('rendering', () => {
    it('renders node with label', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Test VAV')).toBeInTheDocument()
    })

    it('renders G36 badge', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('G36')).toBeInTheDocument()
    })

    it('renders truncated instance ID', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText(/Instance:/)).toBeInTheDocument()
      expect(screen.getByText(/test-ins\.\.\./)).toBeInTheDocument()
    })

    it('renders Inputs section header', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Inputs')).toBeInTheDocument()
    })

    it('renders Outputs section header', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Outputs')).toBeInTheDocument()
    })

    it('renders settings button', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      const buttons = screen.getAllByRole('button')
      const settingsButton = buttons.find((btn) =>
        btn.querySelector('svg.lucide-settings')
      )
      expect(settingsButton).toBeInTheDocument()
    })
  })

  describe('required inputs', () => {
    it('renders required inputs with asterisk marker', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Zone Temperature')).toBeInTheDocument()
      expect(screen.getByText('Cooling Setpoint')).toBeInTheDocument()
      expect(screen.getByText('Heating Setpoint')).toBeInTheDocument()
    })

    it('marks required inputs with asterisk', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      const zoneTemp = screen.getByText('Zone Temperature')
      const container = zoneTemp.closest('div')
      expect(container).toHaveTextContent('*')
    })

    it('does not show remove button for required inputs', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      const zoneTemp = screen.getByText('Zone Temperature')
      const container = zoneTemp.closest('.group')
      const removeButtons = container?.querySelectorAll('button')

      const xButtons = Array.from(removeButtons || []).filter(
        (btn) => btn.querySelector('svg')?.classList.contains('h-3')
      )
      expect(xButtons.length).toBe(0)
    })
  })

  describe('optional inputs', () => {
    it('shows Add Input button when optional inputs available', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Add Input')).toBeInTheDocument()
    })

    it('opens dropdown menu when Add Input clicked', async () => {
      const user = userEvent.setup()
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      const addButton = screen.getByText('Add Input')
      await user.click(addButton)

      expect(screen.getByText('Optional')).toBeInTheDocument()
    })
  })

  describe('outputs', () => {
    it('renders visible outputs', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Damper Position')).toBeInTheDocument()
      expect(screen.getByText('Valve Position')).toBeInTheDocument()
      expect(screen.getByText('Airflow Setpoint')).toBeInTheDocument()
    })

    it('shows Add Output button when optional outputs available', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Add Output')).toBeInTheDocument()
    })
  })

  describe('handle interactions', () => {
    it('calls updateNode when removing optional output', async () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          nodes: [
            {
              id: 'test-node-1',
              data: {
                handles: createMockHandles({
                  visibleOutputs: ['damperPosition', 'valvePosition'],
                }),
                metadata: {
                  computedOutputs: {},
                  inputValues: {},
                },
              },
            },
          ],
          updateNode: mockUpdateNode,
          saveProject: mockSaveProject,
        }
        return selector(state)
      })

      const user = userEvent.setup()
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      const damperOutput = screen.getByText('Damper Position')
      const container = damperOutput.closest('.group')
      const removeButton = container?.querySelector('button')

      if (removeButton) {
        await user.click(removeButton)

        expect(mockUpdateNode).toHaveBeenCalledWith({
          type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
          nodeId: 'test-node-1',
          handles: expect.objectContaining({
            visibleOutputs: ['valvePosition'],
          }),
        })
      }
    })
  })

  describe('computed values display', () => {
    it('displays output values when available', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          nodes: [
            {
              id: 'test-node-1',
              data: {
                handles: createMockHandles(),
                metadata: {
                  computedOutputs: {
                    damperPosition: { type: 'number', value: 0.75 },
                    valvePosition: { type: 'number', value: 0.5 },
                  },
                  inputValues: {},
                },
              },
            },
          ],
          updateNode: mockUpdateNode,
          saveProject: mockSaveProject,
        }
        return selector(state)
      })

      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('0.75')).toBeInTheDocument()
      expect(screen.getByText('0.50')).toBeInTheDocument()
    })

    it('displays input values when available', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          nodes: [
            {
              id: 'test-node-1',
              data: {
                handles: createMockHandles(),
                metadata: {
                  computedOutputs: {},
                  inputValues: {
                    zoneTemperature: 22.5,
                    coolingSetpoint: 24.0,
                  },
                },
              },
            },
          ],
          updateNode: mockUpdateNode,
          saveProject: mockSaveProject,
        }
        return selector(state)
      })

      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('22.50')).toBeInTheDocument()
      expect(screen.getByText('24.00')).toBeInTheDocument()
    })

    it('displays boolean values correctly', () => {
      mockUseFlowStore.mockImplementation((selector) => {
        const state = {
          nodes: [
            {
              id: 'test-node-1',
              data: {
                handles: createMockHandles(),
                metadata: {
                  computedOutputs: {},
                  inputValues: {
                    fanStatus: true,
                  },
                },
              },
            },
          ],
          updateNode: mockUpdateNode,
          saveProject: mockSaveProject,
        }
        return selector(state)
      })

      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('true')).toBeInTheDocument()
    })
  })

  describe('category grouping', () => {
    it('renders input categories as group headers', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Core')).toBeInTheDocument()
      expect(screen.getByText('Discharge')).toBeInTheDocument()
      expect(screen.getByText('Supply')).toBeInTheDocument()
      expect(screen.getByText('System')).toBeInTheDocument()
    })

    it('renders output categories as group headers', () => {
      const props = createNodeProps()
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('Primary')).toBeInTheDocument()
    })
  })

  describe('default label', () => {
    it('uses default label when data label is undefined', () => {
      const props = createNodeProps({ label: undefined })
      render(<G36VavReheatNode {...(props as any)} />)

      expect(screen.getByText('VAV Reheat')).toBeInTheDocument()
    })
  })
})
