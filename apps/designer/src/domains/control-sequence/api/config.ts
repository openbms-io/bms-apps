import { client } from './generated/client.gen'

export const API_BASE_URL =
  process.env.NEXT_PUBLIC_CONTROL_SEQUENCE_API_URL || '/control-sequence'

client.setConfig({
  baseUrl: API_BASE_URL,
})
