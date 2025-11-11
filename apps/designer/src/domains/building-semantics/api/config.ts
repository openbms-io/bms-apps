import { client } from './generated/client.gen'

export const API_BASE_URL =
  process.env.NEXT_PUBLIC_SEMANTICS_API_URL || 'http://localhost:8000'

client.setConfig({
  baseUrl: API_BASE_URL,
})
