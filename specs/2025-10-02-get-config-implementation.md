# get_config Command Implementation Specification

**Date:** 2025-10-02
**Status:** Draft
**Related:** Designer MQTT Integration (Phase 2)

## Overview

The `get_config` command enables BACnet network discovery by allowing users to configure controllers and BACnet readers in the Designer UI, send this configuration to the IoT device via MQTT, and receive discovered BACnet points back for display in the Controllers tab.

## Current State

### SupervisorsTab

- Displays deployment config (organization_id, site_id, iot_device_id)
- Shows MQTT connection status and broker health
- **Missing:** Controller and BACnet reader configuration

### Controllers Tab

- Currently displays **mock data** under "Default Supervisor"
- **Goal:** Replace mock data with real discovered points from IoT device

## User Flow

```
1. SupervisorsTab: User Configuration
   - Click "Configure Controllers" button
     → Modal opens with form to add controller IPs
     → User adds: ["192.168.1.101", "192.168.1.102"]

   - Click "Configure BACnet Readers" button
     → Modal opens with BACnet reader config form
     → User fills:
        * ip_address: "192.168.1.100"
        * subnet_mask: 24
        * bacnet_device_id: 1001
        * port: 47808
        * bbmd_enabled: false
        * is_active: true
     → User can add multiple readers

   - Click "Get Config" button
     → Sends config to IoT device via MQTT

2. MQTT Request (Designer → IoT Device)
   Topic: .../command/get_config/request
   Properties:
     - correlationData: <uuid>
     - responseTopic: .../command/get_config/response
   Payload:
     {
       "urlToUploadConfig": "https://...",
       "jwtToken": "...",
       "iotDeviceControllers": [
         { "ip_address": "192.168.1.101" },
         { "ip_address": "192.168.1.102" }
       ],
       "bacnetReaders": [
         {
           "id": "reader_1",
           "ip_address": "192.168.1.100",
           "subnet_mask": 24,
           "bacnet_device_id": 1001,
           "port": 47808,
           "bbmd_enabled": false,
           "is_active": true
         }
       ]
     }

3. IoT Device Processing
   - Extract correlationData from MQTT message
   - Persist controller IPs to database
   - Persist BACnet reader configs to database
   - Start BACnet discovery:
     * Use readers to scan network
     * Discover controllers at provided IPs
     * Read all BACnet points from controllers
     * Collect point metadata (object type, units, etc.)
   - Build discovered config JSON
   - Upload JSON to presigned URL (HTTP PUT)

4. MQTT Response (IoT Device → Designer)
   Topic: .../command/get_config/response
   Properties:
     - correlationData: <echo from request>
   Payload:
     {
       "success": true,
       "uploaded_at": "2025-10-02T10:30:00Z",
       "controllers_discovered": 2,
       "points_discovered": 47
     }

5. Designer Processing
   - Match response via correlationData
   - Fetch uploaded config from backend (GET /api/.../config)
   - Parse discovered points
   - Store in database:
     * iot_device_configs (full snapshot)
     * bacnet_readers (reader configs)
     * iot_device_controllers (discovered controllers)
     * controller_points (all discovered points)
   - Update Controllers tab with real data

6. Controllers Tab Display
   - Replace mock data with discovered points
   - Show under "Default Supervisor" section
   - Display:
     * Controller name/IP
     * Point list (object type, ID, name, units)
     * Present values (from point_bulk MQTT messages)
```

## Data Structures

### BacnetReaderConfig (User Input)

```typescript
interface BacnetReaderConfig {
  id: string; // Generated UUID
  ip_address: string; // e.g., "192.168.1.100"
  subnet_mask: number; // e.g., 24 for /24
  bacnet_device_id: number; // e.g., 1001
  port: number; // Default: 47808
  bbmd_enabled: boolean; // BACnet Broadcast Management Device
  bbmd_server_ip?: string; // Required if bbmd_enabled = true
  is_active: boolean; // Enable/disable this reader
}
```

### Controller Config (User Input)

```typescript
interface ControllerConfig {
  ip_address: string; // e.g., "192.168.1.101"
}
```

### Discovered Point (IoT Device Output)

```typescript
interface DiscoveredPoint {
  id: number; // Database ID
  controller_ip_address: string; // "192.168.1.101"
  controller_port: number; // 47808
  bacnet_object_type: string; // "analog-input"
  point_id: number; // BACnet object instance (e.g., 0)
  iot_device_point_id: string; // "ai_0"
  controller_id: string; // "bacnet_device_1001"
  controller_device_id: string; // "bacnet_device_1001"
  units?: string; // "degrees-fahrenheit"
  present_value?: string; // "72.5"
  status_flags?: string[]; // ["in-alarm"]
  out_of_service?: boolean; // false
  reliability?: string; // "no-fault-detected"
  created_at: string; // ISO timestamp
  updated_at: string; // ISO timestamp
}
```

## Database Schema

### Designer Database (SQLite)

#### Table: `bacnet_readers`

