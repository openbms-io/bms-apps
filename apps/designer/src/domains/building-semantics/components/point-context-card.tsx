import { Card, CardContent } from '@/components/ui/card'
import { Badge } from '@/components/ui/badge'
import type {
  BACnetPointData,
  BACnetControllerData,
} from '../adapters/ashrae-223p/schemas'

interface PointContextCardProps {
  point: BACnetPointData
  controller?: BACnetControllerData | null
}

export function PointContextCard({ point, controller }: PointContextCardProps) {
  const presentValue = point.discoveredProperties?.presentValue
  const units = point.discoveredProperties?.units
  const description = point.discoveredProperties?.description

  return (
    <Card>
      <CardContent className="pt-6">
        <div className="space-y-2">
          <div className="font-semibold text-lg">{point.name}</div>
          <div className="text-sm text-muted-foreground flex items-center gap-2 flex-wrap">
            <Badge variant="outline">
              {point.objectType}, {point.objectId}
            </Badge>
            {presentValue !== undefined && (
              <span>
                {typeof presentValue === 'number'
                  ? presentValue.toFixed(2)
                  : String(presentValue)}
                {units && ` ${units}`}
              </span>
            )}
            {controller && <Badge variant="secondary">{controller.name}</Badge>}
          </div>
          {description && (
            <div className="text-sm text-muted-foreground">{description}</div>
          )}
        </div>
      </CardContent>
    </Card>
  )
}
