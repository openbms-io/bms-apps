export enum ResourceType {
  BacnetReader = 'bacnetReader',
  Controller = 'controller',
  ControllerPoint = 'controllerPoint',
  DeviceConfig = 'deviceConfig',
}

export interface RouteParams {
  resourceType: ResourceType
  resourceId: string
  orgId: string
  siteId: string
  iotDeviceId: string
}

const ROUTE_PATTERNS = [
  {
    pattern:
      /^\/api\/organizations\/([^\/]+)\/sites\/([^\/]+)\/projects\/([^\/]+)\/iot-devices\/([^\/]+)\/bacnet-readers\/([^\/]+)/,
    resourceType: ResourceType.BacnetReader,
  },
  {
    pattern:
      /^\/api\/organizations\/([^\/]+)\/sites\/([^\/]+)\/projects\/([^\/]+)\/iot-devices\/([^\/]+)\/controllers\/([^\/]+)\/points\/([^\/]+)/,
    resourceType: ResourceType.ControllerPoint,
  },
  {
    pattern:
      /^\/api\/organizations\/([^\/]+)\/sites\/([^\/]+)\/projects\/([^\/]+)\/iot-devices\/([^\/]+)\/controllers\/([^\/]+)/,
    resourceType: ResourceType.Controller,
  },
  {
    pattern:
      /^\/api\/organizations\/([^\/]+)\/sites\/([^\/]+)\/projects\/([^\/]+)\/iot-devices\/([^\/]+)\/configs\/([^\/]+)/,
    resourceType: ResourceType.DeviceConfig,
  },
]

export function matchRoute({
  pathname,
}: {
  pathname: string
}): RouteParams | null {
  for (const { pattern, resourceType } of ROUTE_PATTERNS) {
    const match = pathname.match(pattern)
    if (match) {
      if (resourceType === ResourceType.ControllerPoint) {
        return {
          resourceType,
          orgId: match[1],
          siteId: match[2],
          iotDeviceId: match[4],
          resourceId: match[6],
        }
      }
      return {
        resourceType,
        orgId: match[1],
        siteId: match[2],
        iotDeviceId: match[4],
        resourceId: match[5],
      }
    }
  }
  return null
}
