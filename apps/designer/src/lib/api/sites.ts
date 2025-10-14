import { Site } from '../db/schema'
import { ApiResponse } from './utils'

export const sitesApi = {
  async listByOrg(orgId: string): Promise<Site[]> {
    const res = await fetch(`/api/organizations/${orgId}/sites`)
    const json: ApiResponse<{ sites: Site[] }> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch sites')
    }

    if (!json.data.sites) {
      throw new Error('Sites not found in response')
    }

    return json.data.sites
  },
}
