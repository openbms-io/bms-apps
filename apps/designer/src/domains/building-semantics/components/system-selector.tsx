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
import type { AISuggestion } from '../types/ai-suggestion'
import { AiSuggestedBadge } from './ui/ai-suggested-badge'
import { AISuggestionIndicatorTooltip } from './ai-suggestion-indicator-tooltip'
import { SystemCreateModal } from './system-create-modal'

interface SystemSelectorProps {
  projectId: string
  systems: SystemSummaryDto[]
  selectedSystemId?: string
  onSystemSelect: (systemUri: string) => void
  onSystemCreated: (system: SystemSummaryDto) => void
  disabled: boolean
  templates: TemplateSystemDto[]
  isLoadingTemplates: boolean
  aiSuggestion?: AISuggestion
  isLoadingAi: boolean
  isLowConfidence: boolean
}

export function SystemSelector({
  projectId,
  systems,
  selectedSystemId,
  onSystemSelect,
  onSystemCreated,
  disabled,
  templates,
  isLoadingTemplates,
  aiSuggestion,
  isLoadingAi,
  isLowConfidence,
}: SystemSelectorProps) {
  const [isCreateModalOpen, setIsCreateModalOpen] = useState(false)

  const handleSystemCreated = (system: SystemSummaryDto) => {
    onSystemCreated(system)
    setIsCreateModalOpen(false)
    onSystemSelect(system.systemUri)
  }

  const isAiSuggestionSelected = selectedSystemId === aiSuggestion?.selectedId

  return (
    <div className="space-y-2">
      <div className="flex gap-2">
        <div className="flex-1 flex items-center gap-2">
          <Select
            value={selectedSystemId}
            onValueChange={onSystemSelect}
            disabled={disabled}
          >
            <SelectTrigger className="flex-1">
              <SelectValue placeholder="Select system instance..." />
            </SelectTrigger>
            <SelectContent>
              {systems.map((system) => {
                const isAiSuggested =
                  system.systemUri === aiSuggestion?.selectedId
                return (
                  <SelectItem key={system.systemUri} value={system.systemUri}>
                    <div className="flex items-center gap-2">
                      <AiSuggestedBadge show={isAiSuggested} />
                      <span>
                        {system.label}
                        {system.templateId ? ` (${system.templateId})` : ''}
                      </span>
                    </div>
                  </SelectItem>
                )
              })}
            </SelectContent>
          </Select>
        </div>

        <Button
          variant="outline"
          size="icon"
          onClick={() => setIsCreateModalOpen(true)}
          disabled={disabled}
          title="Create new system instance"
        >
          <Plus className="h-4 w-4" />
        </Button>

        <AISuggestionIndicatorTooltip
          aiSuggestion={aiSuggestion}
          isLoading={isLoadingAi}
          isSelected={isAiSuggestionSelected}
        />

        <SystemCreateModal
          projectId={projectId}
          open={isCreateModalOpen}
          onOpenChange={setIsCreateModalOpen}
          onSystemCreated={handleSystemCreated}
          templates={templates}
          isLoadingTemplates={isLoadingTemplates}
        />
      </div>

      {isLowConfidence && !selectedSystemId && (
        <p className="text-xs text-amber-600">
          No strong match found. Consider creating a new system from a template.
        </p>
      )}
    </div>
  )
}
