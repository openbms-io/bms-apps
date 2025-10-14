import React from 'react'
import { ProjectsContainer } from './components/ProjectsContainer'

interface ProjectsPageProps {
  params: Promise<{ orgId: string; siteId: string }>
}

export default async function ProjectsPage({
  params,
}: ProjectsPageProps): Promise<React.JSX.Element> {
  const { orgId, siteId } = await params
  return <ProjectsContainer orgId={orgId} siteId={siteId} />
}
