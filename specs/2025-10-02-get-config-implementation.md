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
   Topic: iot/global/{organization_id}/{site_id}/{iot_device_id}/command/get_config/request
   Properties:
     - correlationData: <uuid>
     - responseTopic: iot/global/{organization_id}/{site_id}/{iot_device_id}/command/get_config/response

   Payload Schema:
   {
     urlToUploadConfig: string,    // Presigned URL for config upload
     jwtToken: string,             // JWT token for authentication

     iotDeviceControllers: Array<{
       id: string,                 // UUID from Designer DB
       ip_address: string,         // Controller IP (e.g., "192.168.1.101")
       port: number,               // BACnet port (default: 47808)
       device_id: number,          // BACnet device ID
       network_number?: number,    // Optional network number
       mac_address?: string        // Optional MAC address
     }>,

     bacnetReaders: Array<{
       id: string,                 // UUID from Designer DB
       ip_address: string,         // Reader IP (e.g., "192.168.1.100")
       port: number,               // BACnet port (default: 47808)
       device_id: number,          // BACnet device ID
       network_number?: number,    // Optional network number
       mac_address?: string,       // Optional MAC address
       is_active: boolean          // Enable/disable flag
     }>
   }

   Example Payload:
   {
     "urlToUploadConfig": "https://api.example.com/config-uploads/cfg_123",
     "jwtToken": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
     "iotDeviceControllers": [
       {
         "id": "ctrl_uuid_1",
         "ip_address": "192.168.1.101",
         "port": 47808,
         "device_id": 1001,
         "network_number": null,
         "mac_address": null
       },
       {
         "id": "ctrl_uuid_2",
         "ip_address": "192.168.1.102",
         "port": 47808,
         "device_id": 1002
       }
     ],
     "bacnetReaders": [
       {
         "id": "reader_uuid_1",
         "ip_address": "192.168.1.100",
         "port": 47808,
         "device_id": 1000,
         "network_number": null,
         "mac_address": null,
         "is_active": true
       }
     ]
   }

   Field Mapping Notes:
   - Designer DB uses 'device_id', IoT App expects 'device_id' ✅
   - Designer DB uses 'is_active', IoT App uses 'is_active' ✅
   - All snake_case fields match between Designer DB and IoT App expectations
   - Network and MAC address fields are optional (null allowed)

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
  id: string; // UUID (TEXT in DB)
  controller_ip_address: string; // "192.168.1.101"
  controller_port: number; // 47808
  bacnet_object_type: string; // "analog-input"
  point_id: number; // BACnet object instance (e.g., 0)
  controller_id: string; // FK to iot_device_controllers
  controller_device_id: string; // "bacnet_device_1001"
  units?: string; // "degrees-fahrenheit"
  present_value?: string; // "72.5"
  metadata?: {
    // All health and optional BACnet properties stored as JSON
    status_flags?: string[];
    event_state?: string;
    out_of_service?: boolean;
    reliability?: string;
    min_pres_value?: number;
    max_pres_value?: number;
    high_limit?: number;
    low_limit?: number;
    // ... other optional BACnet properties
  };
  is_deleted: boolean;
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
  iot_device_id TEXT,              -- For future Supabase sync
  organization_id TEXT,             -- For future Supabase sync
  site_id TEXT,                     -- For future Supabase sync
  ip_address TEXT NOT NULL,
  subnet_mask INTEGER NOT NULL DEFAULT 24,
  bacnet_device_id INTEGER NOT NULL,
  port INTEGER NOT NULL DEFAULT 47808,
  bbmd_enabled BOOLEAN DEFAULT FALSE,
  bbmd_server_ip TEXT,
  is_active BOOLEAN DEFAULT TRUE,
  connection_status TEXT,           -- Supabase: connection_status_enum
  is_deleted BOOLEAN DEFAULT FALSE, -- Supabase soft delete pattern
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

CREATE INDEX idx_readers_project ON bacnet_readers(project_id);
CREATE INDEX idx_readers_active ON bacnet_readers(is_active);
CREATE INDEX idx_readers_deleted ON bacnet_readers(is_deleted);
```

#### Table: `iot_device_controllers`

```sql
CREATE TABLE iot_device_controllers (
  id TEXT PRIMARY KEY,                  -- UUID (Supabase compatible)
  project_id TEXT NOT NULL,
  iot_device_id TEXT,                   -- For future Supabase sync
  organization_id TEXT,                 -- For future Supabase sync
  site_id TEXT,                         -- For future Supabase sync
  ip_address TEXT NOT NULL,
  bacnet_device_id INTEGER,
  controller_name TEXT,                 -- Supabase field name
  controller_device_id TEXT,            -- Supabase field
  metadata JSON,
  is_active BOOLEAN DEFAULT TRUE,       -- Keep for compatibility
  deleted_at TIMESTAMP,                 -- Supabase soft delete pattern
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE
);

