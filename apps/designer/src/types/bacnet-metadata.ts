export interface BacnetMetadata {
  status_flags?: string[]
  event_state?: string
  out_of_service?: boolean
  reliability?: string
  min_pres_value?: number
  max_pres_value?: number
  high_limit?: number
  low_limit?: number
  resolution?: number
  cov_increment?: number
  time_delay?: number
  deadband?: number
  priority_array?: string
  relinquish_default?: number
  [key: string]: unknown
}
