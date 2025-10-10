'use client'

import { useTreeUIStore } from '@/store/use-tree-ui-store'

export function PointPropertiesContainer() {
  const selectedPointId = useTreeUIStore((state) => state.selectedPointId)

  // Phase 1: No points yet, will implement in Phase 2 when we have MQTT get_config
  if (!selectedPointId) {
    return (
      <div className="p-4 text-center text-muted-foreground">
        <p className="text-sm">Select a point to view its properties</p>
      </div>
    )
  }

  return (
    <div className="p-4 text-center text-muted-foreground">
      <p className="text-sm">Point properties will be available in Phase 2</p>
      <p className="text-xs mt-2">Selected ID: {selectedPointId}</p>
    </div>
  )
}
