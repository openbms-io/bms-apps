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
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import { Loader2 } from 'lucide-react'
import { useState } from 'react'
import { createSystemApiV1ProjectsProjectIdSystemsPost } from '../api/generated/sdk.gen'
import type {
  SystemSummaryDto,
  TemplateSystemDto,
} from '../api/generated/types.gen'

interface SystemCreateModalProps {
  projectId: string
  open: boolean
  onOpenChange: (open: boolean) => void
  onSystemCreated: (system: SystemSummaryDto) => void
  templates?: TemplateSystemDto[]
  isLoadingTemplates?: boolean
}

export function SystemCreateModal({
  projectId,
  open,
  onOpenChange,
  onSystemCreated,
  templates = [],
  isLoadingTemplates = false,
}: SystemCreateModalProps) {
  const [selectedTemplateId, setSelectedTemplateId] = useState<string>('')
  const [label, setLabel] = useState('')
  const [isCreating, setIsCreating] = useState(false)
  const [error, setError] = useState<string | null>(null)

  const selectedTemplate = templates.find((t) => t.id === selectedTemplateId)

  const handleCreate = async () => {
    if (!selectedTemplateId || !label.trim()) {
      setError('Please select a template and provide a label')
      return
    }

    setIsCreating(true)
    setError(null)

    try {
      const response = await createSystemApiV1ProjectsProjectIdSystemsPost({
        path: { project_id: projectId },
        body: {
          templateId: selectedTemplateId,
          label: label.trim(),
        },
      })

      if (response.data) {
        const summary: SystemSummaryDto = {
          systemUri: response.data.systemUri,
          label: response.data.label,
          templateId: response.data.templateId,
        }
        onSystemCreated(summary)
        handleReset()
      }
    } catch (err) {
      setError(
        err instanceof Error ? err.message : 'Failed to create system instance'
      )
    } finally {
      setIsCreating(false)
    }
  }

  const handleReset = () => {
    setSelectedTemplateId('')
    setLabel('')
    setError(null)
  }

  const handleOpenChange = (newOpen: boolean) => {
    if (!newOpen && !isCreating) {
      handleReset()
    }
    onOpenChange(newOpen)
  }

  return (
    <Dialog open={open} onOpenChange={handleOpenChange}>
      <DialogContent className="sm:max-w-[500px]">
        <DialogHeader>
          <DialogTitle>Create System Instance</DialogTitle>
          <DialogDescription>
            Create a reusable system instance from an ASHRAE 223P template. You
            can map multiple BACnet points to this system.
          </DialogDescription>
        </DialogHeader>

        <div className="grid gap-4 py-4">
          <div className="grid gap-2">
            <Label htmlFor="template">Template</Label>
            <Select
              value={selectedTemplateId}
              onValueChange={setSelectedTemplateId}
              disabled={isLoadingTemplates || isCreating}
            >
              <SelectTrigger id="template">
                <SelectValue placeholder="Select ASHRAE 223P template..." />
              </SelectTrigger>
              <SelectContent>
                {templates.map((template) => (
                  <SelectItem key={template.id} value={template.id}>
                    {template.label} ({template.id})
                  </SelectItem>
                ))}
              </SelectContent>
            </Select>
          </div>

          <div className="grid gap-2">
            <Label htmlFor="label">Label</Label>
            <Input
              id="label"
              placeholder="e.g., VAV-Floor3-Zone5"
              value={label}
              onChange={(e) => setLabel(e.target.value)}
              disabled={isCreating}
            />
            <p className="text-sm text-muted-foreground">
              Custom label to identify this system instance
            </p>
          </div>

          {selectedTemplate && (
            <div className="rounded-lg border p-3 bg-muted/50">
              <h4 className="text-sm font-medium mb-2">Template Preview</h4>
              <div className="text-sm text-muted-foreground space-y-1">
                <div>
                  <strong>Devices:</strong> {selectedTemplate.devices.length}
                </div>
                {selectedTemplate.description && (
                  <div>{selectedTemplate.description}</div>
                )}
              </div>
            </div>
          )}

          {error && (
            <div className="text-sm text-destructive bg-destructive/10 border border-destructive/20 rounded-md p-3">
              {error}
            </div>
          )}
        </div>

        <DialogFooter>
          <Button
            variant="outline"
            onClick={() => handleOpenChange(false)}
            disabled={isCreating}
          >
            Cancel
          </Button>
          <Button
            onClick={handleCreate}
            disabled={isCreating || !label.trim() || !selectedTemplateId}
          >
            {isCreating && <Loader2 className="mr-2 h-4 w-4 animate-spin" />}
            Create System
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
