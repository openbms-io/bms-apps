import { Badge } from '@/components/ui/badge'
import {
  Tooltip,
  TooltipContent,
  TooltipProvider,
  TooltipTrigger,
} from '@/components/ui/tooltip'
import type { SemanticEquipment } from '../adapters/ashrae-223p/schemas'
import { useTemplatesQuery } from '../api/queries/use-templates-query'
import { getMappingLabels } from '../utils/template-labels'

interface SemanticBadgeProps {
  mapping: SemanticEquipment
}

export function SemanticBadge({ mapping }: SemanticBadgeProps) {
  const { data: templates } = useTemplatesQuery()

  const labels = getMappingLabels({
    templates,
    equipmentTypeUrn: mapping.equipmentTypeId,
    deviceTypeUrn: mapping.deviceTypeId,
    propertyUrn: mapping.propertyId,
  })

  const tooltipText = `${labels.equipment} | ${labels.device} | ${labels.property}`

  return (
    <TooltipProvider>
      <Tooltip>
        <TooltipTrigger asChild>
          <Badge
            variant="outline"
            className="text-[10px] px-1 py-0 h-4 cursor-help"
          >
            🏷️
          </Badge>
        </TooltipTrigger>
        <TooltipContent>
          <p className="text-xs">{tooltipText}</p>
        </TooltipContent>
      </Tooltip>
    </TooltipProvider>
  )
}
