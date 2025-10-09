import { NextRequest, NextResponse } from 'next/server'
import { organizationsRepository } from '@/lib/db/models/organizations'
import { handleApiError } from '@/lib/api/error-handler'

export async function GET(request: NextRequest): Promise<NextResponse> {
  try {
    const { searchParams } = new URL(request.url)

    const page = searchParams.get('page')
      ? parseInt(searchParams.get('page')!)
      : 1
    const limit = searchParams.get('limit')
      ? parseInt(searchParams.get('limit')!)
      : 100

    const organizations = await organizationsRepository.list({ page, limit })

    const response = {
      success: true,
      organizations,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch organizations')
  }
}
