import { useMutation, useQueryClient } from '@tanstack/react-query'
import { createSpaceApiV1223pSpacesPost } from '../generated'

interface CreateSpaceParams {
  projectId: string
  label: string
  spaceTypeId: string
}

export function useCreateSpaceMutation() {
  const queryClient = useQueryClient()

  return useMutation({
    mutationFn: async ({
      projectId,
      label,
      spaceTypeId,
    }: CreateSpaceParams) => {
      const response = await createSpaceApiV1223pSpacesPost({
        body: {
          projectId,
          label,
          spaceTypeId,
        },
      })
      return response.data
    },
    onSuccess: (_, { projectId }) => {
      queryClient.invalidateQueries({ queryKey: ['spaces', projectId] })
    },
    retry: 3,
  })
}
