'use client'

import { useEffect } from 'react'
import { useRouter } from 'next/navigation'
import { useOrganizations } from '@/hooks/use-organizations'
import { useSites } from '@/hooks/use-sites'

export default function Home() {
  const router = useRouter()
  const { data: organizations, isLoading: isLoadingOrgs } = useOrganizations()
  const firstOrgId = organizations?.[0]?.id
  const { data: sites, isLoading: isLoadingSites } = useSites(firstOrgId)

  useEffect(() => {
    if (!isLoadingOrgs && !isLoadingSites && organizations && sites) {
      if (organizations.length > 0 && sites.length > 0) {
        router.push(
          `/organizations/${organizations[0].id}/sites/${sites[0].id}/projects`
        )
      }
    }
  }, [organizations, sites, isLoadingOrgs, isLoadingSites, router])

  return (
    <div className="flex items-center justify-center h-screen">
      <div className="text-center">
        <div className="text-lg font-medium">Loading...</div>
        <div className="text-sm text-muted-foreground mt-2">
          Initializing application
        </div>
      </div>
    </div>
  )
}
