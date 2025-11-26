'use client'

import { Button } from '@/components/ui/button'
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog'
import { Label } from '@/components/ui/label'
import { Loader2 } from 'lucide-react'
import type { TemplateSystemDto } from '../../api/generated/types.gen'
import type { BuildingSemanticsBacnetConfig } from '../../types'
import { DeviceSelector } from '../device-selector'
import { PropertySelector } from '../property-selector'
import { SystemSelector } from '../system-selector'
import { ShaclValidationErrorModal } from '../shacl-validation-error-modal'
import { useBuildingSemanticsForm } from './use-building-semantics-form'

interface BuildingSemanticsModalProps {
  projectId: string
  open: boolean
  bacnetPointId: string
  bacnetObjectType: string
  buildingSemanticsBacnetConfig: BuildingSemanticsBacnetConfig
  pointLabel?: string
  templates?: TemplateSystemDto[]
  onSaved: () => void
  onSkip?: () => void
  onOpenChange: (open: boolean) => void
}

export function BuildingSemanticsModal({
  projectId,
  open,
  bacnetPointId,
  bacnetObjectType,
  buildingSemanticsBacnetConfig,
  pointLabel,
  templates = [],
  onSaved,
  onSkip,
  onOpenChange,
}: BuildingSemanticsModalProps) {
  const { state, actions, data, validation, loading } =
    useBuildingSemanticsForm({
      projectId,
      bacnetPointId,
      bacnetObjectType,
      buildingSemanticsBacnetConfig,
      open,
      onSaved,
      onOpenChange,
    })

  return (
    <>
      <Dialog open={open} onOpenChange={onOpenChange}>
        <DialogContent className="sm:max-w-[600px]">
          <DialogHeader>
            <DialogTitle>Map BACnet Point to ASHRAE 223P</DialogTitle>
            <DialogDescription>
              {pointLabel && (
                <span className="block font-medium text-foreground">
                  {pointLabel}
                </span>
              )}
              <span className="block text-xs">
                {bacnetPointId} ({bacnetObjectType})
              </span>
            </DialogDescription>
          </DialogHeader>

          <div className="grid gap-4 py-4">
            <div className="grid gap-2">
              <Label>System Instance</Label>
              <SystemSelector
                projectId={projectId}
                systems={data.systems}
                selectedSystemId={state.selectedSystemUri}
                onSystemSelect={actions.selectSystem}
                onSystemCreated={actions.addLocalSystem}
                disabled={loading.isLoadingSystems}
                templates={templates}
                isLoadingTemplates={false}
              />
              <p className="text-xs text-muted-foreground">
                Select an existing system or create a new one from a template
              </p>
            </div>

            <div className="grid gap-2">
              <Label>Device</Label>
              <DeviceSelector
                devices={data.devices}
                selectedDeviceId={state.selectedDeviceUri}
                onDeviceSelect={actions.selectDevice}
                disabled={!state.selectedSystemUri}
                isLoading={loading.isLoadingDevices}
              />
              <p className="text-xs text-muted-foreground">
                Select a device from the system
              </p>
            </div>

            <div className="grid gap-2">
              <Label>Property</Label>
              <PropertySelector
                properties={data.properties}
                selectedPropertyId={state.selectedPropertyUri}
                onPropertySelect={actions.selectProperty}
                disabled={!state.selectedDeviceUri}
                isLoading={loading.isLoadingProperties}
                bacnetObjectType={bacnetObjectType}
              />
              <p className="text-xs text-muted-foreground">
                Select a property (automatically filtered by {bacnetObjectType})
              </p>
            </div>
          </div>

          <DialogFooter>
            <Button
              variant="outline"
              onClick={() => onOpenChange(false)}
              disabled={loading.isSaving}
            >
              Cancel
            </Button>
            {onSkip && (
              <Button
                variant="secondary"
                onClick={() => {
                  onSkip()
                  onOpenChange(false)
                }}
                disabled={loading.isSaving}
              >
                Skip
              </Button>
            )}
            <Button
              onClick={actions.handleSave}
              disabled={!validation.isFormValid || loading.isSaving}
            >
              {loading.isSaving && (
                <Loader2 className="mr-2 h-4 w-4 animate-spin" />
              )}
              Save Mapping
            </Button>
          </DialogFooter>
        </DialogContent>
      </Dialog>

      <ShaclValidationErrorModal
        open={state.showValidationModal}
        errors={state.validationErrors}
        onOpenChange={(open) => {
          if (!open) {
            actions.hideValidationModal()
          }
        }}
      />
    </>
  )
}
