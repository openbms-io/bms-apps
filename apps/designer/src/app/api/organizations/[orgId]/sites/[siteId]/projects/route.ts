import { NextRequest, NextResponse } from 'next/server'
import { ProjectQuerySchema, CreateProjectRequestSchema } from './schemas'
import { projectsRepository } from '@/lib/db/models/projects'
import { handleApiError } from '@/lib/api/error-handler'
import { ProjectMapper } from '@/lib/domain/mappers/project.mapper'

export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ orgId: string; siteId: string }> }
): Promise<NextResponse> {
  try {
    const { siteId } = await params
    const { searchParams } = new URL(request.url)

    const query = ProjectQuerySchema.parse({
      page: searchParams.get('page'),
      limit: searchParams.get('limit'),
      search: searchParams.get('search'),
      sort: searchParams.get('sort'),
      order: searchParams.get('order'),
    })

    const dbData = await projectsRepository.list({ siteId, ...query })

    const data = {
      ...dbData,
      projects: dbData.projects.map(ProjectMapper.toDTO),
    }

    const response = {
      success: true,
      data,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch projects')
  }
}

export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ orgId: string; siteId: string }> }
): Promise<NextResponse> {
  try {
    const { siteId } = await params
    const body = await request.json()

    const dto = CreateProjectRequestSchema.parse(body)

    const dbInsert = ProjectMapper.toDbInsert({ ...dto, siteId })

    const dbProject = await projectsRepository.create(dbInsert)

    const project = ProjectMapper.toDTO(dbProject)

    const response = {
      success: true,
      project,
    }

    return NextResponse.json(response, { status: 201 })
  } catch (error) {
    return handleApiError(error, 'create project')
  }
}
