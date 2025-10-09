import { Site } from '../db/schema'

interface ApiResponse<T> {
  success: boolean
  error?: string
  sites?: T[]
}

export const sitesApi = {
  async listByOrg(orgId: string): Promise<Site[]> {
    const res = await fetch(`/api/organizations/${orgId}/sites`)
    const json: ApiResponse<Site> = await res.json()

    if (!res.ok || !json.success) {
      throw new Error(json.error || 'Failed to fetch sites')
    }

    if (!json.sites) {
      throw new Error('Sites not found in response')
    }

    return json.sites
  },
}
