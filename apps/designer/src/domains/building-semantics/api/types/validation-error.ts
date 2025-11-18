/**
 * SHACL validation error response from POST /api/v1/223p/mappings
 *
 * When SHACL validation fails, the API returns 400 with this structure.
 */
export interface ShaclValidationError {
  validationType: 'SHACL'
  isValid: false
  errors: string[]
  warnings: string[]
}

/**
 * HTTP 400 error response detail containing SHACL validation errors
 */
export interface ValidationErrorResponse {
  detail: ShaclValidationError
}

/**
 * Type guard to check if an error is a SHACL validation error
 *
 * Hey-API client throws the parsed JSON response directly:
 * { detail: { validationType: 'SHACL', isValid: false, errors: [...], warnings: [...] } }
 */
export function isShaclValidationError(
  error: unknown
): error is ValidationErrorResponse {
  if (typeof error !== 'object' || error === null) return false

  const err = error as any
  return (
    err.detail?.validationType === 'SHACL' &&
    err.detail?.isValid === false &&
    Array.isArray(err.detail?.errors)
  )
}

/**
 * Extract SHACL validation errors from an error object
 */
export function extractShaclErrors(error: unknown): string[] {
  if (isShaclValidationError(error)) {
    return error.detail.errors
  }
  return []
}
