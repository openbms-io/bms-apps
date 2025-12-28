import 'server-only'

import { createAnthropic } from '@ai-sdk/anthropic'
import { createOpenAI } from '@ai-sdk/openai'

export type AIProvider = 'anthropic' | 'openai'

export function getProvider(): AIProvider {
  const provider = process.env.AI_PROVIDER ?? 'anthropic'

  if (provider !== 'anthropic' && provider !== 'openai') {
    throw new Error(
      `Invalid AI_PROVIDER: ${provider}. Must be "anthropic" or "openai"`
    )
  }

  return provider
}

export function getAIModel() {
  const provider = getProvider()
  const modelId = process.env.AI_MODEL

  if (!modelId) {
    throw new Error('AI_MODEL environment variable is required')
  }

  console.log(`[AI Client] Using provider: ${provider}, model: ${modelId}`)

  if (provider === 'anthropic') {
    const anthropic = createAnthropic()
    return anthropic(modelId)
  }

  const openai = createOpenAI()
  return openai(modelId)
}
