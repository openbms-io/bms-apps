export type Organization = {
  id: string
  name: string
  createdAt: string
  updatedAt: string
}

export type CreateOrganization = {
  name: string
}

export type UpdateOrganization = {
  name?: string
}
