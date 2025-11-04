import { useQuery } from '@tanstack/react-query'
import { mockBuildingMOTIFService } from '../services/mock-buildingmotif.service'
import { semanticQueryKeys } from './query-keys'

export function useEquipmentTypesQuery() {
  return useQuery({
    queryKey: semanticQueryKeys.templates.equipmentTypes(),
    queryFn: () => mockBuildingMOTIFService.getTemplates(),
    staleTime: Infinity,
  })
}

export function useDeviceTypesQuery() {
  return useQuery({
    queryKey: semanticQueryKeys.templates.deviceTypes(),
    queryFn: () => mockBuildingMOTIFService.getDeviceTypes(),
    staleTime: Infinity,
  })
}

export function useObservablePropertiesQuery() {
  return useQuery({
    queryKey: semanticQueryKeys.templates.observableProperties(),
    queryFn: () => mockBuildingMOTIFService.getObservableProperties(),
    staleTime: Infinity,
  })
}
