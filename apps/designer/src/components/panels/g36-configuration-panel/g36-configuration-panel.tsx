'use client'

import { useState, useEffect } from 'react'
import { Loader2 } from 'lucide-react'
import {
  Sheet,
  SheetContent,
  SheetHeader,
  SheetTitle,
  SheetFooter,
} from '@/components/ui/sheet'
import { Button } from '@/components/ui/button'
import { ScrollArea } from '@/components/ui/scroll-area'
import { Badge } from '@/components/ui/badge'
import {
  useInstanceQuery,
  useDefaultParametersQuery,
} from '@/domains/control-sequence/api/queries'
import {
  useUpdateInstanceMutation,
  useConvertParametersMutation,
} from '@/domains/control-sequence/api/mutations'
import type {
  ReheatParameters,
  ParameterCategory,
  TemperatureUnit,
  AirflowUnit,
  ReheatOutputName,
} from '@/domains/control-sequence/api/generated/types.gen'
import type {
  ControlSequenceInputHandle,
  ControlSequenceOutputHandle,
  SequenceType,
} from '@/domains/control-sequence'
import {
  REHEAT_REQUIRED_INPUTS,
  REHEAT_ALL_OUTPUTS,
  SEQUENCE_DROPDOWN_FIELDS,
} from '@/domains/control-sequence'
import { CollapsibleSection, CategoryFields } from './components'
import { camelToLabel } from '@/lib/utils'
import { type G36ConfigurationPanelProps, BASIC_CATEGORIES } from './types'

type ParameterToOutputsMap = Record<string, ReheatOutputName[] | undefined>
type ParameterToInputsMap = Record<string, string[] | undefined>

function findControllingParameter({
  output,
  parameterToRequiredOutputs,
}: {
  output: ReheatOutputName
  parameterToRequiredOutputs: ParameterToOutputsMap
}): keyof ReheatParameters | undefined {
  for (const [param, outputs] of Object.entries(parameterToRequiredOutputs)) {
    if (outputs?.includes(output)) {
      return param as keyof ReheatParameters
    }
  }
  return undefined
}

function computeVisibleInputs({
  params,
  parameterToRequiredInputs,
}: {
  params: ReheatParameters
  parameterToRequiredInputs: ParameterToInputsMap
}): ControlSequenceInputHandle[] {
  const conditionalInputs: ControlSequenceInputHandle[] = []

  for (const [param, inputs] of Object.entries(parameterToRequiredInputs)) {
    if (params[param as keyof ReheatParameters] && inputs) {
      conditionalInputs.push(...(inputs as ControlSequenceInputHandle[]))
    }
  }

  return [
    ...REHEAT_REQUIRED_INPUTS,
    ...conditionalInputs,
  ] as ControlSequenceInputHandle[]
}

function computeVisibleOutputs({
  params,
  parameterToRequiredOutputs,
}: {
  params: ReheatParameters
  parameterToRequiredOutputs: ParameterToOutputsMap
}): ControlSequenceOutputHandle[] {
  return REHEAT_ALL_OUTPUTS.filter((output) => {
    const controllingParam = findControllingParameter({
      output,
      parameterToRequiredOutputs,
    })

    const isAlwaysVisible = controllingParam === undefined
    const isEnabledByParameter =
      controllingParam && params[controllingParam] === true

    return isAlwaysVisible || isEnabledByParameter
  }) as ControlSequenceOutputHandle[]
}

