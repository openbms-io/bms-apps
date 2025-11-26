import { useEffect, useState, useCallback } from 'react'
import { useFlowStore } from '@/store/use-flow-store'

interface IotDevice {
  organizationId: string
  siteId: string
  id: string
}

interface UseWorkflowLoaderParams {
  orgId: string
  siteId: string
  projectId: string
  iotDevice: IotDevice | undefined
  isLoadingProject: boolean
}

export function useWorkflowLoader({
  orgId,
  siteId,
  projectId,
  iotDevice,
  isLoadingProject,
}: UseWorkflowLoaderParams) {
  const loadWorkflowIntoCanvas = useFlowStore((s) => s.loadWorkflowIntoCanvas)
  const showError = useFlowStore((s) => s.showError)
  const startMqtt = useFlowStore((s) => s.startMqtt)
  const stopMqtt = useFlowStore((s) => s.stopMqtt)
  const clearAllNodes = useFlowStore((s) => s.clearAllNodes)

  const [isLoading, setIsLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)

  // MQTT lifecycle management
  useEffect(() => {
    if (!iotDevice) return

    startMqtt({
      organizationId: iotDevice.organizationId,
      siteId: iotDevice.siteId,
      iotDeviceId: iotDevice.id,
    })

    return () => {
      clearAllNodes()
      stopMqtt()
    }
  }, [
    iotDevice?.organizationId,
    iotDevice?.siteId,
    iotDevice?.id,
    startMqtt,
    stopMqtt,
    clearAllNodes,
    iotDevice,
  ])

  const doLoad = useCallback(async () => {
    if (isLoadingProject) {
      setIsLoading(true)
      return
    }

    setIsLoading(true)
    setError(null)
    try {
      await loadWorkflowIntoCanvas({ orgId, siteId, projectId })
    } catch (e) {
      const msg = e instanceof Error ? e.message : 'Failed to load workflow'
      setError(msg)
      showError('Load Failed', msg)
    } finally {
      setIsLoading(false)
    }
  }, [
    loadWorkflowIntoCanvas,
    orgId,
    siteId,
    projectId,
    showError,
    isLoadingProject,
  ])

  // Load workflow when ready
  useEffect(() => {
    doLoad()
  }, [doLoad])

  return {
    isLoading,
    error,
    retry: doLoad,
  }
}
