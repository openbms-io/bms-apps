/* eslint-disable @typescript-eslint/no-unused-vars */
import type {
  TemplatesResponseDto,
  TemplateSystemDto,
  TemplateDeviceDto,
  TemplatePropertyDto,
  SpaceTypeDto,
  SemanticMappingDto,
  MappingsResponseDto,
  SaveMappingsRequestDto,
  SpaceInstanceDto,
  CreateSpaceRequestDto,
} from './generated'

import {
  getTemplatesApiV1223pTemplatesGet,
  getMappingsApiV1223pMappingsGet,
  saveMappingsApiV1223pMappingsPost,
  listSpacesApiV1223pSpacesGet,
  createSpaceApiV1223pSpacesPost,
} from './generated'

// Type checking verification (hierarchical structure)
const templatesResponse: TemplatesResponseDto = {
  systems: [
    {
      id: 'urn:223p:VAVReheatTerminalUnit',
      label: 'VAV with Reheat',
      description: 'Test',
      devices: [
        {
          id: 'urn:223p:Damper',
          label: 'Damper',
          description: null,
          properties: [
            {
              id: 'urn:223p:DamperPosition',
              label: 'Damper Position',
              propertyType: 'quantifiable',
              description: null,
            },
          ],
        },
      ],
    },
  ],
  spaceTypes: [
    {
      id: 'urn:223p:Office',
      label: 'Office',
      description: null,
    },
  ],
}

// Mapping types verification (camelCase)
const mapping: SemanticMappingDto = {
  equipmentTypeId: 'urn:223p:VAVReheatTerminalUnit',
  deviceTypeId: 'urn:223p:Damper',
  propertyId: 'urn:223p:DamperPosition',
  spaceId: 'urn:bms:PhysicalSpace:room-101',
}

const mappingsResponse: MappingsResponseDto = {
  projectId: 'project-1',
  mappings: {
    'device-1:ai-1': mapping,
  },
}

// Space types verification
const spaceInstance: SpaceInstanceDto = {
  id: 'urn:bms:PhysicalSpace:room-101',
  spaceTypeId: 'urn:223p:Office',
  label: 'Room 101',
  createdAt: '2025-01-01T00:00:00Z',
}

// Service verification
async function testServices() {
  const templates = await getTemplatesApiV1223pTemplatesGet()
  const mappings = await getMappingsApiV1223pMappingsGet({
    query: { projectId: 'project-1' },
  })
  await saveMappingsApiV1223pMappingsPost({
    body: {
      projectId: 'project-1',
      mappings: {},
    },
  })
  const spaces = await listSpacesApiV1223pSpacesGet({
    query: { projectId: 'project-1' },
  })
  await createSpaceApiV1223pSpacesPost({
    body: {
      projectId: 'project-1',
      spaceTypeId: 'urn:223p:Office',
      label: 'Room 101',
    },
  })
}

export {}
