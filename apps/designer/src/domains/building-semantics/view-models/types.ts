export interface EquipmentViewModel {
  pointName: string
  equipmentTypeId: string
  deviceTypeId: string
  propertyId: string
  propertyType: 'quantifiable' | 'enumerated'
  physicalSpaceLabel?: string
  domainSpaceLabels?: string[]
  hasMapping: boolean
}

export interface SpaceViewModel {
  id: string
  label: string
  type: 'PhysicalSpace' | 'DomainSpace'
  pointCount: number
  createdAt: Date
}

export interface TemplatesViewModel {
  equipmentTypeIds: string[]
  deviceTypeIds: string[]
  propertyIds: string[]
  isLoading: boolean
}

export interface CreateMappingParams {
  projectId: string
  pointId: string
  equipmentTypeId: string
  deviceTypeId: string
  propertyId: string
  propertyType: 'quantifiable' | 'enumerated'
  physicalSpaceName?: string
  domainSpaceNames?: string[]
  externalReference: {
    deviceIdentifier?: string
    deviceName?: string
    objectIdentifier?: string
    objectName?: string
    propertyIdentifier?: string
    propertyArrayIndex?: number
    priorityForWriting?: number
  }
}
