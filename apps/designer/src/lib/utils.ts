import { clsx, type ClassValue } from 'clsx'
import { twMerge } from 'tailwind-merge'

export function cn(...inputs: ClassValue[]) {
  return twMerge(clsx(inputs))
}

/**
 * Converts camelCase string to human-readable label.
 *
 * @example
 * camelToLabel('zoneTemperature') // 'Zone Temperature'
 * camelToLabel('hasCO2Sensor') // 'Has CO2 Sensor'
 * camelToLabel('maxCoolingAirflow') // 'Max Cooling Airflow'
 */
export function camelToLabel(camelCase: string): string {
  return camelCase
    .replace(/CO2/g, 'Co2')
    .replace(/([A-Z])/g, ' $1')
    .replace(/^./, (str) => str.toUpperCase())
    .replace(/Co2/g, 'CO2')
    .trim()
}
