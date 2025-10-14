import React from 'react'
import { ProjectCardProps } from './types'
import type { ValidatedWorkflowConfig } from '@/lib/workflow/config-schema'
import {
  Card,
  CardContent,
  CardHeader,
  CardTitle,
  CardDescription,
} from '@/components/ui/card'
import { Button } from '@/components/ui/button'
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu'
import { Badge } from '@/components/ui/badge'
import { MoreHorizontal, Eye, Edit, Trash2 } from 'lucide-react'

export function ProjectCard({
  project,
  onEdit,
  onDelete,
  onView,
}: ProjectCardProps): React.JSX.Element {
  const handleEdit = (): void => {
    onEdit({ id: project.id })
  }

  const handleDelete = (): void => {
    onDelete({ id: project.id })
  }

  const handleView = (): void => {
    onView({ id: project.id })
  }

  const formatDate = ({ date }: { date: string }): string => {
    return new Date(date).toLocaleDateString('en-US', {
      year: 'numeric',
      month: 'short',
      day: 'numeric',
    })
  }

  const getWorkflowConfigSummary = ({
    config,
  }: {
    config?: ValidatedWorkflowConfig
  }): string => {
    if (!config) return 'No workflow'
    const nodeCount = config.data.nodes?.length ?? 0
    return `${nodeCount} nodes`
  }

  return (
    <Card className="hover:shadow-md transition-shadow cursor-pointer group">
      <CardHeader className="pb-3">
        <div className="flex justify-between items-start">
          <div className="flex-1 min-w-0" onClick={handleView}>
            <CardTitle className="text-lg truncate group-hover:text-primary transition-colors">
              {project.name}
            </CardTitle>
            {project.description && (
              <CardDescription className="mt-1 text-sm">
                {project.description}
              </CardDescription>
            )}
          </div>
          <DropdownMenu>
            <DropdownMenuTrigger asChild>
              <Button
                variant="ghost"
                size="icon"
                className="opacity-0 group-hover:opacity-100 transition-opacity"
              >
                <MoreHorizontal className="h-4 w-4" />
              </Button>
            </DropdownMenuTrigger>
            <DropdownMenuContent align="end">
              <DropdownMenuItem onClick={handleView}>
                <Eye className="h-4 w-4 mr-2" />
                View
              </DropdownMenuItem>
              <DropdownMenuItem onClick={handleEdit}>
                <Edit className="h-4 w-4 mr-2" />
                Edit
              </DropdownMenuItem>
              <DropdownMenuItem
                onClick={handleDelete}
                className="text-destructive"
              >
                <Trash2 className="h-4 w-4 mr-2" />
                Delete
              </DropdownMenuItem>
            </DropdownMenuContent>
          </DropdownMenu>
        </div>
      </CardHeader>
      <CardContent className="pt-0" onClick={handleView}>
        <div className="flex items-center justify-between text-sm text-muted-foreground mb-3">
          <Badge variant="secondary" className="text-xs">
            {getWorkflowConfigSummary({ config: project.workflowConfig })}
          </Badge>
          <span>Updated {formatDate({ date: project.updatedAt })}</span>
        </div>
        <div className="text-xs text-muted-foreground">
          Created {formatDate({ date: project.createdAt })}
        </div>
      </CardContent>
    </Card>
  )
}
