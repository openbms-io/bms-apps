import {
  useQuery,
  useMutation,
  useQueryClient,
  UseQueryOptions,
  UseMutationOptions,
} from '@tanstack/react-query'
import type {
  Project,
  CreateProject,
  UpdateProject,
  ProjectQuery,
  ProjectListResponse,
} from '@/app/api/organizations/[orgId]/sites/[siteId]/projects/schemas'

import { projectsApi } from '../lib/api/projects'
import { queryKeys } from '../lib/query-client'

export function useProjects(
  query: { orgId: string; siteId: string } & ProjectQuery,
  options?: Omit<UseQueryOptions<ProjectListResponse>, 'queryKey' | 'queryFn'>
): ReturnType<typeof useQuery<ProjectListResponse>> {
  return useQuery({
    queryKey: queryKeys.projects.list(query),
    enabled: !!query.orgId && !!query.siteId,
    queryFn: () => projectsApi.list(query),
    ...options,
  })
}

export function useProject(
  {
    orgId,
    siteId,
    projectId,
  }: { orgId: string; siteId: string; projectId: string },
  options?: Omit<UseQueryOptions<Project>, 'queryKey' | 'queryFn'>
): ReturnType<typeof useQuery<Project>> {
  return useQuery({
    queryKey: queryKeys.projects.detail(projectId),
    queryFn: () => projectsApi.get({ orgId, siteId, projectId }),
    enabled: !!orgId && !!siteId && !!projectId,
    ...options,
  })
}

export function useCreateProject(
  options?: UseMutationOptions<
    Project,
    Error,
    { orgId: string; siteId: string } & CreateProject
  >
): ReturnType<
  typeof useMutation<
    Project,
    Error,
    { orgId: string; siteId: string } & CreateProject
  >
> {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: (data: { orgId: string; siteId: string } & CreateProject) =>
      projectsApi.create(data),
    onSuccess: (newProject) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.lists(),
      })
      queryClient.setQueryData(
        queryKeys.projects.detail(newProject.id),
        newProject
      )
    },
    ...options,
  })
}

export function useUpdateProject(
  options?: UseMutationOptions<
    Project,
    Error,
    { orgId: string; siteId: string; projectId: string } & UpdateProject
  >
): ReturnType<
  typeof useMutation<
    Project,
    Error,
    { orgId: string; siteId: string; projectId: string } & UpdateProject
  >
> {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: (
      data: { orgId: string; siteId: string; projectId: string } & UpdateProject
    ) => projectsApi.update(data),
    onSuccess: (updatedProject, data) => {
      queryClient.setQueryData(
        queryKeys.projects.detail(data.projectId),
        updatedProject
      )
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.lists(),
      })
    },
    ...options,
  })
}

export function useDeleteProject(
  options?: UseMutationOptions<
    void,
    Error,
    { orgId: string; siteId: string; projectId: string }
  >
): ReturnType<
  typeof useMutation<
    void,
    Error,
    { orgId: string; siteId: string; projectId: string }
  >
> {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: (data: { orgId: string; siteId: string; projectId: string }) =>
      projectsApi.delete(data),
    onSuccess: (_, data) => {
      queryClient.removeQueries({
        queryKey: queryKeys.projects.detail(data.projectId),
      })
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.lists(),
      })
    },
    ...options,
  })
}

export function useOptimisticUpdateProject(
  options?: Omit<
    UseMutationOptions<
      Project,
      Error,
      { orgId: string; siteId: string; projectId: string } & UpdateProject,
      { previousProject: Project | undefined }
    >,
    'mutationFn' | 'onMutate' | 'onError' | 'onSettled'
  >
): ReturnType<
  typeof useMutation<
    Project,
    Error,
    { orgId: string; siteId: string; projectId: string } & UpdateProject,
    { previousProject: Project | undefined }
  >
> {
  const queryClient = useQueryClient()

  return useMutation<
    Project,
    Error,
    { orgId: string; siteId: string; projectId: string } & UpdateProject,
    { previousProject: Project | undefined }
  >({
    mutationFn: (
      data: { orgId: string; siteId: string; projectId: string } & UpdateProject
    ) => projectsApi.update(data),
    onMutate: async (
      data: { orgId: string; siteId: string; projectId: string } & UpdateProject
    ) => {
      await queryClient.cancelQueries({
        queryKey: queryKeys.projects.detail(data.projectId),
      })
      const previousProject = queryClient.getQueryData<Project>(
        queryKeys.projects.detail(data.projectId)
      )
      if (previousProject) {
        const updatedProject: Project = {
          ...previousProject,
          updatedAt: new Date().toISOString(),
        }

        if (data.name !== undefined) {
          updatedProject.name = data.name
        }
        if (data.description !== undefined) {
          updatedProject.description = data.description ?? undefined
        }
        if (data.workflowConfig !== undefined) {
          updatedProject.workflowConfig = data.workflowConfig
        }

        queryClient.setQueryData<Project>(
          queryKeys.projects.detail(data.projectId),
          updatedProject
        )
      }

      return { previousProject }
    },
    onError: (err, data, context) => {
      if (context?.previousProject) {
        queryClient.setQueryData(
          queryKeys.projects.detail(data.projectId),
          context.previousProject
        )
      }
    },
    onSettled: (_, __, data) => {
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.detail(data.projectId),
      })
      queryClient.invalidateQueries({
        queryKey: queryKeys.projects.lists(),
      })
    },
    ...options,
  })
}

export function usePrefetchProject(): ({
  orgId,
  siteId,
  projectId,
}: {
  orgId: string
  siteId: string
  projectId: string
}) => void {
  const queryClient = useQueryClient()

  return ({
    orgId,
    siteId,
    projectId,
  }: {
    orgId: string
    siteId: string
    projectId: string
  }): void => {
    queryClient.prefetchQuery({
      queryKey: queryKeys.projects.detail(projectId),
      queryFn: () => projectsApi.get({ orgId, siteId, projectId }),
      staleTime: 5 * 60 * 1000,
    })
  }
}