export function G36ConfigurationPanel({
  instanceId,
  sequenceType,
  isOpen,
  onClose,
  onHandlesChange,
  onSaveParameters,
}: G36ConfigurationPanelProps) {
  const dropdownFields = SEQUENCE_DROPDOWN_FIELDS[sequenceType]
  const { data, isLoading, isError, error } = useInstanceQuery({ instanceId })
  const { refetch: refetchDefaults } = useDefaultParametersQuery({
    sequenceType: sequenceType as SequenceType,
    enabled: false,
  })
  const updateMutation = useUpdateInstanceMutation()
  const convertMutation = useConvertParametersMutation()
  const [localParams, setLocalParams] = useState<ReheatParameters>({})

  useEffect(() => {
    if (data?.parameters) {
      setLocalParams(data.parameters)
    }
  }, [data?.parameters])

  const parameterToRequiredInputs = data?.parameterToRequiredInputs ?? {}
  const parameterToRequiredOutputs = data?.parameterToRequiredOutputs ?? {}

  const handleParameterChange = <K extends keyof ReheatParameters>(
    key: K,
    value: ReheatParameters[K]
  ) => {
    setLocalParams((prev) => ({ ...prev, [key]: value }))
  }

  const handleUnitChange = async (
    unitType: 'temperatureUnit' | 'airflowUnit',
    newValue: TemperatureUnit | AirflowUnit
  ) => {
    const targetTempUnit =
      unitType === 'temperatureUnit'
        ? (newValue as TemperatureUnit)
        : localParams.temperatureUnit!
    const targetAirflowUnit =
      unitType === 'airflowUnit'
        ? (newValue as AirflowUnit)
        : localParams.airflowUnit!

    const converted = await convertMutation.mutateAsync({
      sequenceType: sequenceType as SequenceType,
      parameters: localParams,
      targetTemperatureUnit: targetTempUnit,
      targetAirflowUnit: targetAirflowUnit,
    })
    setLocalParams(converted)
  }

  const handleResetDefaults = async () => {
    const { data: defaults } = await refetchDefaults()
    if (defaults) {
      setLocalParams(defaults)
    }
  }

  const handleSave = async () => {
    try {
      await updateMutation.mutateAsync({
        instanceId,
        parameters: localParams,
      })

      onHandlesChange({
        visibleInputs: computeVisibleInputs({
          params: localParams,
          parameterToRequiredInputs,
        }),
        visibleOutputs: computeVisibleOutputs({
          params: localParams,
          parameterToRequiredOutputs,
        }),
        parameters: localParams as Record<string, unknown>,
      })
      await onSaveParameters()
      onClose()
    } catch {
      // Error handled by mutation
    }
  }

  const handleCancel = () => {
    if (data?.parameters) {
      setLocalParams(data.parameters)
    }
    onClose()
  }

  if (!isOpen) return null

  const categories = data?.categories ?? {}
  const basicCategories = Object.entries(categories)
    .filter(([cat]) => BASIC_CATEGORIES.includes(cat as ParameterCategory))
    .sort(
      ([a], [b]) =>
        BASIC_CATEGORIES.indexOf(a as ParameterCategory) -
        BASIC_CATEGORIES.indexOf(b as ParameterCategory)
    ) as [ParameterCategory, string[]][]
  const advancedCategories = Object.entries(categories).filter(
    ([cat]) => !BASIC_CATEGORIES.includes(cat as ParameterCategory)
  ) as [ParameterCategory, string[]][]

  return (
    <Sheet open={isOpen} onOpenChange={handleCancel}>
      <SheetContent className="w-[400px] sm:w-[480px] flex flex-col">
        <SheetHeader>
          <SheetTitle className="flex items-center gap-2">
            G36 VAV Reheat Configuration
            <Badge variant="outline" className="text-xs">
              {instanceId.slice(0, 8)}...
            </Badge>
          </SheetTitle>
        </SheetHeader>

        <ScrollArea className="flex-1 mt-6 pr-4">
          {isLoading && (
            <div className="flex items-center justify-center py-8">
              <Loader2 className="h-6 w-6 animate-spin text-muted-foreground" />
            </div>
          )}

          {isError && (
            <div className="text-destructive text-sm py-4">
              Failed to load parameters: {error?.message}
            </div>
          )}

          {data && (
            <div className="space-y-6 pb-4">
              <CollapsibleSection title="Basic Settings" defaultOpen>
                {basicCategories.map(([category, fields]) => (
                  <div key={category} className="space-y-3">
                    <div className="text-xs font-medium text-muted-foreground uppercase tracking-wide">
                      {camelToLabel(category)}
                    </div>
                    <CategoryFields
                      category={category}
                      fields={fields}
                      parameters={localParams}
                      onParameterChange={handleParameterChange}
                      onUnitChange={handleUnitChange}
                      dropdownFields={dropdownFields}
                    />
                  </div>
                ))}
              </CollapsibleSection>

              {advancedCategories.length > 0 && (
                <CollapsibleSection
                  title="Advanced Settings"
                  badge={`${advancedCategories.reduce(
                    (acc, [, f]) => acc + f.length,
                    0
                  )} params`}
                >
                  {advancedCategories.map(([category, fields]) => (
                    <div key={category} className="space-y-3">
                      <div className="text-xs font-medium text-muted-foreground uppercase tracking-wide">
                        {camelToLabel(category)}
                      </div>
                      <CategoryFields
                        category={category}
                        fields={fields}
                        parameters={localParams}
                        onParameterChange={handleParameterChange}
                        onUnitChange={handleUnitChange}
                        dropdownFields={dropdownFields}
                      />
                    </div>
                  ))}
                </CollapsibleSection>
              )}
            </div>
          )}
        </ScrollArea>

        <SheetFooter className="border-t pt-4 mt-auto">
          <Button
            variant="ghost"
            onClick={handleResetDefaults}
            disabled={isLoading || convertMutation.isPending}
          >
            Reset Defaults
          </Button>
          <div className="flex-1" />
          <Button variant="outline" onClick={handleCancel}>
            Cancel
          </Button>
          <Button
            onClick={handleSave}
            disabled={updateMutation.isPending || isLoading}
          >
            {updateMutation.isPending && (
              <Loader2 className="h-4 w-4 animate-spin mr-2" />
            )}
            Save
          </Button>
        </SheetFooter>
      </SheetContent>
    </Sheet>
  )
}
