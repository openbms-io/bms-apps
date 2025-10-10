import { NextRequest, NextResponse } from 'next/server'
import { OrganizationQuerySchema } from './schemas'
import { organizationsRepository } from '@/lib/db/models/organizations'
import { handleApiError } from '@/lib/api/error-handler'
import { OrganizationMapper } from '@/lib/domain/mappers/organization.mapper'

export async function GET(request: NextRequest): Promise<NextResponse> {
  try {
    const { searchParams } = new URL(request.url)

    const query = OrganizationQuerySchema.parse({
      page: searchParams.get('page'),
      limit: searchParams.get('limit'),
    })

    const dbOrganizations = await organizationsRepository.list(query)

    const data = {
      organizations: dbOrganizations.map(OrganizationMapper.toDTO),
    }

    const response = {
      success: true,
      data,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch organizations')
  }
}
