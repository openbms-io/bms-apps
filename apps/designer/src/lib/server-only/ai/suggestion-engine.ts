import 'server-only'

import { generateObject } from 'ai'
import { z } from 'zod'
import type { MemoryContext } from './memory-manager'
import { getAIModel } from './ai-client'
import {
  PromptBuilder,
  type IPromptBuilder,
  type AIPointContext,
  type AICandidate,
  type SelectionContext,
} from './prompt-builder'
import {
  StepRegistry,
  type IStepRegistry,
  type StepType,
} from './step-registry'

export type { AIPointContext, AICandidate, SelectionContext, StepType }

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
        maxRetries: 0,
        temperature: 0,
      })
      return result.object
    },
  }
}

export interface GenerateStepSuggestionParams {
  step: StepType
  point: AIPointContext['point']
  candidates: AICandidate[]
  memoryContext: MemoryContext
  selectionContext?: SelectionContext
}

export class SuggestionEngine {
  private readonly generator: IObjectGenerator
  private readonly stepRegistry: IStepRegistry
  private readonly promptBuilder: IPromptBuilder

  constructor(
    generator: IObjectGenerator,
    stepRegistry: IStepRegistry = new StepRegistry(),
    promptBuilder: IPromptBuilder = new PromptBuilder()
  ) {
    this.generator = generator
    this.stepRegistry = stepRegistry
    this.promptBuilder = promptBuilder
  }

  async generateStepSuggestion({
    step,
    point,
    candidates,
    memoryContext,
    selectionContext,
  }: GenerateStepSuggestionParams): Promise<StepSuggestion> {
    const start = performance.now()

    const systemPrompt = this.stepRegistry.getSystemPrompt({ step })
    const userPrompt = this.promptBuilder.build({
      step,
      point,
      candidates,
      memoryContext,
      selectionContext,
    })

    const result = await this.generator.generate({
      system: systemPrompt,
      prompt: userPrompt,
    })

    const duration = performance.now() - start
    console.log(
      `[AI SDK] generateStepSuggestion (${step}) took ${duration.toFixed(0)}ms`
    )

    return result
  }
}
