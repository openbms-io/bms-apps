import { SignJWT, jwtVerify } from 'jose'

export interface IOTDeviceJWTPayload {
  orgId: string
  siteId: string
  iotDeviceId: string
  scope: string
  [key: string]: unknown
}

export function buildIOTDeviceJWTPayload({
  orgId,
  siteId,
  iotDeviceId,
}: {
  orgId: string
  siteId: string
  iotDeviceId: string
}): IOTDeviceJWTPayload {
  return {
    orgId,
    siteId,
    iotDeviceId,
    scope: 'upload-config',
  }
}

export async function encodeJWT(
  payload: IOTDeviceJWTPayload,
  expiresIn = '1h'
): Promise<string> {
  const secret = process.env.JWT_SECRET

  if (!secret) {
    throw new Error('JWT_SECRET is not configured')
  }

  const secretKey = new TextEncoder().encode(secret)

  const jwt = await new SignJWT(payload)
    .setProtectedHeader({ alg: 'HS256' })
    .setIssuedAt()
    .setExpirationTime(expiresIn)
    .sign(secretKey)

  return jwt
}

export async function decodeJWT(token: string): Promise<IOTDeviceJWTPayload> {
  const secret = process.env.JWT_SECRET

  if (!secret) {
    throw new Error('JWT_SECRET is not configured')
  }

  const secretKey = new TextEncoder().encode(secret)

  const { payload } = await jwtVerify(token, secretKey)

  return payload as IOTDeviceJWTPayload
}
