import 'server-only'

import type { MappingRecord } from './memory-manager'

export interface IMappingMessageFormatter {
  formatMessage(params: { mapping: MappingRecord }): string
  formatMetadata(params: {
    mapping: MappingRecord
    projectId?: string
  }): Record<string, unknown>
}

export class MappingMessageFormatter implements IMappingMessageFormatter {
  formatMessage({ mapping }: { mapping: MappingRecord }): string {
    const overrideText = mapping.wasOverridden
      ? 'User overrode AI suggestion.'
      : 'AI suggestion was accepted.'

    return `Mapping decision: Points matching pattern "${mapping.pointPattern}" from controller "${mapping.controllerId}" were mapped to "${mapping.selectedId}" at step "${mapping.step}". ${overrideText}`
  }

  formatMetadata({
    mapping,
    projectId,
  }: {
    mapping: MappingRecord
    projectId?: string
  }): Record<string, unknown> {
    const metadata: Record<string, unknown> = {
      pointPattern: mapping.pointPattern,
      controllerId: mapping.controllerId,
      step: mapping.step,
      selectedId: mapping.selectedId,
      wasOverridden: mapping.wasOverridden,
    }

    if (projectId) {
      metadata.projectId = projectId
    }

    return metadata
  }
}
