import { NextResponse } from 'next/server'
import { ZodError } from 'zod'

export function handleApiError(
  error: unknown,
  operation: string
): NextResponse {
  console.error(`Error ${operation}:`, error)

  if (error instanceof ZodError) {
    return NextResponse.json(
      {
        error: `Invalid request: ${error.errors
          .map((e) => e.message)
          .join(', ')}`,
      },
      { status: 400 }
    )
  }

  if (error instanceof SyntaxError) {
    return NextResponse.json(
      { error: 'Invalid JSON in request body' },
      { status: 400 }
    )
  }

  return NextResponse.json({ error: `Failed to ${operation}` }, { status: 500 })
}