```sql
CREATE TABLE bacnet_readers (
  id TEXT PRIMARY KEY,
  project_id TEXT NOT NULL,
  ip_address TEXT NOT NULL,
  subnet_mask INTEGER NOT NULL,
  bacnet_device_id INTEGER NOT NULL,
  port INTEGER NOT NULL DEFAULT 47808,
  bbmd_enabled BOOLEAN DEFAULT FALSE,
  bbmd_server_ip TEXT,
  is_active BOOLEAN DEFAULT TRUE,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

CREATE INDEX idx_readers_project ON bacnet_readers(project_id);
CREATE INDEX idx_readers_active ON bacnet_readers(is_active);
```

#### Table: `iot_device_controllers`

```sql
CREATE TABLE iot_device_controllers (
  id TEXT PRIMARY KEY,
  project_id TEXT NOT NULL,
  ip_address TEXT NOT NULL,
  bacnet_device_id INTEGER,
  name TEXT,
  is_active BOOLEAN DEFAULT TRUE,
  metadata JSON,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

CREATE INDEX idx_controllers_project ON iot_device_controllers(project_id);
CREATE INDEX idx_controllers_active ON iot_device_controllers(is_active);
```

#### Table: `controller_points`

```sql
CREATE TABLE controller_points (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  project_id TEXT NOT NULL,
  controller_id TEXT NOT NULL,
  controller_ip_address TEXT NOT NULL,
  controller_port INTEGER NOT NULL DEFAULT 47808,
  bacnet_object_type TEXT NOT NULL,
  point_id INTEGER NOT NULL,
  iot_device_point_id TEXT NOT NULL,
  controller_device_id TEXT NOT NULL,
  units TEXT,
  present_value TEXT,
  status_flags TEXT,
  out_of_service BOOLEAN,
  reliability TEXT,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE,
  FOREIGN KEY (controller_id) REFERENCES iot_device_controllers(id) ON DELETE CASCADE
);

CREATE INDEX idx_points_project ON controller_points(project_id);
CREATE INDEX idx_points_controller ON controller_points(controller_id);
CREATE UNIQUE INDEX idx_points_unique ON controller_points(
  controller_ip_address,
  bacnet_object_type,
  point_id
);
```

#### Table: `iot_device_configs`

```sql
CREATE TABLE iot_device_configs (
  id TEXT PRIMARY KEY,
  project_id TEXT NOT NULL,
  organization_id TEXT NOT NULL,
  site_id TEXT NOT NULL,
  iot_device_id TEXT NOT NULL,
  config_data JSON NOT NULL,
  uploaded_at TIMESTAMP NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

CREATE INDEX idx_configs_project ON iot_device_configs(project_id);
CREATE INDEX idx_configs_uploaded ON iot_device_configs(uploaded_at DESC);
```

### IoT Device Database (SQLite)

**Same tables as Designer** for dual persistence:

- `bacnet_readers`
- `iot_device_controllers`
- `controller_points` (already exists)

## API Endpoints

### 1. BACnet Readers CRUD

```
GET    /api/projects/{projectId}/bacnet-readers
POST   /api/projects/{projectId}/bacnet-readers
PUT    /api/projects/{projectId}/bacnet-readers/{readerId}
DELETE /api/projects/{projectId}/bacnet-readers/{readerId}
```

**Example GET Response:**

```json
{
  "readers": [
    {
      "id": "reader_abc123",
      "ipAddress": "192.168.1.100",
      "subnetMask": 24,
      "bacnetDeviceId": 1001,
      "port": 47808,
      "bbmdEnabled": false,
      "isActive": true,
      "createdAt": "2025-10-02T10:00:00Z"
    }
  ]
}
```

### 2. Controllers CRUD

```
GET    /api/projects/{projectId}/controllers
POST   /api/projects/{projectId}/controllers
DELETE /api/projects/{projectId}/controllers/{controllerId}
```

**Example GET Response:**

```json
{
  "controllers": [
    {
      "id": "ctrl_xyz789",
      "ipAddress": "192.168.1.101",
      "bacnetDeviceId": 1001,
      "name": "AHU-1 Controller",
      "isActive": true
    }
  ]
}
```

### 3. Get Config Flow

```
POST /api/projects/{projectId}/config/upload-url
```

**Response:**

```json
{
  "uploadUrl": "https://.../config-uploads/cfg_123?token=...",
  "configId": "cfg_123",
  "jwtToken": "eyJ...",
  "expiresAt": "2025-10-02T10:35:00Z"
}
```

```
PUT /api/config-uploads/{configId}
Authorization: Bearer {jwtToken}
```

**Request Body (from IoT device):**

```json
{
  "organization_id": "org_123",
  "site_id": "site_456",
  "iot_device_id": "device_789",
  "uploaded_at": "2025-10-02T10:30:00Z",
  "bacnetReaders": [...],
  "controllers": [...],
  "points": [...]
}
```

```
GET /api/projects/{projectId}/config/latest
```

**Response:**

```json
{
  "id": "cfg_123",
  "uploadedAt": "2025-10-02T10:30:00Z",
  "config": {
    "bacnetReaders": [...],
    "controllers": [...],
    "points": [...]
  }
}
```