CREATE INDEX idx_controllers_project ON iot_device_controllers(project_id);
CREATE INDEX idx_controllers_active ON iot_device_controllers(is_active);
CREATE INDEX idx_controllers_deleted ON iot_device_controllers(deleted_at);
```

#### Table: `controller_points`

```sql
CREATE TABLE controller_points (
  id TEXT PRIMARY KEY,                  -- UUID (Supabase: iot_device_point_id)
  project_id TEXT NOT NULL,
  iot_device_id TEXT,                   -- For future Supabase sync
  organization_id TEXT,                 -- For future Supabase sync
  site_id TEXT,                         -- For future Supabase sync
  controller_id TEXT NOT NULL,
  controller_ip_address TEXT NOT NULL,
  controller_port INTEGER NOT NULL DEFAULT 47808,
  bacnet_object_type TEXT NOT NULL,
  point_id INTEGER NOT NULL,
  controller_device_id TEXT NOT NULL,
  units TEXT,
  present_value TEXT,
  metadata JSON,                        -- All health/optional properties as JSON
  is_deleted BOOLEAN DEFAULT FALSE,     -- Supabase soft delete pattern
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (project_id) REFERENCES projects(id) ON DELETE CASCADE,
  FOREIGN KEY (controller_id) REFERENCES iot_device_controllers(id) ON DELETE CASCADE
);

CREATE INDEX idx_points_project ON controller_points(project_id);
CREATE INDEX idx_points_controller ON controller_points(controller_id);
CREATE INDEX idx_points_deleted ON controller_points(is_deleted);
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

#### Table: `projects`

