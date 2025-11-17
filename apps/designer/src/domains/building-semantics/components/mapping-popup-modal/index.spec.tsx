import { render, screen, waitFor } from '@test-utils/render'
import userEvent from '@testing-library/user-event'
import { MappingPopupModal } from './index'
import type {
  BACnetPointData,
  BACnetControllerData,
  SemanticEquipment,
} from '../../adapters/ashrae-223p/schemas'
import type { TemplatesResponseDto } from '../../api/generated'

// Mock the hooks
jest.mock('../../api/queries/use-templates-query')
jest.mock('../../view-models/use-mapping-suggestion-view-model')
jest.mock('../../view-models/use-spaces-view-model')
jest.mock('../../view-models/use-create-equipment-mapping')
jest.mock('../../api/mutations/use-save-mappings-mutation')
jest.mock('../../view-models/use-mappings-view-model')

import { useTemplatesQuery } from '../../api/queries/use-templates-query'
import { useMappingSuggestionViewModel } from '../../view-models/use-mapping-suggestion-view-model'
import { useSpacesViewModel } from '../../view-models/use-spaces-view-model'
import { useCreateEquipmentMapping } from '../../view-models/use-create-equipment-mapping'
import { useSaveMappingsMutation } from '../../api/mutations/use-save-mappings-mutation'
import { useMappingsViewModel } from '../../view-models/use-mappings-view-model'

const mockUseTemplatesQuery = useTemplatesQuery as jest.MockedFunction<
  typeof useTemplatesQuery
>
const mockUseMappingSuggestionViewModel =
  useMappingSuggestionViewModel as jest.MockedFunction<
    typeof useMappingSuggestionViewModel
  >
const mockUseSpacesViewModel = useSpacesViewModel as jest.MockedFunction<
  typeof useSpacesViewModel
>
const mockUseCreateEquipmentMapping = useCreateEquipmentMapping as jest.MockedFunction<
  typeof useCreateEquipmentMapping
>
const mockUseSaveMappingsMutation = useSaveMappingsMutation as jest.MockedFunction<
  typeof useSaveMappingsMutation
>
const mockUseMappingsViewModel = useMappingsViewModel as jest.MockedFunction<
  typeof useMappingsViewModel
>

// Test data
const mockTemplates: TemplatesResponseDto = {
  systems: [
    {
      id: 'vav-reheat',
      label: 'VAV Reheat',
      classUri: 'http://data.ashrae.org/standard223#TerminalUnit',
      description: null,
      devices: [
        {
          id: 'damper',
          label: 'Damper',
          classUri: 'http://data.ashrae.org/standard223#Damper',
          deviceType: 'other',
          description: null,
          properties: [
            {
              id: 'air-temperature',
              label: 'Air Temperature',
              classUri:
                'http://data.ashrae.org/standard223#QuantifiableObservableProperty',
              propertyType: 'quantifiable',
              quantityKind: 'Temperature',
              unit: 'DEG_C',
              medium: 'Fluid-Air',
              enumerationKind: null,
              isActuatable: false,
              description: null,
            },
            {
              id: 'damper-command',
              label: 'Damper Command',
              classUri:
                'http://data.ashrae.org/standard223#QuantifiableActuatableProperty',
              propertyType: 'quantifiable',
              quantityKind: 'Dimensionless',
              unit: 'PERCENT',
              medium: null,
              enumerationKind: null,
              isActuatable: true,
              description: null,
            },
          ],
        },
      ],
    },
    {
      id: 'exhaust-air-unit',
      label: 'Exhaust Air Unit',
      classUri: 'http://data.ashrae.org/standard223#ExhaustAirUnit',
      description: null,
      devices: [
        {
          id: 'heat-recovery-coil',
          label: 'Heat Recovery Coil',
          classUri: 'http://data.ashrae.org/standard223#Coil',
          deviceType: 'other',
          description: null,
          properties: [
            {
              id: 'water-temperature',
              label: 'Water Temperature',
              classUri:
                'http://data.ashrae.org/standard223#QuantifiableObservableProperty',
              propertyType: 'quantifiable',
              quantityKind: 'Temperature',
              unit: 'DEG_C',
              medium: 'Fluid-Water',
              enumerationKind: null,
              isActuatable: false,
              description: null,
            },
          ],
        },
      ],
    },
  ],
  spaceTypes: [],
}

const mockPoint: BACnetPointData = {
  pointId: 'test-point-1',
  objectType: 'analog-value',
  objectId: 2,
  supervisorId: 'supervisor-1',
  controllerId: 'controller-1',
  name: 'Test Point',
  discoveredProperties: {},
}

const mockController: BACnetControllerData = {
  deviceId: 599,
  controllerId: 'controller-1',
  name: 'Test Controller',
}

const mockExistingMapping: SemanticEquipment = {
  equipmentTypeId: 'exhaust-air-unit',
  deviceTypeId: 'heat-recovery-coil',
  propertyId: 'water-temperature',
  propertyType: 'quantifiable',
  physicalSpaceId: 'urn:bms:Space:room-101',
  domainSpaceIds: ['urn:bms:Zone:hvac-1', 'urn:bms:Zone:lighting-1'],
  connectionPoints: undefined,
  externalReference: {
    compositeKey: 'device,599:analog-value,2',
    deviceIdentifier: undefined,
    objectIdentifier: undefined,
    objectName: undefined,
    propertyIdentifier: 'present-value',
  },
  schemaVersion: '223p-2023',
}