### 4. Controller Points

```
GET /api/projects/{projectId}/controller-points
```

**Response:**

```json
{
  "points": [
    {
      "id": 1,
      "controllerId": "ctrl_xyz789",
      "controllerIpAddress": "192.168.1.101",
      "bacnetObjectType": "analog-input",
      "pointId": 0,
      "iotDevicePointId": "ai_0",
      "units": "degrees-fahrenheit",
      "presentValue": "72.5",
      "statusFlags": ["in-alarm"],
      "outOfService": false,
      "reliability": "no-fault-detected"
    }
  ]
}
```

## UI Components

### SupervisorsTab Enhancement

**File:** `apps/designer/src/components/sidebar/supervisors-tab.tsx`

**New UI Elements:**

1. **Configure Controllers Section**

   - Button: "Configure Controllers"
   - Opens modal with controller IP form
   - Lists configured controller IPs
   - Delete functionality per controller

2. **Configure BACnet Readers Section**

   - Button: "Configure Readers"
   - Opens modal with BACnet reader form
   - Lists configured readers
   - Delete functionality per reader

3. **Get Config Button**
   - Disabled when MQTT not connected
   - Shows loading spinner during discovery
   - Triggers full discovery flow

### Controllers Tab Update

**File:** `apps/designer/src/components/sidebar/controllers-tab.tsx`

**Changes:**

- Replace mock data with real `controller_points` from database
- Fetch points via API: `GET /api/projects/{projectId}/controller-points`
- Display under "Default Supervisor" section
- Show real-time `present_value` updates from MQTT `point_bulk` messages

### Modal Components

#### ControllersModal

**File:** `apps/designer/src/components/modals/controllers-modal.tsx`

- Form to add controller IP addresses
- List of existing controllers
- Delete functionality
- Save to database via API

#### BacnetReadersModal

**File:** `apps/designer/src/components/modals/bacnet-readers-modal.tsx`

- Form with fields:
  - IP Address
  - Subnet Mask
  - BACnet Device ID
  - Port (default 47808)
  - BBMD Enabled
  - BBMD Server IP (conditional)
  - Is Active
- List of existing readers
- Delete functionality
- Save to database via API

## MQTT 5.0 Implementation

### Designer Side (Already Implemented ✅)

The Designer's `MqttBus.request()` already implements MQTT 5.0 correctly.

### IoT Device Side (Needs Changes)

**File:** `apps/bms-iot-app/src/controllers/mqtt/mqtt_controller.py`

**Update `on_get_config_request`:**

- Extract correlationData from message.properties
- Persist controllers and readers to database
- Start BACnet discovery
- Upload results to presigned URL
- Publish response with correlation data

**File:** `apps/bms-iot-app/src/network/mqtt_command_dispatcher.py`

**Update `publish_response` method:**

- Add `correlation_data` parameter
- Set MQTT 5 properties when publishing

## Store Integration

**File:** `apps/designer/src/store/slices/mqtt-slice.ts`

```typescript
export interface MQTTSlice {
  configRequest: {
    loading: boolean;
    error?: string;
  };

  getConfig: (params: {
    controllers: ControllerConfig[];
    bacnetReaders: BacnetReaderConfig[];
  }) => Promise<ConfigData>;
}
```

**Implementation:**

1. Generate presigned URL from backend
2. Send MQTT request with config data
3. Wait for response (30s timeout)
4. Fetch uploaded config from backend
5. Return config data for UI display

## Implementation Phases

### Phase 2a: Database & API

1. Database migrations (Designer + IoT app)
2. Repository layer (bacnet_readers, iot_device_controllers, controller_points)
3. API endpoints (CRUD for readers, controllers, points)
4. Presigned URL generation/validation

### Phase 2b: UI Components

1. ControllersModal component
2. BacnetReadersModal component
3. Update SupervisorsTab with config sections
4. Update ControllersTab to use real data

### Phase 2c: MQTT Integration

1. Update IoT app MQTT handler
2. Add correlation data support
3. Implement BACnet discovery flow
4. Config upload to presigned URL

### Phase 2d: Store & Flow Integration

1. Update MQTT slice with getConfig action
2. Wire up UI buttons to store actions
3. Handle loading/error states
4. Replace mock data in ControllersTab

### Phase 2e: Testing

1. Unit tests (all layers)
2. Integration tests (full flow)
3. E2E validation
4. Error handling

## Success Criteria

- [ ] User can add/edit/delete BACnet reader configs
- [ ] User can add/delete controller IP addresses
- [ ] "Get Config" button triggers full discovery flow
- [ ] IoT device discovers points using provided config
- [ ] Discovered points uploaded to Designer
- [ ] Controllers Tab displays real points (mock data replaced)
- [ ] MQTT 5.0 correlation data working correctly
- [ ] Config persisted in both Designer and IoT device databases
- [ ] All tests passing

## Breaking Changes

This is in development - breaking changes are acceptable:

- Controllers Tab mock data will be removed
- New database tables required
- New API endpoints
- SupervisorsTab UI significantly changed
