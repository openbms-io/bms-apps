import { Badge } from '@/components/ui/badge'
import {
  Tooltip,
  TooltipContent,
  TooltipProvider,
  TooltipTrigger,
} from '@/components/ui/tooltip'
import type { SemanticEquipment } from '../schemas'

interface Point223PBadgeProps {
  mapping: SemanticEquipment
}

export function Point223PBadge({ mapping }: Point223PBadgeProps) {
  // Format: "Equipment | Device | Property"
  // Example: "VAV Reheat Terminal Unit | Sensor | air-temperature"
  const tooltipText = `${mapping.equipmentType} | ${mapping.deviceType} | ${mapping.observableProperty}`

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
