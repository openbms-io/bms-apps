import { render, screen, fireEvent } from '@test-utils/render'
import { BuildingSemanticsModal } from './index'
import * as BacnetReferenceQuery from '../../api/queries/use-bacnet-reference-query'
import * as SystemsQuery from '../../api/queries/use-systems-query'
import * as DevicesQuery from '../../api/queries/use-devices-query'
import * as PropertiesQuery from '../../api/queries/use-properties-query'
import * as SaveMutation from '../../api/mutations/use-save-bacnet-reference-mutation'

jest.mock('../../api/queries/use-bacnet-reference-query')
jest.mock('../../api/queries/use-systems-query')
jest.mock('../../api/queries/use-devices-query')
jest.mock('../../api/queries/use-properties-query')
jest.mock('../../api/mutations/use-save-bacnet-reference-mutation')
jest.mock('sonner', () => ({
  toast: {
    success: jest.fn(),
    error: jest.fn(),
  },
}))

describe('BuildingSemanticsModal - Presentation Tests', () => {
  const mockOnSaved = jest.fn()
  const mockOnOpenChange = jest.fn()
  const mockMutate = jest.fn()

  const defaultProps = {
    projectId: 'project-123',
    open: true,
    bacnetPointId: 'point-abc',
    bacnetObjectType: 'analog-input',
    pointLabel: 'Temperature Sensor 1',
    templates: [],
    onSaved: mockOnSaved,
    onOpenChange: mockOnOpenChange,
  }

  const mockSystems = [
    { systemUri: 'sys-1', label: 'HVAC System 1', templateId: 'hvac-template' },
    {
      systemUri: 'sys-2',
      label: 'Lighting System',
      templateId: 'lighting-template',
    },
  ]

  const mockDevices = [
    { deviceUri: 'dev-1', label: 'VAV Box 1' },
    { deviceUri: 'dev-2', label: 'Temperature Sensor' },
  ]

  const mockProperties = [
    { propertyUri: 'prop-1', label: 'Zone Temperature', isActuatable: false },
    { propertyUri: 'prop-2', label: 'Damper Position', isActuatable: true },
  ]

  beforeEach(() => {
    jest.clearAllMocks()

    jest
      .spyOn(BacnetReferenceQuery, 'useBacnetReferenceQuery')
      .mockReturnValue({
        data: undefined,
      } as any)

    jest.spyOn(SystemsQuery, 'useSystemsQuery').mockReturnValue({
      data: mockSystems,
      isLoading: false,
    } as any)

    jest.spyOn(DevicesQuery, 'useDevicesQuery').mockReturnValue({
      data: mockDevices,
      isLoading: false,
    } as any)

    jest.spyOn(PropertiesQuery, 'usePropertiesQuery').mockReturnValue({
      data: mockProperties,
      isLoading: false,
    } as any)

    jest.spyOn(SaveMutation, 'useSaveBacnetReferenceMutation').mockReturnValue({
      mutate: mockMutate,
      isPending: false,
    } as any)
  })

  describe('Modal Rendering', () => {
    it('should render modal with correct title and point information', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      expect(
        screen.getByText('Map BACnet Point to ASHRAE 223P')
      ).toBeInTheDocument()
      expect(screen.getByText('Temperature Sensor 1')).toBeInTheDocument()
      expect(screen.getByText(/point-abc.*analog-input/i)).toBeInTheDocument()
    })

    it('should render all three selection fields with labels', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      expect(screen.getByText('System Instance')).toBeInTheDocument()
      expect(screen.getByText('Device')).toBeInTheDocument()
      expect(screen.getByText('Property')).toBeInTheDocument()
    })

    it('should not render modal when open is false', () => {
      render(<BuildingSemanticsModal {...defaultProps} open={false} />)

      expect(
        screen.queryByText('Map BACnet Point to ASHRAE 223P')
      ).not.toBeInTheDocument()
    })
  })

  describe('Save Button State', () => {
    it('should have Save button disabled initially (no selections)', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      const saveButton = screen.getByRole('button', { name: /save mapping/i })
      expect(saveButton).toBeDisabled()
    })

    it('should show loading spinner when save is pending', () => {
      jest
        .spyOn(SaveMutation, 'useSaveBacnetReferenceMutation')
        .mockReturnValue({
          mutate: mockMutate,
          isPending: true,
        } as any)

      render(<BuildingSemanticsModal {...defaultProps} />)

      const saveButton = screen.getByRole('button', { name: /save mapping/i })
      expect(saveButton).toBeDisabled()
      expect(
        screen
          .getByText(/save mapping/i)
          .closest('button')
          ?.querySelector('svg')
      ).toBeInTheDocument()
    })
  })

  describe('Cancel Button', () => {
    it('should call onOpenChange(false) when user clicks cancel', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      const cancelButton = screen.getByRole('button', { name: /cancel/i })
      fireEvent.click(cancelButton)

      expect(mockOnOpenChange).toHaveBeenCalledWith(false)
    })

    it('should disable cancel button while save is pending', () => {
      jest
        .spyOn(SaveMutation, 'useSaveBacnetReferenceMutation')
        .mockReturnValue({
          mutate: mockMutate,
          isPending: true,
        } as any)

      render(<BuildingSemanticsModal {...defaultProps} />)

      const cancelButton = screen.getByRole('button', { name: /cancel/i })
      expect(cancelButton).toBeDisabled()
    })
  })

  describe('Loading States', () => {
    it('should disable system selector while systems are loading', () => {
      jest.spyOn(SystemsQuery, 'useSystemsQuery').mockReturnValue({
        data: [],
        isLoading: true,
      } as any)

      render(<BuildingSemanticsModal {...defaultProps} />)

      const systemSelector = screen
        .getByText(/select system instance/i)
        .closest('button')
      expect(systemSelector).toBeDisabled()
    })

    it('should disable device selector until system is selected', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      expect(screen.getByText(/select a system first/i)).toBeInTheDocument()
    })

    it('should disable property selector until device is selected', () => {
      render(<BuildingSemanticsModal {...defaultProps} />)

      expect(screen.getByText(/select a device first/i)).toBeInTheDocument()
    })
  })

  describe('Existing Reference Pre-population', () => {
    it('should display pre-populated selections when existing reference is loaded', () => {
      jest
        .spyOn(BacnetReferenceQuery, 'useBacnetReferenceQuery')
        .mockReturnValue({
          data: {
            systemUri: 'sys-1',
            deviceUri: 'dev-1',
            propertyUri: 'prop-1',
            bacnetPointId: 'point-abc',
          },
        } as any)

      render(<BuildingSemanticsModal {...defaultProps} />)

      expect(
        screen.getByText('HVAC System 1 (hvac-template)')
      ).toBeInTheDocument()
      expect(screen.getByText('VAV Box 1')).toBeInTheDocument()
      expect(screen.getByText('Zone Temperature [Input]')).toBeInTheDocument()
    })
  })
})
