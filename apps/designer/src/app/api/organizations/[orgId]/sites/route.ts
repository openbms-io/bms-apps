import { NextRequest, NextResponse } from 'next/server'
import { SiteQuerySchema } from './schemas'
import { sitesRepository } from '@/lib/db/models/sites'
import { handleApiError } from '@/lib/api/error-handler'
import { SiteMapper } from '@/lib/domain/mappers/site.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ orgId: string }> }
): Promise<NextResponse> {
  try {
    const { orgId } = await params
    const { searchParams } = new URL(request.url)

    const query = SiteQuerySchema.parse({
      page: searchParams.get('page'),
      limit: searchParams.get('limit'),
    })

    const dbSites = await sitesRepository.listByOrganization(orgId, query)

    const data = {
      sites: dbSites.map((db) =>
        SiteMapper.toDTO({
          ...db,
          description: db.description ?? null,
        })
      ),
    }

    const response = {
      success: true,
      data,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch sites')
  }
}
