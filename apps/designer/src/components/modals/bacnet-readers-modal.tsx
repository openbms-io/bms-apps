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
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select'
import { Trash2 } from 'lucide-react'
import {
  useBacnetReaders,
  useCreateBacnetReader,
  useDeleteBacnetReader,
} from '@/hooks/use-bacnet-readers'
import { toast } from 'sonner'

interface BacnetReadersModalProps {
  open: boolean
  onOpenChange: (open: boolean) => void
  orgId: string
  siteId: string
  projectId: string
  iotDeviceId: string
}

export function BacnetReadersModal({
  open,
  onOpenChange,
  orgId,
  siteId,
  projectId,
  iotDeviceId,
}: BacnetReadersModalProps) {
  const [formData, setFormData] = useState({
    name: '',
    ipAddress: '',
    port: '47808',
    deviceId: '',
    subnetMask: '24' as '8' | '16' | '24' | '28' | '30',
    bbmdEnabled: false,
    bbmdServerIp: '',
    isActive: true,
  })

  const { data: readers, isLoading } = useBacnetReaders(
    orgId,
    siteId,
    projectId,
    iotDeviceId
  )
  const createMutation = useCreateBacnetReader()
  const deleteMutation = useDeleteBacnetReader()

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

    const subnetMask = parseInt(formData.subnetMask) as 8 | 16 | 24 | 28 | 30

    if (formData.bbmdEnabled && !formData.bbmdServerIp) {
      toast.error('BBMD Server IP is required when BBMD is enabled')
      return
    }

    if (formData.bbmdServerIp) {
      const ipRegex = /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
      if (!ipRegex.test(formData.bbmdServerIp)) {
        toast.error('Invalid BBMD Server IP address format')
        return
      }
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
          subnetMask,
          bbmdEnabled: formData.bbmdEnabled,
          bbmdServerIp: formData.bbmdServerIp || undefined,
          isActive: formData.isActive,
        },
      })

      toast.success('BACnet reader added successfully')
      setFormData({
        name: '',
        ipAddress: '',
        port: '47808',
        deviceId: '',
        subnetMask: '24' as '8' | '16' | '24' | '28' | '30',
        bbmdEnabled: false,
        bbmdServerIp: '',
        isActive: true,
      })
    } catch (error) {
      toast.error(
        error instanceof Error ? error.message : 'Failed to add BACnet reader'
      )
    }
  }

  const handleDelete = async (readerId: string) => {
    try {
      await deleteMutation.mutateAsync({
        orgId,
        siteId,
        projectId,
        iotDeviceId,
        readerId,
      })
      toast.success('BACnet reader deleted successfully')
    } catch (error) {
      toast.error(
        error instanceof Error
          ? error.message
          : 'Failed to delete BACnet reader'
      )
    }
  }

  return (
    <Dialog open={open} onOpenChange={onOpenChange}>
      <DialogContent className="max-w-2xl max-h-[80vh] overflow-y-auto">
        <DialogHeader>
          <DialogTitle>BACnet Reader Network Interface</DialogTitle>
          <DialogDescription>
            Configure network interfaces for BACnet/IP communication.
          </DialogDescription>
        </DialogHeader>

        <div className="space-y-6">
          <div className="border rounded-lg p-4">
            <h3 className="text-sm font-semibold mb-4">
              Add Network Interface
            </h3>
            <form onSubmit={handleSubmit} className="space-y-4">
              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="reader-name" className="text-right">
                  Name *
                </Label>
                <Input
                  id="reader-name"
                  value={formData.name}
                  onChange={(e) =>
                    setFormData({ ...formData, name: e.target.value })
                  }
                  placeholder="Reader 1"
                  className="col-span-3"
                  required
                />
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="reader-ip" className="text-right">
                  IP Address *
                </Label>
                <Input
                  id="reader-ip"
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
                <Label htmlFor="reader-port" className="text-right">
                  Port *
                </Label>
                <Input
                  id="reader-port"
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
                <Label htmlFor="reader-device-id" className="text-right">
                  Device ID *
                </Label>
                <Input
                  id="reader-device-id"
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
                <Label htmlFor="reader-subnet" className="text-right">
                  Subnet Mask *
                </Label>
                <Select
                  value={formData.subnetMask}
                  onValueChange={(value) =>
                    setFormData({
                      ...formData,
                      subnetMask: value as '8' | '16' | '24' | '28' | '30',
                    })
                  }
                >
                  <SelectTrigger className="col-span-3">
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent>
                    <SelectItem value="8">/8 (255.0.0.0)</SelectItem>
                    <SelectItem value="16">/16 (255.255.0.0)</SelectItem>
                    <SelectItem value="24">/24 (255.255.255.0)</SelectItem>
                    <SelectItem value="28">/28 (255.255.255.240)</SelectItem>
                    <SelectItem value="30">/30 (255.255.255.252)</SelectItem>
                  </SelectContent>
                </Select>
              </div>

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="reader-bbmd" className="text-right">
                  BBMD Enabled
                </Label>
                <div className="col-span-3">
                  <Switch
                    id="reader-bbmd"
                    checked={formData.bbmdEnabled}
                    onCheckedChange={(checked) =>
                      setFormData({ ...formData, bbmdEnabled: checked })
                    }
                  />
                </div>
              </div>

              {formData.bbmdEnabled && (
                <div className="grid grid-cols-4 items-center gap-4">
                  <Label htmlFor="reader-bbmd-ip" className="text-right">
                    BBMD Server IP *
                  </Label>
                  <Input
                    id="reader-bbmd-ip"
                    value={formData.bbmdServerIp}
                    onChange={(e) =>
                      setFormData({ ...formData, bbmdServerIp: e.target.value })
                    }
                    placeholder="192.168.1.1"
                    className="col-span-3"
                  />
                </div>
              )}

              <div className="grid grid-cols-4 items-center gap-4">
                <Label htmlFor="reader-active" className="text-right">
                  Active
                </Label>
                <div className="col-span-3">
                  <Switch
                    id="reader-active"
                    checked={formData.isActive}
                    onCheckedChange={(checked) =>
                      setFormData({ ...formData, isActive: checked })
                    }
                  />
                </div>
              </div>

              <div className="flex justify-end">
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
                  {createMutation.isPending ? 'Adding...' : 'Add Interface'}
                </Button>
              </div>
            </form>
          </div>

          <div className="border rounded-lg p-4">
            <h3 className="text-sm font-semibold mb-4">
              Configured Interfaces
            </h3>
            {isLoading ? (
              <div className="text-sm text-muted-foreground text-center py-4">
                Loading interfaces...
              </div>
            ) : !readers || readers.length === 0 ? (
              <div className="text-sm text-muted-foreground text-center py-4">
                No interfaces configured
              </div>
            ) : (
              <div className="space-y-2">
                {readers.map((reader) => (
                  <div
                    key={reader.id}
                    className="flex items-center justify-between p-3 border rounded-lg hover:bg-muted/50"
                  >
                    <div className="flex-1">
                      <div className="flex items-center gap-2">
                        <span className="font-medium text-sm">
                          {reader.name}
                        </span>
                        {!reader.isActive && (
                          <span className="text-xs px-2 py-0.5 rounded bg-gray-200 text-gray-600">
                            Inactive
                          </span>
                        )}
                      </div>
                      <div className="text-xs text-muted-foreground mt-1">
                        {reader.ipAddress}:{reader.port} | Device ID:{' '}
                        {reader.deviceId} | Subnet: /{reader.subnetMask}
                        {reader.bbmdEnabled &&
                          ` | BBMD: ${reader.bbmdServerIp ?? 'N/A'}`}
                      </div>
                    </div>
                    <Button
                      variant="ghost"
                      size="icon"
                      onClick={() => handleDelete(reader.id)}
                      disabled={deleteMutation.isPending}
                      className="h-8 w-8 text-red-500 hover:text-red-700 hover:bg-red-50"
                    >
                      <Trash2 className="h-4 w-4" />
                    </Button>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>

        <DialogFooter>
          <Button variant="outline" onClick={() => onOpenChange(false)}>
            Close
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  )
}
