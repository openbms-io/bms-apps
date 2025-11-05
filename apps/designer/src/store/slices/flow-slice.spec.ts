import { create } from 'zustand'
import { FlowSlice, createFlowSlice } from './flow-slice'
import { projectsApi } from '@/lib/api/projects'
import {
  serializeWorkflow,
  deserializeWorkflow,
  createNodeFactory,
} from '@/lib/workflow/serializer'
import type { Project } from '@/app/api/organizations/[orgId]/sites/[siteId]/projects/schemas'

// Mock the dependencies
jest.mock('@/lib/api/projects')
jest.mock('@/lib/workflow/serializer')
jest.mock('uuid', () => ({
  v4: jest.fn(() => 'mock-uuid-' + Math.random().toString(36).substr(2, 9)),
}))

const mockProjectsApi = projectsApi as jest.Mocked<typeof projectsApi>
const mockSerializeWorkflow = serializeWorkflow as jest.MockedFunction<
  typeof serializeWorkflow
>
const mockDeserializeWorkflow = deserializeWorkflow as jest.MockedFunction<
  typeof deserializeWorkflow
>
const mockCreateNodeFactory = createNodeFactory as jest.MockedFunction<
  typeof createNodeFactory
>

describe('FlowSlice - Save/Load Integration', () => {
  let store: ReturnType<typeof create<FlowSlice>>

  beforeEach(() => {
    store = create<FlowSlice>()(createFlowSlice)
    jest.clearAllMocks()
  })

  describe('saveProject', () => {
    it('should successfully save a project with workflow config', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const mockProject: Project = {
        id: projectId,
        siteId: 'test-site-123',
        name: 'Test Project',
        description: 'Test Description',
        workflowConfig: undefined,
        createdAt: '2025-01-01T00:00:00Z',
        updatedAt: '2025-01-01T00:00:00Z',
      }

      const mockVersionedConfig = {
        schema_info: {
          version: '1.0.0',
          compatibility: '>=1.0.0',
          schema_name: 'WorkflowConfig',
        },
        data: {
          metadata: {
            lastModified: '2025-01-01T00:00:00Z',
          },
          nodes: [],
          edges: [],
        },
      }

      mockSerializeWorkflow.mockReturnValue(mockVersionedConfig)
      mockProjectsApi.update.mockResolvedValue(mockProject)

      // Act
      await store.getState().saveProject({ projectId })

      // Assert
      expect(store.getState().saveStatus).toBe('saved')
      expect(mockSerializeWorkflow).toHaveBeenCalledWith({
        reactFlowObject: {
          nodes: [],
          edges: [],
          viewport: { x: 0, y: 0, zoom: 1 },
        },
        metadata: expect.objectContaining({
          lastModified: expect.any(String),
        }),
      })
      expect(mockProjectsApi.update).toHaveBeenCalledWith({
        orgId: undefined,
        siteId: undefined,
        projectId: projectId,
        workflowConfig: mockVersionedConfig,
      })
    })

    it('should set saveStatus to error when save fails', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const error = new Error('API Error')
      const mockVersionedConfig = {
        schema_info: {
          version: '1.0.0',
          compatibility: '>=1.0.0',
          schema_name: 'WorkflowConfig',
        },
        data: {
          metadata: {
            lastModified: '2025-01-01T00:00:00Z',
          },
          nodes: [],
          edges: [],
        },
      }

      mockSerializeWorkflow.mockReturnValue(mockVersionedConfig)
      mockProjectsApi.update.mockRejectedValue(error)

      // Act & Assert
      await expect(store.getState().saveProject({ projectId })).rejects.toThrow(
        'API Error'
      )
      expect(store.getState().saveStatus).toBe('error')
    })

    it('should set saveStatus to saving during operation', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const mockVersionedConfig = {
        schema_info: {
          version: '1.0.0',
          compatibility: '>=1.0.0',
          schema_name: 'WorkflowConfig',
        },
        data: {
          metadata: {
            lastModified: '2025-01-01T00:00:00Z',
          },
          nodes: [],
          edges: [],
        },
      }

      mockSerializeWorkflow.mockReturnValue(mockVersionedConfig)

      // Create a promise we can control
      let resolveUpdate: (value: Project) => void
      const updatePromise = new Promise<Project>((resolve) => {
        resolveUpdate = resolve
      })
      mockProjectsApi.update.mockReturnValue(updatePromise)

      // Act
      const savePromise = store.getState().saveProject({ projectId })

      // Assert - status should be saving
      expect(store.getState().saveStatus).toBe('saving')

      // Resolve the update
      const mockProject: Project = {
        id: projectId,
        siteId: 'test-site-123',
        name: 'Test Project',
        description: 'Test Description',
        workflowConfig: undefined,
        createdAt: '2025-01-01T00:00:00Z',
        updatedAt: '2025-01-01T00:00:00Z',
      }
      resolveUpdate(mockProject)
      await savePromise
    })

    // Retry behavior is verified at API layer; flow-slice calls API once.
  })

  describe('loadWorkflowIntoCanvas', () => {
    it('should successfully load a project with workflow config', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const mockVersionedConfig = {
        schema_info: {
          version: '1.0.0',
          compatibility: '>=1.0.0',
          schema_name: 'WorkflowConfig',
        },
        data: {
          metadata: {
            lastModified: '2025-01-01T00:00:00Z',
          },
          nodes: [],
          edges: [],
        },
      }

      const mockProject: Project = {
        id: projectId,
        siteId: 'test-site-123',
        name: 'Test Project',
        description: 'Test Description',
        workflowConfig: mockVersionedConfig,
        createdAt: '2025-01-01T00:00:00Z',
        updatedAt: '2025-01-01T00:00:00Z',
      }

      const mockDeserializedState = {
        nodes: [],
        edges: [],
        metadata: {
          lastModified: '2025-01-01T00:00:00Z',
        },
      }

      mockProjectsApi.get.mockResolvedValue(mockProject)
      mockDeserializeWorkflow.mockReturnValue(mockDeserializedState)

      // Act
      await store.getState().loadWorkflowIntoCanvas({
        orgId: 'test-org',
        siteId: 'test-site',
        projectId,
      })

      // Assert
      expect(store.getState().saveStatus).toBe('saved')
      expect(mockProjectsApi.get).toHaveBeenCalledWith({
        orgId: 'test-org',
        siteId: 'test-site',
        projectId,
      })
      expect(mockDeserializeWorkflow).toHaveBeenCalledWith(
        expect.objectContaining({
          versionedConfig: mockVersionedConfig,
          mqttBus: expect.any(Object),
          onDataChange: expect.any(Function),
        })
      )
    })

    it('should handle empty workflow config', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const mockProject: Project = {
        id: projectId,
        siteId: 'test-site-123',
        name: 'Test Project',
        description: 'Test Description',
        workflowConfig: undefined,
        createdAt: '2025-01-01T00:00:00Z',
        updatedAt: '2025-01-01T00:00:00Z',
      }

      mockProjectsApi.get.mockResolvedValue(mockProject)

      // Act
      await store.getState().loadWorkflowIntoCanvas({
        orgId: 'test-org',
        siteId: 'test-site',
        projectId,
      })

      // Assert
      expect(store.getState().saveStatus).toBe('saved')
      expect(store.getState().nodes).toEqual([])
      expect(store.getState().edges).toEqual([])
      expect(mockDeserializeWorkflow).not.toHaveBeenCalled()
    })

    it('should set saveStatus to error when load fails', async () => {
      // Arrange
      const projectId = 'test-project-123'
      const error = new Error('API Error')
      mockProjectsApi.get.mockRejectedValue(error)

      // Act & Assert
      await expect(
        store.getState().loadWorkflowIntoCanvas({
          orgId: 'test-org',
          siteId: 'test-site',
          projectId,
        })
      ).rejects.toThrow('API Error')
      expect(store.getState().saveStatus).toBe('error')
    })

    // Retry behavior is verified at API layer; flow-slice calls API once.
  })

  describe('initial state', () => {
    it('should initialize with unsaved status', () => {
      expect(store.getState().saveStatus).toBe('unsaved')
    })
  })
})
