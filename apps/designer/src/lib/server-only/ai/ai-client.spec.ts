jest.mock('server-only', () => ({}))

jest.mock('@ai-sdk/anthropic', () => ({
  createAnthropic: () => (model: string) => ({
    provider: 'anthropic',
    model,
  }),
}))

jest.mock('@ai-sdk/openai', () => ({
  createOpenAI: () => (model: string) => ({
    provider: 'openai',
    model,
  }),
}))

import { getProvider, getAIModel } from './ai-client'

describe('AI Client', () => {
  const originalEnv = process.env

  beforeEach(() => {
    process.env = { ...originalEnv }
    delete process.env.AI_PROVIDER
    delete process.env.AI_MODEL
  })

  afterAll(() => {
    process.env = originalEnv
  })

  describe('getProvider', () => {
    it('returns anthropic by default when AI_PROVIDER not set', () => {
      expect(getProvider()).toBe('anthropic')
    })

    it('returns anthropic when AI_PROVIDER=anthropic', () => {
      process.env.AI_PROVIDER = 'anthropic'
      expect(getProvider()).toBe('anthropic')
    })

    it('returns openai when AI_PROVIDER=openai', () => {
      process.env.AI_PROVIDER = 'openai'
      expect(getProvider()).toBe('openai')
    })

    it('throws error for invalid AI_PROVIDER value', () => {
      process.env.AI_PROVIDER = 'invalid-provider'
      expect(() => getProvider()).toThrow(
        'Invalid AI_PROVIDER: invalid-provider. Must be "anthropic" or "openai"'
      )
    })
  })

  describe('getAIModel', () => {
    it('throws error when AI_MODEL not set', () => {
      expect(() => getAIModel()).toThrow(
        'AI_MODEL environment variable is required'
      )
    })

    it('uses Anthropic provider when AI_PROVIDER=anthropic', () => {
      process.env.AI_PROVIDER = 'anthropic'
      process.env.AI_MODEL = 'claude-3-5-sonnet-20241022'

      const model = getAIModel()

      expect(model).toEqual({
        provider: 'anthropic',
        model: 'claude-3-5-sonnet-20241022',
      })
    })

    it('uses OpenAI provider when AI_PROVIDER=openai', () => {
      process.env.AI_PROVIDER = 'openai'
      process.env.AI_MODEL = 'gpt-4o'

      const model = getAIModel()

      expect(model).toEqual({
        provider: 'openai',
        model: 'gpt-4o',
      })
    })

    it('uses Anthropic provider by default when AI_PROVIDER not set', () => {
      process.env.AI_MODEL = 'claude-3-5-sonnet-20241022'

      const model = getAIModel()

      expect(model).toEqual({
        provider: 'anthropic',
        model: 'claude-3-5-sonnet-20241022',
      })
    })

    it('uses custom model from AI_MODEL with anthropic provider', () => {
      process.env.AI_PROVIDER = 'anthropic'
      process.env.AI_MODEL = 'claude-3-opus-20240229'

      const model = getAIModel()

      expect(model).toEqual({
        provider: 'anthropic',
        model: 'claude-3-opus-20240229',
      })
    })

    it('uses custom model from AI_MODEL with openai provider', () => {
      process.env.AI_PROVIDER = 'openai'
      process.env.AI_MODEL = 'gpt-4-turbo'

      const model = getAIModel()

      expect(model).toEqual({
        provider: 'openai',
        model: 'gpt-4-turbo',
      })
    })
  })
})
