import { MainLayout } from '@/components/layout/main-layout'
import { InfrastructureSidebar } from '@/components/sidebar/infrastructure-sidebar'
import { FlowCanvas } from '@/components/canvas/flow-canvas'
import { WorkflowLoader } from '@/components/canvas/workflow-loader'

interface ProjectPageProps {
  params: Promise<{ orgId: string; siteId: string; projectId: string }>
}

export default async function ProjectPage({ params }: ProjectPageProps) {
  const { orgId, siteId, projectId } = await params

  return (
    <MainLayout
      projectName={`Project ${projectId}`}
      sidebar={
        <InfrastructureSidebar
          orgId={orgId}
          siteId={siteId}
          projectId={projectId}
        />
      }
    >
      <WorkflowLoader orgId={orgId} siteId={siteId} projectId={projectId} />
      <FlowCanvas orgId={orgId} siteId={siteId} projectId={projectId} />
    </MainLayout>
  )
}
