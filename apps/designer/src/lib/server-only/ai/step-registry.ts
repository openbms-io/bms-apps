import 'server-only'

import { type StepType } from '@/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'

export type { StepType }

export interface IStepRegistry {
  getSystemPrompt(params: { step: StepType }): string
}

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

export class StepRegistry implements IStepRegistry {
  getSystemPrompt({ step }: { step: StepType }): string {
    return STEP_SYSTEM_PROMPTS[step]
  }
}
