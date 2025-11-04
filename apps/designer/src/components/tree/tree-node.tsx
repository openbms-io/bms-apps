'use client'

import { ChevronRight, ChevronDown, Trash2, Pencil, Plus } from 'lucide-react'
import { cn } from '@/lib/utils'
import { TreeNode as TreeNodeType } from '@/types/infrastructure'
import { Point223PBadge } from '@/domains/building-semantics/components/point-223p-badge'

interface TreeNodeProps {
  node: TreeNodeType
  onToggle: (nodeId: string) => void
  onSelect?: (nodeId: string | null) => void
  onDelete?: (nodeId: string) => void
  onAdd223PMapping?: (nodeId: string) => void
  onEdit223PMapping?: (nodeId: string) => void
  isSelected?: boolean
  isDraggable?: boolean
  onDragStart?: (e: React.DragEvent, node: TreeNodeType) => void
}

export function TreeNode({
  node,
  onToggle,
  onSelect,
  onDelete,
  onAdd223PMapping,
  onEdit223PMapping,
  isSelected = false,
  isDraggable = false,
  onDragStart,
}: TreeNodeProps) {
  const handleClick = (e: React.MouseEvent) => {
    if (node.hasChildren) {
      e.stopPropagation()
      onToggle(node.id)
    }
  }

  const handleSelect = (e: React.MouseEvent) => {
    e.stopPropagation()
    if (onSelect) {
      if (node.type === 'point') {
        onSelect(node.id)
      } else {
        // Clear selection when clicking non-point nodes
        onSelect(null)
      }
    }
  }

  const handleDragStart = (e: React.DragEvent) => {
    if (isDraggable && onDragStart && node.type === 'point') {
      onDragStart(e, node)
    } else {
      e.preventDefault()
    }
  }

  const handleDelete = (e: React.MouseEvent) => {
    e.stopPropagation()
    if (onDelete) {
      onDelete(node.id)
    }
  }

  const handleAdd223PMapping = (e: React.MouseEvent) => {
    e.stopPropagation()
    if (onAdd223PMapping) {
      onAdd223PMapping(node.id)
    }
  }

  const handleEdit223PMapping = (e: React.MouseEvent) => {
    e.stopPropagation()
    if (onEdit223PMapping) {
      onEdit223PMapping(node.id)
    }
  }

  const paddingLeft = node.depth * 16

  return (
    <div
      className={cn(
        'group flex items-center gap-1 py-1.5 px-2 hover:bg-accent/50 cursor-pointer select-none',
        isSelected && 'bg-accent',
        node.type === 'point' && 'hover:bg-accent'
      )}
      style={{ paddingLeft: `${paddingLeft}px` }}
      onClick={handleSelect}
      draggable={isDraggable && node.type === 'point'}
      onDragStart={handleDragStart}
    >
      {node.hasChildren && (
        <button
          onClick={handleClick}
          className="p-0.5 hover:bg-accent-foreground/10 rounded"
        >
          {node.isExpanded ? (
            <ChevronDown className="h-3 w-3" />
          ) : (
            <ChevronRight className="h-3 w-3" />
          )}
        </button>
      )}

      {!node.hasChildren && <span className="w-4" />}

      <span className="text-sm mr-1">{node.icon}</span>

      <div className="flex-1 min-w-0">
        <div className="flex items-center gap-2">
          <span
            className={cn(
              'text-sm font-medium truncate',
              node.type === 'point' && 'text-foreground/90'
            )}
          >
            {node.label}
          </span>

          {node.type === 'point' && node.semanticMapping && (
            <Point223PBadge mapping={node.semanticMapping} />
          )}
        </div>

        {node.sublabel && (
          <span className="text-xs text-muted-foreground truncate block">
            {node.sublabel}
          </span>
        )}
      </div>

      {node.type === 'point' && !node.semanticMapping && onAdd223PMapping && (
        <button
          onClick={handleAdd223PMapping}
          className="opacity-0 group-hover:opacity-100 p-1 hover:bg-primary/10 rounded transition-opacity"
          title="Add 223P mapping"
        >
          <Plus className="h-3.5 w-3.5 text-primary" />
        </button>
      )}

      {node.type === 'point' && node.semanticMapping && onEdit223PMapping && (
        <button
          onClick={handleEdit223PMapping}
          className="opacity-0 group-hover:opacity-100 p-1 hover:bg-primary/10 rounded transition-opacity"
          title="Edit 223P mapping"
        >
          <Pencil className="h-3.5 w-3.5 text-primary" />
        </button>
      )}

      {node.type === 'controller' && onDelete && (
        <button
          onClick={handleDelete}
          className="opacity-0 group-hover:opacity-100 p-1 hover:bg-destructive/10 rounded transition-opacity"
          title="Delete controller"
        >
          <Trash2 className="h-3.5 w-3.5 text-destructive" />
        </button>
      )}
    </div>
  )
}
