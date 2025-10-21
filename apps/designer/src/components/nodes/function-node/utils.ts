import { ComputeValue } from '@/types/infrastructure'

export const formatValue = (val: ComputeValue | undefined): string => {
  if (val === undefined) return '-'
  if (val.type === 'number' && typeof val.value === 'number') {
    return isNaN(val.value) ? 'NaN' : val.value.toFixed(2)
  }
  return val.value ? 'true' : 'false'
}
