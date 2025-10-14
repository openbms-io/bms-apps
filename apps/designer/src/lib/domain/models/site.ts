export type Site = {
  id: string
  organizationId: string
  name: string
  description?: string
  createdAt: string
  updatedAt: string
}

export type CreateSite = {
  organizationId: string
  name: string
  description?: string
}

export type UpdateSite = {
  name?: string
  description?: string | null
}
