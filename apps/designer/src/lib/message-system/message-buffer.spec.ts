import { createMessageBuffer, MessageBuffer } from './message-buffer'
import { Message } from './types'
import { MessageValue } from '@/types/infrastructure'

describe('MessageBuffer', () => {
  let buffer: MessageBuffer<'input1' | 'input2' | 'input3'>

  beforeEach(() => {
    buffer = createMessageBuffer<'input1' | 'input2' | 'input3'>()
  })

  const createMessage = (value: MessageValue): Message => ({
    payload: { value, type: 'number' },
    _msgid: 'test-msg-id',
    timestamp: Date.now(),
  })

  describe('set and get', () => {
    it('stores and retrieves messages by handle', () => {
      const message = createMessage(42)
      buffer.set('input1', message)

      expect(buffer.get('input1')).toBe(message)
    })

    it('returns undefined for handles without messages', () => {
      expect(buffer.get('input1')).toBeUndefined()
    })

    it('overwrites existing messages for the same handle', () => {
      const message1 = createMessage(1)
      const message2 = createMessage(2)

      buffer.set('input1', message1)
      buffer.set('input1', message2)

      expect(buffer.get('input1')).toBe(message2)
    })
  })

  describe('has', () => {
    it('returns true for handles with messages', () => {
      buffer.set('input1', createMessage(42))

      expect(buffer.has('input1')).toBe(true)
    })

    it('returns false for handles without messages', () => {
      expect(buffer.has('input1')).toBe(false)
    })
  })

  describe('hasAll', () => {
    it('returns true when all specified handles have messages', () => {
      buffer.set('input1', createMessage(1))
      buffer.set('input2', createMessage(2))

      expect(buffer.hasAll(['input1', 'input2'])).toBe(true)
    })

    it('returns false when some handles are missing', () => {
      buffer.set('input1', createMessage(1))

      expect(buffer.hasAll(['input1', 'input2'])).toBe(false)
    })

    it('returns true for empty array', () => {
      expect(buffer.hasAll([])).toBe(true)
    })

    it('works with readonly arrays', () => {
      buffer.set('input1', createMessage(1))
      buffer.set('input2', createMessage(2))

      const requiredHandles = ['input1', 'input2'] as const
      expect(buffer.hasAll(requiredHandles)).toBe(true)
    })
  })

  describe('clear', () => {
    it('removes all messages from buffer', () => {
      buffer.set('input1', createMessage(1))
      buffer.set('input2', createMessage(2))

      buffer.clear()

      expect(buffer.has('input1')).toBe(false)
      expect(buffer.has('input2')).toBe(false)
    })
  })

  describe('collectValues', () => {
    it('extracts values from ComputeValue payloads', () => {
      buffer.set('input1', createMessage(42))
      buffer.set('input2', createMessage('hello'))

      const values = buffer.collectValues()

      expect(values).toEqual({
        input1: 42,
        input2: 'hello',
      })
    })

    it('handles raw payload values (non-ComputeValue)', () => {
      const rawMessage: Message = {
        payload: 123 as unknown as Message['payload'],
        _msgid: 'test',
        timestamp: Date.now(),
      }
      buffer.set('input1', rawMessage)

      const values = buffer.collectValues()

      expect(values).toEqual({ input1: 123 })
    })

    it('handles undefined payloads', () => {
      const undefinedPayloadMessage: Message = {
        payload: undefined,
        _msgid: 'test',
        timestamp: Date.now(),
      }
      buffer.set('input1', undefinedPayloadMessage)

      const values = buffer.collectValues()

      expect(values).toEqual({ input1: undefined })
    })

    it('returns empty object when buffer is empty', () => {
      const values = buffer.collectValues()

      expect(values).toEqual({})
    })

    it('handles boolean values', () => {
      buffer.set('input1', {
        payload: { value: true, type: 'boolean' },
        _msgid: 'test',
        timestamp: Date.now(),
      })

      const values = buffer.collectValues()

      expect(values).toEqual({ input1: true })
    })
  })

  describe('type safety', () => {
    it('enforces handle types at compile time', () => {
      type TestHandle = 'zoneTemperature' | 'coolingSetpoint'
      const typedBuffer = createMessageBuffer<TestHandle>()

      typedBuffer.set('zoneTemperature', createMessage(21.5))
      typedBuffer.set('coolingSetpoint', createMessage(24))

      expect(typedBuffer.hasAll(['zoneTemperature', 'coolingSetpoint'])).toBe(
        true
      )
    })
  })
})
