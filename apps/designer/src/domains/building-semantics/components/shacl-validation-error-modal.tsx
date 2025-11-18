'use client'

import {
  AlertDialog,
  AlertDialogAction,
  AlertDialogContent,
  AlertDialogDescription,
  AlertDialogFooter,
  AlertDialogHeader,
  AlertDialogTitle,
} from '@/components/ui/alert-dialog'
import { Alert, AlertDescription } from '@/components/ui/alert'
import { AlertCircle } from 'lucide-react'

interface ShaclValidationErrorModalProps {
  open: boolean
  errors: string[]
  onOpenChange: (open: boolean) => void
}

/**
 * Modal that displays SHACL validation errors when a mapping fails validation.
 *
 * Shows user-friendly error messages from the backend SHACL validation engine,
 * allowing the user to fix issues and retry.
 */
export function ShaclValidationErrorModal({
  open,
  errors,
  onOpenChange,
}: ShaclValidationErrorModalProps) {
  return (
    <AlertDialog open={open} onOpenChange={onOpenChange}>
      <AlertDialogContent className="max-w-2xl">
        <AlertDialogHeader>
          <AlertDialogTitle className="flex items-center gap-2 text-red-600">
            <AlertCircle className="h-5 w-5" />
            SHACL Validation Failed
          </AlertDialogTitle>
          <AlertDialogDescription>
            The mapping does not comply with ASHRAE 223P constraints. Please fix
            the following errors and try again:
          </AlertDialogDescription>
        </AlertDialogHeader>

        <div className="space-y-2 max-h-[400px] overflow-y-auto">
          {errors.map((error, index) => (
            <Alert key={index} variant="destructive">
              <AlertDescription className="text-sm">• {error}</AlertDescription>
            </Alert>
          ))}
        </div>

        <AlertDialogFooter>
          <AlertDialogAction onClick={() => onOpenChange(false)}>
            Fix Issues
          </AlertDialogAction>
        </AlertDialogFooter>
      </AlertDialogContent>
    </AlertDialog>
  )
}
