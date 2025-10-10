export type IotDevice = {
  id: string
  organizationId: string
  siteId: string
  name: string
  description?: string
  createdAt: string
  updatedAt: string
}

export type CreateIotDevice = {
  organizationId: string
  siteId: string
  name: string
  description?: string
}

export type UpdateIotDevice = {
  name?: string
  description?: string | null
}
