'use client'

import { useState } from 'react'
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogFooter,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog'
import { Button } from '@/components/ui/button'
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import { Switch } from '@/components/ui/switch'
import { useCreateIotDeviceController } from '@/hooks/use-iot-device-controllers'
import { toast } from 'sonner'

interface AddControllerDialogProps {
  open: boolean
  onOpenChange: (open: boolean) => void
  orgId: string
  siteId: string
  projectId: string
  iotDeviceId: string
}

export function AddControllerDialog({
  open,
  onOpenChange,
  orgId,
  siteId,
  projectId,
  iotDeviceId,
}: AddControllerDialogProps) {
  const [formData, setFormData] = useState({
    name: '',
    ipAddress: '',
    port: '47808',
    deviceId: '',
    networkNumber: '',
    macAddress: '',
    isActive: true,
  })

  const createMutation = useCreateIotDeviceController()

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault()

    const ipRegex = /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
    if (!ipRegex.test(formData.ipAddress)) {
      toast.error('Invalid IP address format')
      return
    }

    const port = parseInt(formData.port)
    if (isNaN(port) || port < 1 || port > 65535) {
      toast.error('Port must be between 1 and 65535')
      return
    }

    const deviceId = parseInt(formData.deviceId)
    if (isNaN(deviceId) || deviceId < 0) {
      toast.error('Device ID must be a positive number')
      return
    }

    const networkNumber = formData.networkNumber
      ? parseInt(formData.networkNumber)
      : undefined
    if (
      networkNumber !== undefined &&
      (isNaN(networkNumber) || networkNumber < 0)
    ) {
      toast.error('Network number must be a positive number')
      return
    }

    try {
      await createMutation.mutateAsync({
        orgId,
        siteId,
        projectId,
        iotDeviceId,
        data: {
          name: formData.name,
          ipAddress: formData.ipAddress,
          port,
          deviceId,
          networkNumber,
          macAddress: formData.macAddress || undefined,
          isActive: formData.isActive,
        },
      })

      toast.success('Controller added successfully')
      setFormData({
        name: '',
        ipAddress: '',
        port: '47808',
        deviceId: '',
        networkNumber: '',
        macAddress: '',
        isActive: true,
      })
      onOpenChange(false)
    } catch (error) {
      toast.error(
        error instanceof Error ? error.message : 'Failed to add controller'
      )
    }
  }

  return (
    <Dialog open={open} onOpenChange={onOpenChange}>
      <DialogContent className="max-w-md">
        <DialogHeader>
          <DialogTitle>Add New Controller</DialogTitle>
          <DialogDescription>
            Configure the BACnet controller settings.
          </DialogDescription>
        </DialogHeader>
        <form onSubmit={handleSubmit}>
          <div className="grid gap-4 py-4">
            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="name" className="text-right">
                Name *
              </Label>
              <Input
                id="name"
                value={formData.name}
                onChange={(e) =>
                  setFormData({ ...formData, name: e.target.value })
                }
                placeholder="Main Controller"
                className="col-span-3"
                required
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="ip-address" className="text-right">
                IP Address *
              </Label>
              <Input
                id="ip-address"
                value={formData.ipAddress}
                onChange={(e) =>
                  setFormData({ ...formData, ipAddress: e.target.value })
                }
                placeholder="192.168.1.100"
                className="col-span-3"
                required
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="port" className="text-right">
                Port *
              </Label>
              <Input
                id="port"
                type="number"
                value={formData.port}
                onChange={(e) =>
                  setFormData({ ...formData, port: e.target.value })
                }
                placeholder="47808"
                className="col-span-3"
                required
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="device-id" className="text-right">
                Device ID *
              </Label>
              <Input
                id="device-id"
                type="number"
                value={formData.deviceId}
                onChange={(e) =>
                  setFormData({ ...formData, deviceId: e.target.value })
                }
                placeholder="123456"
                className="col-span-3"
                required
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="network-number" className="text-right">
                Network Number
              </Label>
              <Input
                id="network-number"
                type="number"
                value={formData.networkNumber}
                onChange={(e) =>
                  setFormData({ ...formData, networkNumber: e.target.value })
                }
                placeholder="Optional"
                className="col-span-3"
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="mac-address" className="text-right">
                MAC Address
              </Label>
              <Input
                id="mac-address"
                value={formData.macAddress}
                onChange={(e) =>
                  setFormData({ ...formData, macAddress: e.target.value })
                }
                placeholder="Optional"
                className="col-span-3"
              />
            </div>

            <div className="grid grid-cols-4 items-center gap-4">
              <Label htmlFor="is-active" className="text-right">
                Active
              </Label>
              <div className="col-span-3">
                <Switch
                  id="is-active"
                  checked={formData.isActive}
                  onCheckedChange={(checked) =>
                    setFormData({ ...formData, isActive: checked })
                  }
                />
              </div>
            </div>
          </div>
          <DialogFooter>
            <Button
              type="submit"
              disabled={
                !formData.name ||
                !formData.ipAddress ||
                !formData.port ||
                !formData.deviceId ||
                createMutation.isPending
              }
            >
              {createMutation.isPending ? 'Adding...' : 'Add Controller'}
            </Button>
          </DialogFooter>
        </form>
      </DialogContent>
    </Dialog>
  )
}
