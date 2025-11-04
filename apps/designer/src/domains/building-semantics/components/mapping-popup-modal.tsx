'use client'

import { useState, useEffect } from 'react'
import {
  Dialog,
  DialogContent,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog'
import { Button } from '@/components/ui/button'
import { Label } from '@/components/ui/label'
import {
  Collapsible,
  CollapsibleContent,
  CollapsibleTrigger,
} from '@/components/ui/collapsible'
import { ChevronDown, AlertCircle } from 'lucide-react'
import { PointContextCard } from './point-context-card'
import { ConfidenceIndicator } from './confidence-indicator'
import { OverallConfidenceBar } from './overall-confidence-bar'
import { SearchableSelect } from './searchable-select'
import { SpaceComboBox } from './space-combobox'
import { SpaceMultiComboBox } from './space-multi-combobox'
import { mockValidationService } from '../adapters/ashrae-223p/services'
import {
  useEquipmentTypesQuery,
  useDeviceTypesQuery,
  useObservablePropertiesQuery,
} from '../api/queries/use-templates-query'
import { useMappingSuggestionViewModel } from '../view-models/use-mapping-suggestion-view-model'
import { useSpacesViewModel } from '../view-models/use-spaces-view-model'
import { useCreateEquipmentMapping } from '../view-models/use-create-equipment-mapping'
import { useDeleteMappingMutation } from '../api/queries/use-mappings-query'
import { toast } from 'sonner'
import type {
  BACnetPointData,
  SemanticEquipment,
  ValidationResultDTO,
  BACnetControllerData,
} from '../adapters/ashrae-223p/schemas'
import {
  createDeviceIdentifier,
  createObjectIdentifier,
} from '../utils/bacnet-keys'

interface MappingPopupModalProps {
  projectId: string
  open: boolean
  point: BACnetPointData | null
  controller: BACnetControllerData | null
  existingMapping?: SemanticEquipment | null
  mode?: 'create' | 'edit'
  onConfirm: (mapping: SemanticEquipment) => void
  onSkip: () => void
  onOpenChange: (open: boolean) => void
}

export function MappingPopupModal({
  projectId,
  open,
  point,
  controller,
  existingMapping,
  mode = 'create',
  onConfirm,
  onSkip,
  onOpenChange,
}: MappingPopupModalProps) {
  const [equipmentType, setEquipmentType] = useState('')
  const [deviceType, setDeviceType] = useState('')
  const [observableProperty, setObservableProperty] = useState('')
  const [physicalSpaceName, setPhysicalSpaceName] = useState('')
  const [domainSpaceNames, setDomainSpaceNames] = useState<string[]>([])
  const [isSpaceSectionOpen, setIsSpaceSectionOpen] = useState(true)

  const { data: equipmentTypes = [] } = useEquipmentTypesQuery()
  const { data: deviceTypes = [] } = useDeviceTypesQuery()
  const { data: observableProperties = [] } = useObservablePropertiesQuery()
  const { physicalSpaces, domainSpaces } = useSpacesViewModel(projectId)

  const { execute: createMapping } = useCreateEquipmentMapping()
  const { mutate: deleteMapping } = useDeleteMappingMutation()

  const suggestion = useMappingSuggestionViewModel(projectId, point)
  const [validationResult, setValidationResult] =
    useState<ValidationResultDTO | null>(null)

  useEffect(() => {
    if (open) {
      if (existingMapping) {
        setEquipmentType(existingMapping.equipmentType)
        setDeviceType(existingMapping.deviceType)
        setObservableProperty(existingMapping.observableProperty)
        setPhysicalSpaceName('')
        setDomainSpaceNames([])
      } else if (suggestion) {
        setEquipmentType(suggestion.equipmentType.value)
        setDeviceType(suggestion.deviceType.value)
        setObservableProperty(suggestion.observableProperty.value)
        setPhysicalSpaceName(suggestion.physicalSpace?.value.label || '')
        setDomainSpaceNames(
          suggestion.domainSpaces?.map((ds) => ds.value.label) || []
        )
      }
    }
  }, [suggestion, existingMapping, open])

  const autoFillHint = suggestion?.autoFillSource
    ? 'Auto-filled from previous point on same device'
    : undefined

  useEffect(() => {
    if (point && deviceType) {
      const result = mockValidationService.validateMapping(
        point,
        deviceType as never
      )
      setValidationResult(result)
    } else {
      setValidationResult(null)
    }
  }, [point, deviceType])

  const handleConfirm = async () => {
    if (!point) return

    const propertyType = observableProperties.some(
      (prop) => prop === observableProperty
    )
      ? 'quantifiable'
      : 'enumerated'

    const mapping = await createMapping({
      projectId,
      pointId: point.pointId,
      equipmentType,
      deviceType,
      observableProperty,
      propertyType,
      physicalSpaceName,
      domainSpaceNames,
      externalReference: {
        deviceIdentifier: controller
          ? createDeviceIdentifier(controller.deviceId)
          : undefined,
        objectIdentifier: createObjectIdentifier(
          point.objectType,
          point.objectId
        ),
        objectName: point.name,
        propertyIdentifier: 'present-value',
      },
    })

    onConfirm(mapping)
  }

  const handleSkip = () => {
    onSkip()
  }

  const handleDelete = () => {
    if (!existingMapping?.externalReference.compositeKey) {
      toast.error('Cannot delete: missing composite key')
      return
    }

    deleteMapping(
      {
        projectId,
        compositeKey: existingMapping.externalReference.compositeKey,
      },
      {
        onSuccess: () => {
          toast.success('223P mapping removed')
          onOpenChange(false)
        },
        onError: (error) => {
          toast.error(error.message || 'Failed to remove mapping')
        },
      }
    )
  }

  if (!point) return null

  return (
    <Dialog open={open} onOpenChange={onOpenChange}>
      <DialogContent className="max-w-2xl max-h-[90vh] overflow-y-auto">
        <DialogHeader>
          <DialogTitle>
            {mode === 'edit'
              ? 'Edit 223P Mapping'
              : 'Tag BACnet Point with ASHRAE 223P'}
          </DialogTitle>
        </DialogHeader>

        <div className="space-y-6">
          <PointContextCard point={point} controller={controller} />

          <div className="space-y-4">
            <div className="space-y-2">
              <Label htmlFor="equipment-type">Equipment Type</Label>
              <SearchableSelect
                id="equipment-type"
                value={equipmentType}
                onValueChange={setEquipmentType}
                options={equipmentTypes}
                aiSuggestion={
                  suggestion
                    ? {
                        value: suggestion.equipmentType.value,
                        confidence: suggestion.equipmentType.confidence,
                      }
                    : undefined
                }
                autoFillHint={autoFillHint}
                placeholder="Select equipment type..."
                emptyText="No equipment types found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.equipmentType.confidence}
                />
              )}
            </div>

            <Collapsible
              open={isSpaceSectionOpen}
              onOpenChange={setIsSpaceSectionOpen}
              className="space-y-2"
            >
              <CollapsibleTrigger asChild>
                <Button
                  variant="ghost"
                  className="flex w-full justify-between p-0 hover:bg-transparent"
                  type="button"
                >
                  <Label className="text-base font-semibold cursor-pointer">
                    Space Associations (Optional)
                  </Label>
                  <ChevronDown
                    className={`h-4 w-4 transition-transform duration-200 ${
                      isSpaceSectionOpen ? 'rotate-180' : ''
                    }`}
                  />
                </Button>
              </CollapsibleTrigger>
              <CollapsibleContent className="space-y-4 pt-2">
                <div className="space-y-2">
                  <Label htmlFor="physical-space">
                    Physical Space (Optional)
                  </Label>
                  <p className="text-xs text-muted-foreground mb-2">
                    Where is this equipment physically installed?
                  </p>
                  <SpaceComboBox
                    id="physical-space"
                    value={physicalSpaceName}
                    onValueChange={setPhysicalSpaceName}
                    spaces={physicalSpaces}
                    aiSuggestion={
                      suggestion?.physicalSpace
                        ? {
                            value: suggestion.physicalSpace.value.label,
                            confidence: suggestion.physicalSpace.confidence,
                          }
                        : undefined
                    }
                    autoFillHint={autoFillHint}
                    placeholder="Select or type physical location..."
                  />
                  {suggestion?.physicalSpace && (
                    <ConfidenceIndicator
                      confidence={suggestion.physicalSpace.confidence}
                    />
                  )}
                </div>

                <div className="space-y-2">
                  <Label htmlFor="domain-spaces">
                    Domain Spaces (Optional)
                  </Label>
                  <p className="text-xs text-muted-foreground mb-2">
                    Which functional areas does this equipment serve or control?
                  </p>
                  <SpaceMultiComboBox
                    id="domain-spaces"
                    value={domainSpaceNames}
                    onValueChange={setDomainSpaceNames}
                    spaces={domainSpaces}
                    aiSuggestions={suggestion?.domainSpaces?.map((ds) => ({
                      value: ds.value.label,
                      confidence: ds.confidence,
                    }))}
                    autoFillHint={autoFillHint}
                    placeholder="Select or type domain spaces..."
                  />
                </div>
              </CollapsibleContent>
            </Collapsible>

            <div className="space-y-2">
              <div className="flex items-center gap-2">
                <Label htmlFor="device-type">Device Type</Label>
                {validationResult && !validationResult.isValid && (
                  <AlertCircle className="h-4 w-4 text-destructive" />
                )}
              </div>
              <SearchableSelect
                id="device-type"
                value={deviceType}
                onValueChange={setDeviceType}
                options={deviceTypes}
                aiSuggestion={
                  suggestion
                    ? {
                        value: suggestion.deviceType.value,
                        confidence: suggestion.deviceType.confidence,
                      }
                    : undefined
                }
                placeholder="Select device type..."
                emptyText="No device types found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.deviceType.confidence}
                />
              )}
              {validationResult &&
                !validationResult.isValid &&
                validationResult.errors.length > 0 && (
                  <div className="flex items-start gap-2 text-sm text-destructive">
                    <AlertCircle className="h-4 w-4 mt-0.5 flex-shrink-0" />
                    <span>{validationResult.errors[0].message}</span>
                  </div>
                )}
            </div>

            <div className="space-y-2">
              <Label htmlFor="observable-property">Observable Property</Label>
              <SearchableSelect
                id="observable-property"
                value={observableProperty}
                onValueChange={setObservableProperty}
                options={observableProperties}
                aiSuggestion={
                  suggestion
                    ? {
                        value: suggestion.observableProperty.value,
                        confidence: suggestion.observableProperty.confidence,
                      }
                    : undefined
                }
                placeholder="Select observable property..."
                emptyText="No observable properties found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.observableProperty.confidence}
                />
              )}
            </div>
          </div>

          {suggestion && (
            <OverallConfidenceBar confidence={suggestion.overallConfidence} />
          )}
        </div>

        <DialogFooter>
          {mode === 'edit' && existingMapping && (
            <Button
              variant="destructive"
              onClick={handleDelete}
              className="mr-auto"
            >
              Delete Mapping
            </Button>
          )}
          <Button variant="outline" onClick={handleSkip}>
            {mode === 'edit' ? 'Cancel' : 'Skip'}
          </Button>
          <Button
            onClick={handleConfirm}
            disabled={validationResult !== null && !validationResult.isValid}
          >
            {mode === 'edit' ? 'Update' : 'Confirm'}
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
