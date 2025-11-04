'use client'

import { useState } from 'react'
import { Button } from '@/components/ui/button'
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card'
import { MappingPopupModal } from '@/domains/building-semantics/components'
import type {
  BACnetPointData,
  SemanticEquipment,
  BACnetControllerData,
} from '@/domains/building-semantics'

const samplePoints: BACnetPointData[] = [
  {
    pointId: 'bfc8f7b0-6186-5eb2-9ef1-a3c2ec7a4382',
    objectType: 'analog-input',
    objectId: 1,
    supervisorId: 'd7b702fc-a3df-4126-83ef-ee8722cf89d3',
    controllerId: '1a897c64-b763-4139-a82b-6a7ef550709a',
    name: 'VAV-2-01_ZoneTemp',
    discoveredProperties: {
      objectIdentifier: ['analog-input', 1],
      objectName: 'VAV-2-01_ZoneTemp',
      presentValue: 72.3,
      objectType: 'analog-input',
      description: 'Zone Temperature Sensor',
      units: 'degrees-fahrenheit',
      statusFlags: [0, 0, 0, 0],
      inAlarm: false,
      fault: false,
      overridden: false,
      outOfService: false,
    },
  },
  {
    pointId: 'cfc8f7b0-6186-5eb2-9ef1-a3c2ec7a4383',
    objectType: 'analog-output',
    objectId: 2,
    supervisorId: 'd7b702fc-a3df-4126-83ef-ee8722cf89d3',
    controllerId: '1a897c64-b763-4139-a82b-6a7ef550709a',
    name: 'VAV-2-01_DamperPos',
    discoveredProperties: {
      objectIdentifier: ['analog-output', 2],
      objectName: 'VAV-2-01_DamperPos',
      presentValue: 45.5,
      objectType: 'analog-output',
      description: 'Damper Position Actuator',
      units: 'percent',
      statusFlags: [0, 0, 0, 0],
      priorityArray: [
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
      ],
      relinquishDefault: 0,
      inAlarm: false,
      fault: false,
      overridden: false,
      outOfService: false,
    },
  },
  {
    pointId: 'dfc8f7b0-6186-5eb2-9ef1-a3c2ec7a4384',
    objectType: 'analog-input',
    objectId: 3,
    supervisorId: 'd7b702fc-a3df-4126-83ef-ee8722cf89d3',
    controllerId: '2a897c64-b763-4139-a82b-6a7ef550709b',
    name: 'AHU-1_SupplyTemp',
    discoveredProperties: {
      objectIdentifier: ['analog-input', 3],
      objectName: 'AHU-1_SupplyTemp',
      presentValue: 55.0,
      objectType: 'analog-input',
      units: 'degrees-fahrenheit',
      statusFlags: [0, 0, 0, 0],
      inAlarm: false,
      fault: false,
      overridden: false,
      outOfService: false,
    },
  },
  {
    pointId: 'efc8f7b0-6186-5eb2-9ef1-a3c2ec7a4385',
    objectType: 'analog-value',
    objectId: 4,
    supervisorId: 'd7b702fc-a3df-4126-83ef-ee8722cf89d3',
    controllerId: '3a897c64-b763-4139-a82b-6a7ef550709c',
    name: 'time',
    discoveredProperties: {
      objectIdentifier: ['analog-value', 4],
      objectName: 'time',
      presentValue: 25,
      objectType: 'analog-value',
      statusFlags: [0, 0, 0, 0],
      priorityArray: [
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        null,
      ],
      relinquishDefault: 0,
      inAlarm: false,
      fault: false,
      overridden: false,
      outOfService: false,
    },
  },
]

const mockController: BACnetControllerData = {
  deviceId: 123,
  controllerId: '1a897c64-b763-4139-a82b-6a7ef550709a',
  name: 'VAV-2-01 Controller',
}

export default function Test223PModalPage() {
  const [showModal, setShowModal] = useState(false)
  const [selectedPoint, setSelectedPoint] = useState<BACnetPointData | null>(
    null
  )
  const [savedMappings, setSavedMappings] = useState<
    Record<string, SemanticEquipment>
  >({})

  const handleOpenModal = (point: BACnetPointData) => {
    setSelectedPoint(point)
    setShowModal(true)
  }

  const handleConfirm = (mapping: SemanticEquipment) => {
    if (selectedPoint) {
      setSavedMappings((prev) => ({
        ...prev,
        [selectedPoint.pointId]: mapping,
      }))
      sessionStorage.setItem(
        `semantic-${selectedPoint.pointId}`,
        JSON.stringify(mapping)
      )
    }
    setShowModal(false)
  }

  const handleSkip = () => {
    setShowModal(false)
  }

  return (
    <div className="container mx-auto p-8 space-y-8">
      <div>
        <h1 className="text-3xl font-bold mb-2">223P Mapping Modal Test</h1>
        <p className="text-muted-foreground">
          Click on any BACnet point below to open the 223P mapping modal with AI
          suggestions.
        </p>
      </div>

      <div className="grid gap-4 md:grid-cols-2">
        {samplePoints.map((point) => {
          const hasMapp = savedMappings[point.pointId]
          return (
            <Card
              key={point.pointId}
              className={hasMapp ? 'border-green-500' : ''}
            >
              <CardHeader>
                <CardTitle className="text-base flex items-center justify-between">
                  <span>{point.name}</span>
                  {hasMapp && (
                    <span className="text-xs bg-green-100 text-green-800 px-2 py-1 rounded">
                      Tagged
                    </span>
                  )}
                </CardTitle>
              </CardHeader>
              <CardContent className="space-y-2">
                <div className="text-sm text-muted-foreground">
                  <div>Type: {point.objectType}</div>
                  <div>Controller: {point.controllerId}</div>
                  {point.discoveredProperties?.presentValue !== undefined && (
                    <div>
                      Value: {point.discoveredProperties.presentValue}{' '}
                      {point.discoveredProperties.units}
                    </div>
                  )}
                </div>
                {hasMapp ? (
                  <div className="space-y-1 text-sm pt-2 border-t">
                    <div className="font-medium">Mapped to:</div>
                    <div className="text-muted-foreground">
                      <div>Equipment: {hasMapp.equipmentType}</div>
                      <div>Device: {hasMapp.deviceType}</div>
                      <div>Property: {hasMapp.observableProperty}</div>
                    </div>
                  </div>
                ) : (
                  <Button
                    onClick={() => handleOpenModal(point)}
                    className="w-full mt-2"
                  >
                    Tag with 223P
                  </Button>
                )}
              </CardContent>
            </Card>
          )
        })}
      </div>

      <MappingPopupModal
        projectId="demo-project"
        open={showModal}
        point={selectedPoint}
        controller={mockController}
        onConfirm={handleConfirm}
        onSkip={handleSkip}
        onOpenChange={setShowModal}
      />
    </div>
  )
}