describe('MappingPopupModal', () => {
  const mockOnConfirm = jest.fn()
  const mockOnSkip = jest.fn()
  const mockOnOpenChange = jest.fn()
  const mockExecute = jest.fn()
  const mockMutate = jest.fn()

  beforeEach(() => {
    jest.clearAllMocks()

    // Default mock implementations
    mockUseTemplatesQuery.mockReturnValue({
      data: mockTemplates,
      isLoading: false,
      error: null,
    } as any)

    mockUseMappingSuggestionViewModel.mockReturnValue(undefined)

    mockUseSpacesViewModel.mockReturnValue({
      physicalSpaces: [
        { id: 'urn:bms:Space:room-101', label: 'Room 101' },
        { id: 'urn:bms:Space:room-202', label: 'Room 202' },
      ],
      domainSpaces: [
        { id: 'urn:bms:Zone:hvac-1', label: 'HVAC Zone 1' },
        { id: 'urn:bms:Zone:lighting-1', label: 'Lighting Zone 1' },
      ],
    } as any)

    mockUseCreateEquipmentMapping.mockReturnValue({
      execute: mockExecute,
    } as any)

    mockUseSaveMappingsMutation.mockReturnValue({
      mutate: mockMutate,
    } as any)

    mockUseMappingsViewModel.mockReturnValue({
      data: new Map(),
      isLoading: false,
      error: null,
    } as any)
  })

  describe('Initialization Tests', () => {
    it('should render empty form in create mode', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          mode="create"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByText('Tag BACnet Point with ASHRAE 223P')).toBeInTheDocument()
      expect(screen.getByLabelText(/Equipment Type/i)).toBeInTheDocument()
      expect(screen.getByLabelText(/Device Type/i)).toBeInTheDocument()
      expect(screen.getByLabelText(/Observable Property/i)).toBeInTheDocument()
    })

    it('should populate form from existingMapping in edit mode', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByText('Edit 223P Mapping')).toBeInTheDocument()
    })

    it('[REGRESSION] should preserve property selection from existingMapping', async () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      await waitFor(() => {
        const allComboboxes = screen.getAllByRole('combobox')
        expect(allComboboxes.length).toBeGreaterThan(0)
      })

      const allComboboxes = screen.getAllByRole('combobox')
      const comboboxTexts = allComboboxes.map(cb => cb.textContent)

      expect(comboboxTexts.some(text => text?.includes('Water Temperature'))).toBe(true)
    })

    it('[REGRESSION] should populate space fields from existingMapping', async () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      await waitFor(() => {
        const allComboboxes = screen.getAllByRole('combobox')
        expect(allComboboxes.length).toBeGreaterThan(0)
      })

      const allComboboxes = screen.getAllByRole('combobox')
      const comboboxTexts = allComboboxes.map(cb => cb.textContent)

      expect(comboboxTexts.some(text => text?.includes('urn:bms:Space:room-101'))).toBe(true)
    })
  })

  describe('Cascading Selection Tests', () => {
    it('[REGRESSION] should not clear selections during initialization', async () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      await waitFor(() => {
        const allComboboxes = screen.getAllByRole('combobox')
        expect(allComboboxes.length).toBeGreaterThan(0)
      })

      const allComboboxes = screen.getAllByRole('combobox')
      const comboboxTexts = allComboboxes.map(cb => cb.textContent)

      expect(comboboxTexts.some(text => text?.includes('Exhaust Air Unit'))).toBe(true)
      expect(comboboxTexts.some(text => text?.includes('Heat Recovery Coil'))).toBe(true)
      expect(comboboxTexts.some(text => text?.includes('Water Temperature'))).toBe(true)
    })
  })

  describe('Form Validation Tests', () => {
    it('should disable confirm button when fields incomplete', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          mode="create"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      const confirmButton = screen.getByRole('button', { name: /Confirm/i })
      expect(confirmButton).toBeDisabled()
    })
  })

  describe('Modal Behavior Tests', () => {
    it('should show skip button in create mode', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          mode="create"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByRole('button', { name: /Skip/i })).toBeInTheDocument()
    })

    it('should show cancel button in edit mode', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByRole('button', { name: /Cancel/i })).toBeInTheDocument()
    })

    it('should show delete button in edit mode', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          existingMapping={mockExistingMapping}
          mode="edit"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByRole('button', { name: /Delete Mapping/i })).toBeInTheDocument()
    })

    it('should call onSkip when skip button clicked', async () => {
      const user = userEvent.setup()
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          mode="create"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      await user.click(screen.getByRole('button', { name: /Skip/i }))
      expect(mockOnSkip).toHaveBeenCalled()
    })
  })

  describe('Point Context Display', () => {
    it('should display point information', () => {
      render(
        <MappingPopupModal
          projectId="test-project"
          open={true}
          point={mockPoint}
          controller={mockController}
          mode="create"
          onConfirm={mockOnConfirm}
          onSkip={mockOnSkip}
          onOpenChange={mockOnOpenChange}
        />
      )

      expect(screen.getByText('Test Point')).toBeInTheDocument()
    })
  })
})
