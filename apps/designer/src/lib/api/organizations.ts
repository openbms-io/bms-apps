import { Organization } from '../db/schema'

interface ApiResponse<T> {
  success: boolean
  error?: string
  organizations?: T[]
}

export const organizationsApi = {
  async list(): Promise<Organization[]> {
    const res = await fetch('/api/organizations')
    const json: ApiResponse<Organization> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch organizations')
    }

    if (!json.organizations) {
      throw new Error('Organizations not found in response')
    }

    return json.organizations
  },
}
