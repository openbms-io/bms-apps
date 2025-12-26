import 'server-only'

import { generateObject } from 'ai'
import { z } from 'zod'
import type { MemoryContext } from './memory-manager'
import { getAIModel } from './ai-client'

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

export interface StepSuggestion {
  selectedId: string
  confidence: number
  reasoning: string
  alternatives: Array<{ id: string; confidence: number }>
}

export const StepSuggestionSchema = z.object({
  selectedId: z.string(),
  confidence: z.number().min(0).max(1),
  reasoning: z.string(),
  alternatives: z.array(
    z.object({
      id: z.string(),
      confidence: z.number().min(0).max(1),
    })
  ),
})

export interface IObjectGenerator {
  generate(params: { system: string; prompt: string }): Promise<StepSuggestion>
}

export function createObjectGenerator(): IObjectGenerator {
  const model = getAIModel()

  return {
    async generate({ system, prompt }): Promise<StepSuggestion> {
      const result = await generateObject({
        model,
        schema: StepSuggestionSchema,
        system,
        prompt,
      })
      return result.object
    },
  }
}

type StepType = 'system' | 'device' | 'property'

const STEP_SYSTEM_PROMPTS: Record<StepType, string> = {
  system: `You are an expert in ASHRAE 223P semantic modeling for building automation systems.
Your task is to select the best ASHRAE 223P system template that matches a BACnet point.
Consider the point name pattern, object type, and any previous mapping decisions.
Return the most appropriate system ID from the provided candidates.`,
  device: `You are an expert in ASHRAE 223P semantic modeling for building automation systems.
Your task is to select the best device type within the chosen system for a BACnet point.
Consider the point's object type, units, and description to match the appropriate device.
Return the most appropriate device ID from the provided candidates.`,
  property: `You are an expert in ASHRAE 223P semantic modeling for building automation systems.
Your task is to select the best property (observable/actuatable) for a BACnet point.
Consider the point's units, present value type, and state text for the best match.
Return the most appropriate property ID from the provided candidates.`,
}

export class SuggestionEngine {
  private readonly generator: IObjectGenerator

  constructor(generator: IObjectGenerator) {
    this.generator = generator
  }

  async generateStepSuggestion({
    step,
    point,
    candidates,
    memoryContext,
    selectionContext,
  }: {
    step: StepType
    point: AIPointContext['point']
    candidates: string[]
    memoryContext: MemoryContext
    selectionContext?: { systemId?: string; deviceId?: string }
  }): Promise<StepSuggestion> {
    const system = STEP_SYSTEM_PROMPTS[step]
    const prompt = this.buildUserPrompt({
      step,
      point,
      candidates,
      memoryContext,
      selectionContext,
    })

    return this.generator.generate({ system, prompt })
  }

  private buildUserPrompt({
    step,
    point,
    candidates,
    memoryContext,
    selectionContext,
  }: {
    step: StepType
    point: AIPointContext['point']
    candidates: string[]
    memoryContext: MemoryContext
    selectionContext?: { systemId?: string; deviceId?: string }
  }): string {
    const sections: string[] = []

    sections.push('## BACnet Point Information')
    sections.push(`Name: ${point.name}`)
    sections.push(`Object Type: ${point.objectType}`)
    sections.push(`Object ID: ${point.objectId}`)
    sections.push(`Controller ID: ${point.controllerId}`)

    if (point.description) {
      sections.push(`Description: ${point.description}`)
    }
    if (point.units) {
      sections.push(`Units: ${point.units}`)
    }
    if (point.presentValue !== undefined) {
      sections.push(`Present Value: ${JSON.stringify(point.presentValue)}`)
    }
    if (point.stateText && point.stateText.length > 0) {
      sections.push(`State Text: ${point.stateText.join(', ')}`)
    }

    if (selectionContext) {
      sections.push('')
      sections.push('## Selection Context')
      if (selectionContext.systemId) {
        sections.push(`Selected System: ${selectionContext.systemId}`)
      }
      if (selectionContext.deviceId) {
        sections.push(`Selected Device: ${selectionContext.deviceId}`)
      }
    }

    sections.push('')
    sections.push('## Available Candidates')
    sections.push(candidates.join(', '))

    if (memoryContext.relevantMemories.length > 0) {
      sections.push('')
      sections.push('## Previous Mapping Decisions')
      for (const memory of memoryContext.relevantMemories) {
        sections.push(`- ${memory.text}`)
      }
    }

    sections.push('')
    sections.push(`## Task`)
    sections.push(
      `Select the best ${step} from the available candidates for this BACnet point.`
    )

    return sections.join('\n')
  }
}
