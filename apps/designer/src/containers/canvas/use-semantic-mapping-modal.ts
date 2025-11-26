import { useState, useCallback } from 'react'
import type { XYPosition } from '@xyflow/react'
import type {
  BACnetPointData,
  BACnetControllerData,
} from '@/domains/building-semantics'
import type { DraggedPoint } from '@/store/slices/flow-slice'

export function useSemanticMappingModal() {
  const [isOpen, setIsOpen] = useState(false)
  const [pendingPosition, setPendingPosition] = useState<XYPosition | null>(
    null
  )
  const [pendingDraggedPoint, setPendingDraggedPoint] =
    useState<DraggedPoint | null>(null)
  const [bacnetPoint, setBacnetPoint] = useState<BACnetPointData | undefined>(
    undefined
  )
  const [bacnetController, setBacnetController] = useState<
    BACnetControllerData | undefined
  >(undefined)

  const openModal = useCallback(
    (
      position: XYPosition,
      draggedPoint: DraggedPoint,
      point: BACnetPointData,
      controller: BACnetControllerData
    ) => {
      setPendingPosition(position)
      setPendingDraggedPoint(draggedPoint)
      setBacnetPoint(point)
      setBacnetController(controller)
      setIsOpen(true)
    },
    []
  )

  const closeModal = useCallback(() => {
    setIsOpen(false)
    setPendingPosition(null)
    setPendingDraggedPoint(null)
    setBacnetPoint(undefined)
    setBacnetController(undefined)
  }, [])

  return {
    isOpen,
    setIsOpen,
    pendingPosition,
    pendingDraggedPoint,
    bacnetPoint,
    bacnetController,
    openModal,
    closeModal,
  }
}
