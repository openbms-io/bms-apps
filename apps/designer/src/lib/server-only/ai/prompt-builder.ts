import 'server-only'

import type { MemoryContext } from './memory-manager'
import type { StepType } from './step-registry'

export interface AIPointContext {
  point: {
    name: string
    objectType: string
    objectId: number
    controllerId: string
    description?: string
    units?: string
    presentValue?: unknown
    stateText?: string[]
  }
}

export interface SelectionContext {
  systemId?: string
  deviceId?: string
}

export interface AICandidate {
  id: string
  label: string
}

export interface PromptParams {
  step: StepType
  point: AIPointContext['point']
  candidates: AICandidate[]
  memoryContext: MemoryContext
  selectionContext?: SelectionContext
}

export interface IPromptBuilder {
  build(params: PromptParams): string
}

export class PromptBuilder implements IPromptBuilder {
  build({
    step,
    point,
    candidates,
    memoryContext,
    selectionContext,
  }: PromptParams): string {
    const sections: string[] = []

    sections.push(this.buildPointInfoSection({ point }))

    if (selectionContext) {
      const contextSection = this.buildSelectionContextSection({
        selectionContext,
      })
      if (contextSection) {
        sections.push(contextSection)
      }
    }

    sections.push(this.buildCandidatesSection({ candidates }))

    if (memoryContext.relevantMemories.length > 0) {
      sections.push(this.buildMemorySection({ memoryContext }))
    }

    sections.push(this.buildTaskSection({ step }))

    return sections.join('\n')
  }

  private buildPointInfoSection({
    point,
  }: {
    point: AIPointContext['point']
  }): string {
    const lines: string[] = []

    lines.push('## BACnet Point Information')
    lines.push(`Name: ${point.name}`)
    lines.push(`Object Type: ${point.objectType}`)
    lines.push(`Object ID: ${point.objectId}`)
    lines.push(`Controller ID: ${point.controllerId}`)

    if (point.description) {
      lines.push(`Description: ${point.description}`)
    }
    if (point.units) {
      lines.push(`Units: ${point.units}`)
    }
    if (point.presentValue !== undefined) {
      lines.push(`Present Value: ${JSON.stringify(point.presentValue)}`)
    }
    if (point.stateText && point.stateText.length > 0) {
      lines.push(`State Text: ${point.stateText.join(', ')}`)
    }

    return lines.join('\n')
  }

  private buildSelectionContextSection({
    selectionContext,
  }: {
    selectionContext: SelectionContext
  }): string | null {
    const lines: string[] = []

    if (selectionContext.systemId) {
      lines.push(`Selected System: ${selectionContext.systemId}`)
    }
    if (selectionContext.deviceId) {
      lines.push(`Selected Device: ${selectionContext.deviceId}`)
    }

    if (lines.length === 0) {
      return null
    }

    return ['', '## Selection Context', ...lines].join('\n')
  }

  private buildCandidatesSection({
    candidates,
  }: {
    candidates: AICandidate[]
  }): string {
    const candidateLines = candidates.map((c) => `- "${c.label}" (ID: ${c.id})`)
    return [
      '',
      '## Available Candidates',
      ...candidateLines,
      '',
      'IMPORTANT: When selecting, you MUST return the ID value (not the label).',
    ].join('\n')
  }

  private buildMemorySection({
    memoryContext,
  }: {
    memoryContext: MemoryContext
  }): string {
    const lines = memoryContext.relevantMemories.map(
      (memory) => `- ${memory.text}`
    )
    return ['', '## Previous Mapping Decisions', ...lines].join('\n')
  }

  private buildTaskSection({ step }: { step: StepType }): string {
    return [
      '',
      '## Task',
      `Select the best ${step} from the available candidates for this BACnet point.`,
    ].join('\n')
  }
}
