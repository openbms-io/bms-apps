import { NextRequest, NextResponse } from 'next/server'
import { ZodError } from 'zod'
import { AISuggestionRequestDTOSchema } from '@/domains/building-semantics/adapters/ashrae-223p/schemas/ai-suggestion.dto.schemas'
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
    const validatedRequest = AISuggestionRequestDTOSchema.parse(body)

    const service = createAISuggestionService()

    const suggestion = await service.getSuggestion({
      step: validatedRequest.step,
      orgId,
      projectId,
      point: validatedRequest.point,
      candidates: validatedRequest.candidates,
      selectionContext: validatedRequest.selectionContext,
    })

    return NextResponse.json({
      success: true,
      data: suggestion,
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

    console.error('AI suggestion error:', error)

    return NextResponse.json(
      { success: false, error: 'AI service unavailable' },
      { status: 503 }
    )
  }
}
