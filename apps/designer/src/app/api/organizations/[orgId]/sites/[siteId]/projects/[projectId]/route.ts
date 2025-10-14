import { NextRequest, NextResponse } from 'next/server'
import { UpdateProjectRequestSchema } from '../schemas'
import { projectsRepository } from '@/lib/db/models/projects'
import { handleApiError } from '@/lib/api/error-handler'
import { ProjectMapper } from '@/lib/domain/mappers/project.mapper'

interface RouteParams {
  params: Promise<{ projectId: string }>
}

export async function GET(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { projectId } = await params

    const dbProject = await projectsRepository.findById(projectId)

    if (!dbProject) {
      return NextResponse.json(
        {
          success: false,
          error: 'Project not found',
        },
        { status: 404 }
      )
    }

    const project = ProjectMapper.toDTO(dbProject)

    const response = {
      success: true,
      project,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'fetch project')
  }
}

export async function PUT(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { projectId } = await params
    const body = await request.json()

    const dto = UpdateProjectRequestSchema.parse(body)

    const dbUpdate = ProjectMapper.toDbUpdate(dto)

    const dbProject = await projectsRepository.update(projectId, dbUpdate)

    if (!dbProject) {
      return NextResponse.json(
        {
          success: false,
          error: 'Project not found',
        },
        { status: 404 }
      )
    }

    const project = ProjectMapper.toDTO(dbProject)

    const response = {
      success: true,
      project,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'update project')
  }
}

export async function DELETE(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { projectId } = await params

    const deleted = await projectsRepository.delete(projectId)

    if (!deleted) {
      return NextResponse.json(
        {
          success: false,
          error: 'Project not found',
        },
        { status: 404 }
      )
    }

    const response = {
      success: true,
    }

    return NextResponse.json(response)
  } catch (error) {
    return handleApiError(error, 'delete project')
  }
}
