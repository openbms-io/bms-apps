'use client'

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
import { ChevronDown } from 'lucide-react'
import { PointContextCard } from '../point-context-card'
import { ConfidenceIndicator } from '../confidence-indicator'
import { OverallConfidenceBar } from '../overall-confidence-bar'
import { SearchableSelect } from '../searchable-select'
import { SpaceComboBox } from '../space-combobox'
import { SpaceMultiComboBox } from '../space-multi-combobox'
import { useTemplatesQuery } from '../../api/queries/use-templates-query'
import { useMappingSuggestionViewModel } from '../../view-models/use-mapping-suggestion-view-model'
import { useSpacesViewModel } from '../../view-models/use-spaces-view-model'
import type {
  BACnetPointData,
  SemanticEquipment,
  BACnetControllerData,
} from '../../adapters/ashrae-223p/schemas'
import { useMappingFormState } from './use-mapping-form-state'
import { useTemplateOptions } from './use-template-options'
import { useMappingConfirm } from './use-mapping-confirm'
import { useMappingDelete } from './use-mapping-delete'

interface MappingPopupModalProps {
  projectId: string
  open: boolean
  point: BACnetPointData | undefined
  controller: BACnetControllerData | undefined
  existingMapping?: SemanticEquipment | undefined
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
  const { data: templates } = useTemplatesQuery()
  const { physicalSpaces, domainSpaces } = useSpacesViewModel(projectId)
  const suggestion = useMappingSuggestionViewModel(projectId, point)

  const formState = useMappingFormState(open, existingMapping, suggestion)
  const { equipmentTypes, deviceTypes, observableProperties } = useTemplateOptions(
    templates,
    formState.state.equipmentType,
    formState.state.deviceType
  )
  const { confirmMapping } = useMappingConfirm(
    projectId,
    point,
    controller,
    observableProperties
  )
  const { deleteMapping } = useMappingDelete(projectId, point, controller)

  const handleConfirm = async () => {
    const mapping = await confirmMapping(formState.state)
    if (mapping) onConfirm(mapping)
  }

  const handleDelete = () => {
    deleteMapping(() => onOpenChange(false))
  }

  if (!point) return null

  const {
    equipmentType,
    deviceType,
    observableProperty,
    physicalSpaceName,
    domainSpaceNames,
    isSpaceSectionOpen,
  } = formState.state

  const isFormValid = equipmentType && deviceType && observableProperty

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
                onValueChange={formState.setEquipmentType}
                options={equipmentTypes}
                aiSuggestion={
                  suggestion
                    ? {
                        id: suggestion.equipmentTypeId.id,
                        confidence: suggestion.equipmentTypeId.confidence,
                      }
                    : undefined
                }
                placeholder="Select equipment type..."
                emptyText="No equipment types found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.equipmentTypeId.confidence}
                />
              )}
            </div>

            <Collapsible
              open={isSpaceSectionOpen}
              onOpenChange={formState.toggleSpaceSection}
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
                    onValueChange={formState.setPhysicalSpaceName}
                    spaces={physicalSpaces}
                    aiSuggestion={
                      suggestion?.physicalSpace
                        ? {
                            id: suggestion.physicalSpace.id.label,
                            confidence: suggestion.physicalSpace.confidence,
                          }
                        : undefined
                    }
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
                    onValueChange={formState.setDomainSpaceNames}
                    spaces={domainSpaces}
                    aiSuggestions={suggestion?.domainSpaces?.map((ds) => ({
                      id: ds.id.label,
                      confidence: ds.confidence,
                    }))}
                    placeholder="Select or type domain spaces..."
                  />
                </div>
              </CollapsibleContent>
            </Collapsible>

            <div className="space-y-2">
              <Label htmlFor="device-type">Device Type</Label>
              <SearchableSelect
                id="device-type"
                value={deviceType}
                onValueChange={formState.setDeviceType}
                options={deviceTypes}
                aiSuggestion={
                  suggestion
                    ? {
                        id: suggestion.deviceTypeId.id,
                        confidence: suggestion.deviceTypeId.confidence,
                      }
                    : undefined
                }
                disabled={!equipmentType}
                placeholder={
                  equipmentType
                    ? 'Select device type...'
                    : 'Select equipment type first...'
                }
                emptyText="No device types found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.deviceTypeId.confidence}
                />
              )}
            </div>

            <div className="space-y-2">
              <Label htmlFor="observable-property">Observable Property</Label>
              <SearchableSelect
                id="observable-property"
                value={observableProperty}
                onValueChange={formState.setObservableProperty}
                options={observableProperties}
                aiSuggestion={
                  suggestion
                    ? {
                        id: suggestion.propertyId.id,
                        confidence: suggestion.propertyId.confidence,
                      }
                    : undefined
                }
                disabled={!deviceType}
                placeholder={
                  deviceType
                    ? 'Select observable property...'
                    : 'Select device type first...'
                }
                emptyText="No observable properties found."
              />
              {suggestion && (
                <ConfidenceIndicator
                  confidence={suggestion.propertyId.confidence}
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
          <Button variant="outline" onClick={onSkip}>
            {mode === 'edit' ? 'Cancel' : 'Skip'}
          </Button>
          <Button onClick={handleConfirm} disabled={!isFormValid}>
            {mode === 'edit' ? 'Update' : 'Confirm'}
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
