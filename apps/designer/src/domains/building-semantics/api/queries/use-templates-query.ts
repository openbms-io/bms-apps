import { useQuery } from '@tanstack/react-query'
import { mockBuildingMOTIFService } from '../services/mock-buildingmotif.service'
import { queryKeys223p } from './query-keys'

export function useEquipmentTypesQuery() {
  return useQuery({
    queryKey: queryKeys223p.templates.equipmentTypes(),
    queryFn: () => mockBuildingMOTIFService.getTemplates(),
    staleTime: Infinity,
  })
}

export function useDeviceTypesQuery() {
  return useQuery({
    queryKey: queryKeys223p.templates.deviceTypes(),
    queryFn: () => mockBuildingMOTIFService.getDeviceTypes(),
    staleTime: Infinity,
  })
}

export function useObservablePropertiesQuery() {
  return useQuery({
    queryKey: queryKeys223p.templates.observableProperties(),
    queryFn: () => mockBuildingMOTIFService.getObservableProperties(),
    staleTime: Infinity,
  })
}
