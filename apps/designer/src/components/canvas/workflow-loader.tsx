'use client'

import { Loader2, AlertTriangle } from 'lucide-react'
import { Button } from '@/components/ui/button'
import { useProject } from '@/hooks/use-projects'
import { useIotDevice } from '@/hooks/use-iot-device'
import { useWorkflowLoader } from '@/hooks/use-workflow-loader'

interface WorkflowLoaderProps {
  orgId: string
  siteId: string
  projectId: string
}

export function WorkflowLoader({
  orgId,
  siteId,
  projectId,
}: WorkflowLoaderProps) {
  const { data: project, isLoading: isLoadingProject } = useProject({
    orgId,
    siteId,
    projectId,
  })
  const { data: iotDevice } = useIotDevice(
    orgId,
    siteId,
    projectId,
    project?.iotDeviceId ?? undefined
  )

  const { isLoading, error, retry } = useWorkflowLoader({
    orgId,
    siteId,
    projectId,
    iotDevice,
    isLoadingProject,
  })

  return (
    <>
      {isLoading && (
        <div className="fixed inset-0 z-40 flex items-center justify-center bg-background/60 backdrop-blur-[1px]">
          <div className="flex items-center gap-3 rounded-md border border-border bg-card px-4 py-3 shadow-sm">
            <Loader2 className="h-5 w-5 animate-spin" />
            <span className="text-sm">Loading workflow…</span>
          </div>
        </div>
      )}

      {!isLoading && error && (
        <div className="fixed top-16 right-6 z-40 max-w-sm rounded-md border border-border bg-card p-4 shadow-md">
          <div className="flex items-start gap-3">
            <AlertTriangle className="h-5 w-5 text-destructive mt-0.5" />
            <div className="flex-1">
              <div className="font-medium text-sm">Failed to load workflow</div>
              <div className="text-xs text-muted-foreground mt-1 break-words">
                {error}
              </div>
              <div className="mt-3 flex gap-2">
                <Button size="sm" onClick={() => void retry()}>
                  Retry
                </Button>
              </div>
            </div>
          </div>
        </div>
      )}
    </>
  )
}
