jest.mock('jose')

import { encodeJWT, decodeJWT, buildIOTDeviceJWTPayload } from './jwt'

describe('JWT Utilities', () => {
  const mockPayload = {
    orgId: 'org_123',
    siteId: 'site_456',
    iotDeviceId: 'device_789',
    scope: 'upload-config',
  }

  beforeAll(() => {
    process.env.JWT_SECRET =
      'test-secret-key-minimum-32-characters-long-for-hs256'
  })

  describe('encodeJWT and decodeJWT', () => {
    it('should encode and decode JWT with correct payload', async () => {
      const token = await encodeJWT(mockPayload)

      expect(token).toBeDefined()
      expect(typeof token).toBe('string')

      const decoded = await decodeJWT(token)

      expect(decoded.orgId).toBe(mockPayload.orgId)
      expect(decoded.siteId).toBe(mockPayload.siteId)
      expect(decoded.iotDeviceId).toBe(mockPayload.iotDeviceId)
      expect(decoded.scope).toBe(mockPayload.scope)
    })

    it('should throw error for expired token', async () => {
      await expect(decodeJWT('expired.token')).rejects.toThrow()
    })

    it('should throw error for invalid token', async () => {
      const invalidToken = 'invalid.token.here'

      await expect(decodeJWT(invalidToken)).rejects.toThrow()
    })

    it('should throw error if JWT_SECRET is not set', async () => {
      const originalSecret = process.env.JWT_SECRET
      delete process.env.JWT_SECRET

      await expect(encodeJWT(mockPayload)).rejects.toThrow(
        'JWT_SECRET is not configured'
      )

      process.env.JWT_SECRET = originalSecret
    })
  })

  describe('buildIOTDeviceJWTPayload', () => {
    it('should build correct payload structure', () => {
      const payload = buildIOTDeviceJWTPayload({
        orgId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
      })

      expect(payload).toEqual({
        orgId: 'org_123',
        siteId: 'site_456',
        iotDeviceId: 'device_789',
        scope: 'upload-config',
      })
    })
  })
})
