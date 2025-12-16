'use client'

import {
  memo,
  useState,
  useCallback,
  useMemo,
  Fragment,
  useEffect,
} from 'react'
import {
  Handle,
  Position,
  NodeProps,
  useUpdateNodeInternals,
} from '@xyflow/react'
import { useShallow } from 'zustand/react/shallow'
import { Card } from '@/components/ui/card'
import { Badge } from '@/components/ui/badge'
import { Button } from '@/components/ui/button'
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu'
import { Plus, X, Settings } from 'lucide-react'
import type {
  ControlSequenceInputHandle,
  ControlSequenceOutputHandle,
  SequenceType,
} from '@/domains/control-sequence/sequence-types'
import type { InputCategory, OutputCategory } from '@/domains/control-sequence'
import { ControlSequenceNodeData } from '@/types/node-data-types'
import { MessageValue } from '@/types/infrastructure'
import { useFlowStore } from '@/store/use-flow-store'
import {
  ControlSequenceHandles,
  ComputedOutputs,
} from '@/lib/data-nodes/base-control-sequence-node'
import { camelToLabel } from '@/lib/utils'
import { G36ConfigurationPanel } from '@/components/panels/g36-configuration-panel'

interface ControlSequenceNodeConfig {
  sequenceType: SequenceType
  badgeLabel: string
  defaultLabel: string
  allInputs: readonly ControlSequenceInputHandle[]
  allOutputs: readonly ControlSequenceOutputHandle[]
  requiredInputs: readonly ControlSequenceInputHandle[]
}

function formatOutputValue(value: MessageValue): string {
  if (typeof value === 'number') {
    return value.toFixed(2)
  }
  if (typeof value === 'boolean') {
    return value ? 'true' : 'false'
  }
  return value
}

