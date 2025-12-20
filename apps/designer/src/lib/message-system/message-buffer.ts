import { Message } from './types'
import { ComputeValue, MessageValue } from '@/types/infrastructure'

export interface MessageBuffer<THandle extends string> {
  set(handle: THandle, message: Message): void
  get(handle: THandle): Message | undefined
  has(handle: THandle): boolean
  clear(): void
  hasAll(handles: readonly THandle[]): boolean
  collectValues(): Record<string, MessageValue | unknown>
}

export function createMessageBuffer<
  THandle extends string,
>(): MessageBuffer<THandle> {
  const buffer = new Map<THandle, Message>()

  return {
    set: (handle: THandle, message: Message) => {
      buffer.set(handle, message)
    },

    get: (handle: THandle) => buffer.get(handle),

    has: (handle: THandle) => buffer.has(handle),

    clear: () => buffer.clear(),

    hasAll: (handles: readonly THandle[]) =>
      handles.every((h) => buffer.has(h)),

    collectValues: () => {
      const values: Record<string, MessageValue | unknown> = {}
      for (const [handle, message] of buffer) {
        const payload = message.payload
        values[handle] =
          payload && typeof payload === 'object' && 'value' in payload
            ? (payload as ComputeValue).value
            : (payload as unknown)
      }
      return values
    },
  }
}
