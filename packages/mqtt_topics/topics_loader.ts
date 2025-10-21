import mqttTopics from './topics.json';

// TopicConfig interface matching Python TopicConfig
export interface TopicConfig {
  topic: string;
  qos: number;
  retain: boolean;
}

// Type for the structure of topics.json with replaced values
export type AllTopics = {
  command: {
    get_config: {
      request: TopicConfig;
      response: TopicConfig;
    };
    reboot: {
      request: TopicConfig;
      response: TopicConfig;
    };
    set_value_to_point: {
      request: TopicConfig;
      response: TopicConfig;
    };
    start_monitoring: {
      request: TopicConfig;
      response: TopicConfig;
    };
    stop_monitoring: {
      request: TopicConfig;
      response: TopicConfig;
    };
  };
  status: {
    heartbeat: TopicConfig;
  };
  data: {
    point: TopicConfig | null;
    point_bulk: TopicConfig;
  };
  alert_management: {
    acknowledge: TopicConfig;
    resolve: TopicConfig;
  };
};

// Strongly typed params for all possible placeholders in topics.json
export type TopicParams = {
  organization_id?: string;
  site_id?: string;
  iot_device_id?: string;
  controller_device_id?: string;
  iot_device_point_id?: string;
  tenant_id?: string;
};

export enum CommandNameEnum {
  GET_CONFIG = 'get_config',
  REBOOT = 'reboot',
  SET_VALUE_TO_POINT = 'set_value_to_point',
  START_MONITORING = 'start_monitoring',
  STOP_MONITORING = 'stop_monitoring',
}

// MQTT message payload types matching Python ControllerPointDTO (camelCase)

export interface ControllerPoint {
  // Core identification fields
  id: number | null
  controllerId: string
  controllerIpAddress: string
  controllerPort: number
  bacnetObjectType: string
  pointId: number
  iotDevicePointId: string
  controllerDeviceId: string

  // Value and metadata
  units: string | null
  presentValue: string | null
  isUploaded: boolean

  // Timestamps
  createdAt: string
  updatedAt: string
  createdAtUnixMilliTimestamp: number

  // Health monitoring fields
  statusFlags: number[] | null  // Array of 4 integers [0, 1, 0, 1]
  eventState: string | null
  outOfService: boolean | null
  reliability: string | null

  // Value limit properties
  minPresValue: number | null
  maxPresValue: number | null
  highLimit: number | null
  lowLimit: number | null
  resolution: number | null

  // Control properties
  priorityArray: Array<number | null> | null  // 16-element array
  relinquishDefault: number | null

  // Notification configuration properties
  covIncrement: number | null
  timeDelay: number | null
  timeDelayNormal: number | null
  notificationClass: number | null
  notifyType: string | null
  deadband: number | null
  limitEnable: { lowLimitEnable: boolean; highLimitEnable: boolean } | null

  // Event properties
  eventEnable: { toFault: boolean; toNormal: boolean; toOffnormal: boolean } | null
  ackedTransitions: { toFault: boolean; toNormal: boolean; toOffnormal: boolean } | null
  eventTimeStamps: Array<string | null> | null  // 3-element array of ISO 8601 strings
  eventMessageTexts: string[] | null  // 3-element array
  eventMessageTextsConfig: string[] | null  // 3-element array

  // Algorithm control properties
  eventDetectionEnable: boolean | null
  eventAlgorithmInhibitRef: {
    objectIdentifier: string
    propertyIdentifier: string
    arrayIndex: number | null
  } | null
  eventAlgorithmInhibit: boolean | null
  reliabilityEvaluationInhibit: boolean | null

  errorInfo: string | null
}

export interface PointBulkPayload {
  points: ControllerPoint[]
}

function buildTopic(template: string, params: Readonly<Record<string, string>>): string {
  return template.replace(/\{(\w+)\}/g, (_m, key: string) =>
    Object.prototype.hasOwnProperty.call(params, key) && params[key] !== undefined
      ? params[key]
      : `{${key}}`
  );
}

export function getAllTopics({ params }: { params: TopicParams }): AllTopics {
  function replaceDeep<T>(node: T): T {
    if (typeof node === 'string') {
      return buildTopic(node as unknown as string, params as Record<string, string>) as unknown as T;
    }
    if (node && typeof node === 'object') {
      if (Array.isArray(node)) {
        return (node as unknown[]).map((n) => replaceDeep(n)) as unknown as T;
      }
      const next: Record<string, unknown> = {};
      for (const [k, v] of Object.entries(node as Record<string, unknown>)) {
        next[k] = replaceDeep(v);
      }
      return next as T;
    }
    return node;
  }

  const replaced = replaceDeep<typeof mqttTopics>(mqttTopics);
  const missingPointIds = !params.controller_device_id || !params.iot_device_point_id;
  return {
    ...replaced,
    data: {
      ...replaced.data,
      point: missingPointIds ? null : replaced.data.point,
    },
  } as AllTopics;
}

function buildMQTTSubscriptionPattern(topicTemplate: string): string {
  return topicTemplate.replace(/\{[^}]+\}/g, '+');
}

export const getGlobalTopicsToWriteToDB = (): string[] => {
  // MQTT shared subscription with queue for load balancing across multiple instances
  // See: https://docs.emqx.com/en/emqx/latest/messaging/mqtt-shared-subscription.html
  // Using $queue pattern to ensure only one instance processes each message

  const topics = [
    buildMQTTSubscriptionPattern(mqttTopics.data.point_bulk.topic),
    buildMQTTSubscriptionPattern(mqttTopics.command.set_value_to_point.response.topic).replace('set_value_to_point', '+'),
    buildMQTTSubscriptionPattern(mqttTopics.status.heartbeat.topic),
    buildMQTTSubscriptionPattern(mqttTopics.alert_management.acknowledge.topic),
    buildMQTTSubscriptionPattern(mqttTopics.alert_management.resolve.topic)
  ];

  // Add queue prefix for load balancing across multiple instances
  return topics.map((topic) => `$queue/${topic}`);
}
