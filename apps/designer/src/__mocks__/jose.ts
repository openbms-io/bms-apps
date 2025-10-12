export class SignJWT {
  private payload: unknown

  constructor(payload: unknown) {
    this.payload = payload
  }

  setProtectedHeader() {
    return this
  }

  setIssuedAt() {
    return this
  }

  setExpirationTime() {
    return this
  }

  async sign() {
    return 'mocked.jwt.token'
  }
}

export async function jwtVerify(token: string) {
  if (token === 'invalid.token.here') {
    throw new Error('Invalid token')
  }
  if (token === 'expired.token') {
    throw new Error('Token expired')
  }
  return {
    payload: {
      orgId: 'org_123',
      siteId: 'site_456',
      iotDeviceId: 'device_789',
      scope: 'upload-config',
    },
  }
}
