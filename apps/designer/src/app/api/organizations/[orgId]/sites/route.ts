import { NextRequest, NextResponse } from 'next/server'
import { sitesRepository } from '@/lib/db/models/sites'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ orgId: string }> }
): Promise<NextResponse> {
  try {
    const { orgId } = await params
    const { searchParams } = new URL(request.url)

    const page = searchParams.get('page')
      ? parseInt(searchParams.get('page')!)
      : 1
    const limit = searchParams.get('limit')
      ? parseInt(searchParams.get('limit')!)
      : 100

    const sites = await sitesRepository.listByOrganization(orgId, {
      page,
      limit,
    })

    const response = {
      success: true,
      sites,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch sites')
  }
}