export function createControlSequenceNodeUI(config: ControlSequenceNodeConfig) {
  const ControlSequenceNode = memo(({ data, id }: NodeProps) => {
    const typedData = data as ControlSequenceNodeData
    const [isPanelOpen, setIsPanelOpen] = useState(false)

    const handles = useFlowStore(
      useShallow((state) => {
        const node = state.nodes.find((n) => n.id === id)
        return (node?.data?.handles ??
          typedData.handles) as ControlSequenceHandles
      })
    )

    const computedOutputs = useFlowStore(
      useShallow((state) => {
        const node = state.nodes.find((n) => n.id === id)
        const nodeData = node?.data as ControlSequenceNodeData | undefined
        return (nodeData?.metadata?.computedOutputs ?? {}) as ComputedOutputs
      })
    )

    const inputValues = useFlowStore(
      useShallow((state) => {
        const node = state.nodes.find((n) => n.id === id)
        const nodeData = node?.data as ControlSequenceNodeData | undefined
        return (nodeData?.metadata?.inputValues ?? {}) as Record<
          string,
          MessageValue
        >
      })
    )

    const updateNode = useFlowStore((state) => state.updateNode)
    const saveProject = useFlowStore((state) => state.saveProject)

    const handlePanelClose = useCallback(() => setIsPanelOpen(false), [])

    const handleHandlesChange = useCallback(
      (visibleInputs: ControlSequenceInputHandle[]) => {
        updateNode({
          type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
          nodeId: id,
          handles: {
            ...handles,
            visibleInputs,
          },
        })
      },
      [updateNode, id, handles]
    )

    const updateNodeInternals = useUpdateNodeInternals()

    const visibleInputs = handles.visibleInputs
    const visibleOutputs = handles.visibleOutputs
    const parameterControlledInputs = handles.parameterControlledInputs ?? []
    const inputCategories = handles.inputCategories ?? {}
    const outputCategories = handles.outputCategories ?? {}

    // React Flow requires re-registration of handles when they are dynamically added/removed
    useEffect(() => {
      updateNodeInternals(id)
    }, [id, updateNodeInternals, visibleInputs, visibleOutputs])

    const groupedVisibleInputs = useMemo(() => {
      const groups: [InputCategory, ControlSequenceInputHandle[]][] = []
      for (const [category, categoryInputs] of Object.entries(
        inputCategories
      )) {
        const visible = (categoryInputs as ControlSequenceInputHandle[]).filter(
          (h) => visibleInputs.includes(h)
        )
        if (visible.length > 0) {
          groups.push([category as InputCategory, visible])
        }
      }
      return groups
    }, [inputCategories, visibleInputs])

    const groupedOptionalInputs = useMemo(() => {
      const groups: [InputCategory, ControlSequenceInputHandle[]][] = []
      for (const [category, categoryInputs] of Object.entries(
        inputCategories
      )) {
        const available = (
          categoryInputs as ControlSequenceInputHandle[]
        ).filter(
          (h) =>
            !visibleInputs.includes(h) && !parameterControlledInputs.includes(h)
        )
        if (available.length > 0) {
          groups.push([category as InputCategory, available])
        }
      }
      return groups
    }, [inputCategories, visibleInputs, parameterControlledInputs])

    const hasOptionalInputs = groupedOptionalInputs.length > 0

    const groupedVisibleOutputs = useMemo(() => {
      const groups: [OutputCategory, ControlSequenceOutputHandle[]][] = []
      for (const [category, categoryOutputs] of Object.entries(
        outputCategories
      )) {
        const visible = (
          categoryOutputs as ControlSequenceOutputHandle[]
        ).filter((h) => visibleOutputs.includes(h))
        if (visible.length > 0) {
          groups.push([category as OutputCategory, visible])
        }
      }
      return groups
    }, [outputCategories, visibleOutputs])

    const groupedOptionalOutputs = useMemo(() => {
      const groups: [OutputCategory, ControlSequenceOutputHandle[]][] = []
      for (const [category, categoryOutputs] of Object.entries(
        outputCategories
      )) {
        const available = (
          categoryOutputs as ControlSequenceOutputHandle[]
        ).filter((h) => !visibleOutputs.includes(h))
        if (available.length > 0) {
          groups.push([category as OutputCategory, available])
        }
      }
      return groups
    }, [outputCategories, visibleOutputs])

    const hasOptionalOutputs = groupedOptionalOutputs.length > 0

    const addInput = (handle: ControlSequenceInputHandle) => {
      updateNode({
        type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
        nodeId: id,
        handles: {
          ...handles,
          visibleInputs: [...visibleInputs, handle],
        },
      })
    }

    const removeInput = (handle: ControlSequenceInputHandle) => {
      updateNode({
        type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
        nodeId: id,
        handles: {
          ...handles,
          visibleInputs: visibleInputs.filter((h) => h !== handle),
        },
      })
    }

    const addOutput = (handle: ControlSequenceOutputHandle) => {
      updateNode({
        type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
        nodeId: id,
        handles: {
          ...handles,
          visibleOutputs: [...visibleOutputs, handle],
        },
      })
    }

    const removeOutput = (handle: ControlSequenceOutputHandle) => {
      updateNode({
        type: 'UPDATE_CONTROL_SEQUENCE_HANDLES',
        nodeId: id,
        handles: {
          ...handles,
          visibleOutputs: visibleOutputs.filter((h) => h !== handle),
        },
      })
    }

    const instanceId = typedData.metadata?.instanceId

    return (
      <>
        <Card className="min-w-[350px] border-2 border-primary/50">
          <div className="p-3">
            <div className="flex items-center justify-between mb-3">
              <span className="text-sm font-medium">
                {typedData.label ?? config.defaultLabel}
              </span>
              <div className="flex items-center gap-1">
                <Button
                  size="icon"
                  variant="ghost"
                  className="h-6 w-6"
                  onClick={() => setIsPanelOpen(true)}
                >
                  <Settings className="h-4 w-4" />
                </Button>
                <Badge variant="default" className="text-xs bg-primary">
                  {config.badgeLabel}
                </Badge>
              </div>
            </div>

            <div className="text-xs text-muted-foreground mb-3">
              Instance: {instanceId?.slice(0, 8)}...
            </div>

            <div className="flex gap-4">
              <div className="flex-1">
                <div className="text-xs font-medium text-muted-foreground mb-2">
                  Inputs
                </div>
                <div className="space-y-2">
                  {groupedVisibleInputs.map(([category, inputs]) => (
                    <Fragment key={category}>
                      <div className="text-xs text-muted-foreground/70">
                        {camelToLabel(category)}
                      </div>
                      <div className="space-y-1">
                        {inputs.map((handle) => {
                          const isRequired =
                            handles.requiredInputs.includes(handle)
                          const inputValue = inputValues[handle]
                          return (
                            <div
                              key={handle}
                              className="relative group flex items-center"
                            >
                              <Handle
                                type="target"
                                position={Position.Left}
                                id={handle}
                                className="!relative !top-auto !left-auto !transform-none w-2 h-2 bg-blue-500"
                                style={{ position: 'relative' }}
                              />
                              <div className="flex-1 text-sm ml-2">
                                {camelToLabel(handle)}
                                {isRequired && (
                                  <span className="text-destructive ml-0.5">
                                    *
                                  </span>
                                )}
                                {inputValue !== undefined && (
                                  <span className="text-xs text-muted-foreground ml-1">
                                    {formatOutputValue(inputValue)}
                                  </span>
                                )}
                              </div>
                              {!isRequired && (
                                <Button
                                  size="icon"
                                  variant="ghost"
                                  className="h-4 w-4 opacity-0 group-hover:opacity-100"
                                  onClick={() => removeInput(handle)}
                                >
                                  <X className="h-3 w-3" />
                                </Button>
                              )}
                            </div>
                          )
                        })}
                      </div>
                    </Fragment>
                  ))}
                </div>

                {hasOptionalInputs && (
                  <DropdownMenu>
                    <DropdownMenuTrigger asChild>
                      <Button
                        size="sm"
                        variant="ghost"
                        className="w-full mt-2 h-6 text-xs"
                      >
                        <Plus className="h-3 w-3 mr-1" />
                        Add Input
                      </Button>
                    </DropdownMenuTrigger>
                    <DropdownMenuContent className="max-h-[300px] overflow-y-auto">
                      {groupedOptionalInputs.map(
                        ([category, inputs], index) => (
                          <Fragment key={category}>
                            {index > 0 && <DropdownMenuSeparator />}
                            <DropdownMenuLabel className="text-xs font-semibold text-muted-foreground uppercase tracking-wide py-1">
                              {camelToLabel(category)}
                            </DropdownMenuLabel>
                            {inputs.map((handle) => (
                              <DropdownMenuItem
                                key={handle}
                                onClick={() => addInput(handle)}
                              >
                                {camelToLabel(handle)}
                              </DropdownMenuItem>
                            ))}
                          </Fragment>
                        )
                      )}
                    </DropdownMenuContent>
                  </DropdownMenu>
                )}
              </div>

              <div className="flex-1">
                <div className="text-xs font-medium text-muted-foreground mb-2">
                  Outputs
                </div>
                <div className="space-y-2">
                  {groupedVisibleOutputs.map(([category, outputs]) => (
                    <Fragment key={category}>
                      <div className="text-xs text-muted-foreground/70 text-right">
                        {camelToLabel(category)}
                      </div>
                      <div className="space-y-1">
                        {outputs.map((handle) => {
                          const outputValue = computedOutputs[handle]
                          return (
                            <div
                              key={handle}
                              className="relative group flex items-center justify-end"
                            >
                              <Button
                                size="icon"
                                variant="ghost"
                                className="h-4 w-4 opacity-0 group-hover:opacity-100"
                                onClick={() => removeOutput(handle)}
                              >
                                <X className="h-3 w-3" />
                              </Button>
                              <div className="flex-1 text-sm text-right mr-2">
                                {camelToLabel(handle)}
                                {outputValue !== undefined && (
                                  <span className="text-xs text-muted-foreground ml-1">
                                    {formatOutputValue(outputValue.value)}
                                  </span>
                                )}
                              </div>
                              <Handle
                                type="source"
                                position={Position.Right}
                                id={handle}
                                className="!relative !top-auto !right-auto !transform-none w-2 h-2 bg-green-500"
                                style={{ position: 'relative' }}
                              />
                            </div>
                          )
                        })}
                      </div>
                    </Fragment>
                  ))}
                </div>

                {hasOptionalOutputs && (
                  <DropdownMenu>
                    <DropdownMenuTrigger asChild>
                      <Button
                        size="sm"
                        variant="ghost"
                        className="w-full mt-2 h-6 text-xs"
                      >
                        <Plus className="h-3 w-3 mr-1" />
                        Add Output
                      </Button>
                    </DropdownMenuTrigger>
                    <DropdownMenuContent className="max-h-[300px] overflow-y-auto">
                      {groupedOptionalOutputs.map(
                        ([category, outputs], index) => (
                          <Fragment key={category}>
                            {index > 0 && <DropdownMenuSeparator />}
                            <DropdownMenuLabel className="text-xs font-semibold text-muted-foreground uppercase tracking-wide py-1">
                              {camelToLabel(category)}
                            </DropdownMenuLabel>
                            {outputs.map((handle) => (
                              <DropdownMenuItem
                                key={handle}
                                onClick={() => addOutput(handle)}
                              >
                                {camelToLabel(handle)}
                              </DropdownMenuItem>
                            ))}
                          </Fragment>
                        )
                      )}
                    </DropdownMenuContent>
                  </DropdownMenu>
                )}
              </div>
            </div>
          </div>
        </Card>

        {instanceId && (
          <G36ConfigurationPanel
            instanceId={instanceId}
            sequenceType={config.sequenceType}
            isOpen={isPanelOpen}
            onClose={handlePanelClose}
            onHandlesChange={handleHandlesChange}
            onSaveParameters={saveProject}
          />
        )}
      </>
    )
  })

  ControlSequenceNode.displayName = `ControlSequenceNode_${config.sequenceType}`
  return ControlSequenceNode
}
