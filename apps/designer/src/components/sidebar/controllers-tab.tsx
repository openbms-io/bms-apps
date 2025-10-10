'use client'

import { ControllersTreeContainer } from '@/containers/controllers-tree-container'
import { PointPropertiesContainer } from '@/containers/point-properties-container'
import { useInfrastructureStore } from '@/store/use-infrastructure-store'

interface ControllersTabProps {
  orgId: string
  siteId: string
  projectId: string
}

export function ControllersTab({
  orgId,
  siteId,
  projectId,
}: ControllersTabProps) {
  const selectedPointId = useInfrastructureStore(
    (state) => state.selectedPointId
  )

  return (
    <div className="h-full flex flex-col">
      {/* Tree view takes most of the space */}
      <div className="flex-1 min-h-0">
        <ControllersTreeContainer
          orgId={orgId}
          siteId={siteId}
          projectId={projectId}
        />
      </div>

      {/* Properties panel shows when a point is selected */}
      {selectedPointId && (
        <div className="h-1/3 border-t overflow-y-auto">
          <PointPropertiesContainer />
        </div>
      )}
    </div>
  )
}