```sql
CREATE TABLE projects (
  id TEXT PRIMARY KEY,
  name TEXT NOT NULL,
  organization_id TEXT,  -- For future Supabase sync/migration
  site_id TEXT,         -- For future Supabase sync/migration
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### IoT Device Database (SQLite)

**Same tables as Designer** for dual persistence:

- `bacnet_readers` (same structure with org/site/device fields)
- `iot_device_controllers` (same structure with Supabase fields)
- `controller_points` (already exists, update with metadata JSON)

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

### Phase 2a: MQTT 5.0 Request/Response (bms-iot-app) [Done]

1. Extract correlationData from MQTT message properties in `mqtt_controller.py:on_get_config_request`
2. Update `mqtt_command_dispatcher.py:publish_response` to include correlation_data parameter
3. Set MQTT 5 properties when publishing responses
4. Unit tests for correlation handling

### Phase 2b: Database & API (Designer)

**Database Schema - Hierarchical Structure:**

Create proper hierarchy: Organization → Site → Project → IoT Device → BACnet Resources

1. **New Tables using Drizzle ORM:** [Done]

   - `organizations` table with auto-generated `org_<uuid>` ID
   - `sites` table with UUID ID and FK to organizations
   - Update `projects` table with FK to sites (remove flat org/site fields)
   - `bacnet_readers` table scoped to org/site/iot_device
   - `iot_device_controllers` table scoped to org/site/iot_device
   - `controller_points` table with FK to controllers, scoped to org/site/iot_device
   - `iot_device_configs` table scoped to org/site/iot_device

2. **Idempotent Hierarchy Generation:**

   - Create `hierarchy-init.ts` utility for transaction-based org/site generation
   - Auto-generate on root page load if not exists
   - Format: `org_<uuid>` for organization, `uuid()` for site
   - Ensure single generation (idempotent within transaction)

3. **Migration Workflow:**
   - Define schemas in `apps/designer/src/lib/db/schema/`
   - Generate migration: `pnpm db:generate`
   - Apply migration: `pnpm db:migrate`
   - Clean DB approach (no data migration needed)

**Repository Layer:**

- `bacnet-readers-repository.ts` - CRUD scoped to org/site/iot_device
- `controllers-repository.ts` - CRUD scoped to org/site/iot_device
- `controller-points-repository.ts` - CRUD scoped to controller
- `iot-device-configs-repository.ts` - CRUD scoped to org/site/iot_device

**API Endpoints - Hierarchical Paths:**

All endpoints follow DB hierarchy pattern:
`/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/{resource}`

**Design Decision: Why Hierarchical URLs?**

While this seems verbose for a local SQLite app, we chose the full hierarchical path structure for future cloud deployment:

1. **Multi-Tenant Security**: Explicit org/site scoping prevents accidental data leakage across organizations
2. **RBAC-Friendly**: Site/org-level permissions can be enforced in middleware before DB queries
3. **Clerk.com Integration**: Matches their organization-scoping pattern where `auth.orgId` validates against URL `[orgId]`
4. **Explicit > Implicit**: Better to be verbose and safe than rely on inferred context from joins
5. **Database Alignment**: API structure mirrors the hierarchical data model exactly

Alternative considered: Project-scoped APIs (`/api/projects/[projectId]/bacnet-readers`) would be simpler but require complex join-based validation for every request in multi-tenant scenarios, increasing security risk.

**BACnet Readers:**

- GET/POST `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/bacnet-readers`
- GET/PUT/DELETE `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/bacnet-readers/[readerId]`

**Controllers:**

- GET/POST `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/controllers`
- GET/PUT/DELETE `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/controllers/[controllerId]`

**Controller Points:**

- GET/POST `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/controllers/[controllerId]/points`
- GET/PUT/DELETE `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/controllers/[controllerId]/points/[pointId]`

**Device Configs:**

- GET/POST `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/configs`
- GET/PUT `/api/organizations/[orgId]/sites/[siteId]/projects/[projectId]/iot-devices/[iotDeviceId]/configs/[configId]`

**Page Structure:**

```
app/
├── page.tsx                           # Root - calls ensureHierarchyExists()
├── organizations/
│   └── [orgId]/
│       └── sites/
│           └── [siteId]/
│               └── projects/
│                   └── [projectId]/
│                       ├── page.tsx   # Project (existing)
│                       └── iot-devices/
│                           └── [iotDeviceId]/
│                               ├── bacnet-readers/page.tsx
│                               ├── controllers/
│                               │   ├── page.tsx
│                               │   └── [controllerId]/points/page.tsx
│                               └── configs/page.tsx
```

### Phase 2c: UI Components (Designer)

1. ControllersModal (IP address form)
2. BacnetReadersModal (reader config form with all Supabase fields)
3. Update SupervisorsTab (config sections + Get Config button)
4. Save the Controllers, BacnetReaders info in the database by integrating with CRUD endpoint.

### Phase 2d: Store & Business Logic (Designer)

1. Update mqtt-slice with getConfig action
2. Implement flow: Generate presigned URL → Send MQTT request → Match response via correlationData → Fetch config → Persist to DB
3. Error handling and loading states
4. Handle metadata JSON when storing/retrieving points
5. Update ControllersTab (replace mock data with real API data, display metadata properties)

### Phase 2e: Integration & Testing (Both apps)

1. End-to-end flow validation
2. MQTT correlation verification
3. Error scenarios testing (timeout, upload failure, discovery errors)
4. Verify metadata JSON storage/retrieval
5. Verify Supabase-compatible field handling

## Success Criteria

- [ ] User can add/edit/delete BACnet reader configs
- [ ] User can add/delete controller IP addresses
- [ ] "Get Config" button triggers full discovery flow
- [ ] IoT device discovers points using provided config
- [ ] Discovered points uploaded to Designer
- [ ] Controllers Tab displays real points (mock data replaced)
- [ ] MQTT 5.0 correlation data working correctly
- [ ] Config persisted in both Designer and IoT device databases
- [ ] Metadata JSON properly stores all health/optional BACnet properties
- [ ] Database structure aligns with Supabase (nullable org/site/device fields present)
- [ ] All tests passing

## Breaking Changes

This is in development - breaking changes are acceptable:

- Controllers Tab mock data will be removed
- Database schema changes:
  - `controller_points.id`: INTEGER → TEXT UUID
  - Individual health columns → metadata JSON
  - Added nullable org/site/device hierarchy fields
  - Added Supabase compatibility fields (connection_status, is_deleted, deleted_at, etc.)
- New API endpoints
- SupervisorsTab UI significantly changed

## Migration Path to Supabase

The nullable fields (organization_id, site_id, iot_device_id) in Designer database enable future migration:

1. **Current state**: project_id-based flow, org/site/device fields are NULL
2. **Migration**: Populate org/site/device fields, update FKs to use them instead of project_id
3. **Future state**: Full org → site → project → device hierarchy, sync with Supabase

Database structure already matches Supabase schema for seamless future integration.
