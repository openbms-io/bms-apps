import { Organization } from '../db/schema'
import { ApiResponse } from './utils'

export const organizationsApi = {
  async list(): Promise<Organization[]> {
    const res = await fetch('/api/organizations')
    const json: ApiResponse<{ organizations: Organization[] }> =
      await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch organizations')
    }

    if (!json.data.organizations) {
      throw new Error('Organizations not found in response')
    }

    return json.data.organizations
  },
}
