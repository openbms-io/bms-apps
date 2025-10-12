import { ConfigUploadSchema } from './schemas'

describe('ConfigUploadSchema', () => {
  it('should validate correct upload payload', () => {
    const validPayload = {
      config: [
        {
          vendor_id: 123,
          device_id: 1001,
          controller_id: 'ctrl_1',
          controller_ip_address: '192.168.1.101',
          object_list: [
            {
              type: 'analogInput',
              point_id: 0,
              iot_device_point_id: 'point_1',
              properties: {
                objectIdentifier: ['analog-input', 0],
                objectName: 'Temperature',
                presentValue: 72.5,
                objectType: 'analogInput',
                statusFlags: '0000',
                outOfService: 0,
              },
            },
          ],
        },
      ],
    }

    const result = ConfigUploadSchema.safeParse(validPayload)
    expect(result.success).toBe(true)
  })

  it('should reject payload with missing required fields', () => {
    const invalidPayload = {
      organization_id: 'org_123',
      // Missing site_id, iot_device_id, etc.
    }

    const result = ConfigUploadSchema.safeParse(invalidPayload)
    expect(result.success).toBe(false)
  })

  it('should accept optional point fields', () => {
    const payloadWithOptionals = {
      config: [
        {
          vendor_id: 456,
          device_id: 1001,
          controller_id: 'ctrl_1',
          controller_ip_address: '192.168.1.101',
          object_list: [
            {
              type: 'analogInput',
              point_id: 0,
              iot_device_point_id: 'point_1',
              properties: {
                objectIdentifier: ['analog-input', 0],
                objectName: 'Temperature',
                presentValue: 72.5,
                objectType: 'analogInput',
                statusFlags: '0000',
                units: 'degreesFahrenheit',
                description: 'Room temperature sensor',
                outOfService: 0,
              },
            },
          ],
        },
      ],
    }

    const result = ConfigUploadSchema.safeParse(payloadWithOptionals)
    expect(result.success).toBe(true)
  })
})
