import { NextRequest, NextResponse } from 'next/server'
import { ZodError } from 'zod'
import { AISuggestionConfirmRequestDTOSchema } from '@/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'
import { createAISuggestionService } from '@/lib/server-only/ai'

interface RouteParams {
  params: Promise<{
    orgId: string
    siteId: string
    projectId: string
  }>
}

export async function POST(
  request: NextRequest,
  { params }: RouteParams
): Promise<NextResponse> {
  try {
    const { orgId, projectId } = await params
    const body = await request.json()
    const validatedRequest = AISuggestionConfirmRequestDTOSchema.parse(body)

    const service = createAISuggestionService()

    await service.confirmMapping({
      orgId,
      projectId,
      mapping: validatedRequest.mapping,
    })

    return NextResponse.json({
      success: true,
    })
  } catch (error) {
    if (error instanceof ZodError) {
      return NextResponse.json(
        {
          success: false,
          error: `Invalid request: ${error.errors
            .map((e) => e.message)
            .join(', ')}`,
        },
        { status: 400 }
      )
    }

    if (error instanceof SyntaxError) {
      return NextResponse.json(
        { success: false, error: 'Invalid JSON in request body' },
        { status: 400 }
      )
    }

    console.error('AI suggestion confirm error:', error)

    return NextResponse.json(
      { success: false, error: 'AI service unavailable' },
      { status: 503 }
    )
  }
}
