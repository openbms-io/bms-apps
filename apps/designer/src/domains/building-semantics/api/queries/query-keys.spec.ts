import { semanticQueryKeys } from './query-keys'

describe('semanticQueryKeys', () => {
  describe('aiSuggestions', () => {
    it('generates step-based query key for system step', () => {
      const key = semanticQueryKeys.aiSuggestions.step(
        'system',
        'org-123',
        'proj-456',
        'point-789'
      )
      expect(key).toEqual([
        'building-semantics',
        'ai-suggestions',
        'step',
        'system',
        'org-123',
        'proj-456',
        'point-789',
      ])
    })

    it('generates step-based query key for device step', () => {
      const key = semanticQueryKeys.aiSuggestions.step(
        'device',
        'org-123',
        'proj-456',
        'point-789'
      )
      expect(key).toEqual([
        'building-semantics',
        'ai-suggestions',
        'step',
        'device',
        'org-123',
        'proj-456',
        'point-789',
      ])
    })

    it('generates step-based query key for property step', () => {
      const key = semanticQueryKeys.aiSuggestions.step(
        'property',
        'org-123',
        'proj-456',
        'point-789'
      )
      expect(key).toEqual([
        'building-semantics',
        'ai-suggestions',
        'step',
        'property',
        'org-123',
        'proj-456',
        'point-789',
      ])
    })

    it('generates confirm mutation key', () => {
      const key = semanticQueryKeys.aiSuggestions.confirm('org-123', 'proj-456')
      expect(key).toEqual([
        'building-semantics',
        'ai-suggestions',
        'confirm',
        'org-123',
        'proj-456',
      ])
    })
  })
})
