'use client'

import { Button } from '@/components/ui/button'
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import { Plus } from 'lucide-react'
import { useState } from 'react'
import type {
  SystemSummaryDto,
  TemplateSystemDto,
} from '../api/generated/types.gen'
import { SystemCreateModal } from './system-create-modal'

interface SystemSelectorProps {
  projectId: string
  systems: SystemSummaryDto[]
  selectedSystemId?: string
  onSystemSelect: (systemUri: string) => void
  onSystemCreated: (system: SystemSummaryDto) => void
  disabled?: boolean
  templates?: TemplateSystemDto[]
  isLoadingTemplates?: boolean
}

export function SystemSelector({
  projectId,
  systems,
  selectedSystemId,
  onSystemSelect,
  onSystemCreated,
  disabled = false,
  templates = [],
  isLoadingTemplates = false,
}: SystemSelectorProps) {
  const [isCreateModalOpen, setIsCreateModalOpen] = useState(false)

  const handleSystemCreated = (system: SystemSummaryDto) => {
    onSystemCreated(system)
    setIsCreateModalOpen(false)
    onSystemSelect(system.systemUri)
  }

  return (
    <div className="flex gap-2">
      <Select
        value={selectedSystemId}
        onValueChange={onSystemSelect}
        disabled={disabled}
      >
        <SelectTrigger className="flex-1">
          <SelectValue placeholder="Select system instance..." />
        </SelectTrigger>
        <SelectContent>
          {systems.map((system) => (
            <SelectItem key={system.systemUri} value={system.systemUri}>
              {system.label}
              {system.templateId ? ` (${system.templateId})` : ''}
            </SelectItem>
          ))}
        </SelectContent>
      </Select>

      <Button
        variant="outline"
        size="icon"
        onClick={() => setIsCreateModalOpen(true)}
        disabled={disabled}
        title="Create new system instance"
      >
        <Plus className="h-4 w-4" />
      </Button>

      <SystemCreateModal
        projectId={projectId}
        open={isCreateModalOpen}
        onOpenChange={setIsCreateModalOpen}
        onSystemCreated={handleSystemCreated}
        templates={templates}
        isLoadingTemplates={isLoadingTemplates}
      />
    </div>
  )
}
