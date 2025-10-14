DROP TABLE `deployment_config`;--> statement-breakpoint
PRAGMA foreign_keys=OFF;--> statement-breakpoint
CREATE TABLE `__new_bacnet_readers` (
	`id` text PRIMARY KEY NOT NULL,
	`organization_id` text NOT NULL,
	`site_id` text NOT NULL,
	`iot_device_id` text NOT NULL,
	`ip_address` text NOT NULL,
	`port` integer DEFAULT 47808 NOT NULL,
	`device_id` integer NOT NULL,
	`subnet_mask` integer DEFAULT 24 NOT NULL,
	`bbmd_enabled` integer DEFAULT false NOT NULL,
	`bbmd_server_ip` text,
	`name` text NOT NULL,
	`description` text,
	`is_active` integer DEFAULT true NOT NULL,
	`metadata` text,
	`is_deleted` integer DEFAULT false NOT NULL,
	`created_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	`updated_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	FOREIGN KEY (`organization_id`) REFERENCES `organizations`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`site_id`) REFERENCES `sites`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`iot_device_id`) REFERENCES `iot_devices`(`id`) ON UPDATE no action ON DELETE cascade
);
--> statement-breakpoint
INSERT INTO `__new_bacnet_readers`("id", "organization_id", "site_id", "iot_device_id", "ip_address", "port", "device_id", "subnet_mask", "bbmd_enabled", "bbmd_server_ip", "name", "description", "is_active", "metadata", "is_deleted", "created_at", "updated_at") SELECT "id", "organization_id", "site_id", "iot_device_id", "ip_address", "port", "device_id", "subnet_mask", "bbmd_enabled", "bbmd_server_ip", "name", "description", "is_active", "metadata", "is_deleted", "created_at", "updated_at" FROM `bacnet_readers`;--> statement-breakpoint
DROP TABLE `bacnet_readers`;--> statement-breakpoint
ALTER TABLE `__new_bacnet_readers` RENAME TO `bacnet_readers`;--> statement-breakpoint
PRAGMA foreign_keys=ON;--> statement-breakpoint
CREATE INDEX `idx_bacnet_readers_org_site_device` ON `bacnet_readers` (`organization_id`,`site_id`,`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_bacnet_readers_device` ON `bacnet_readers` (`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_bacnet_readers_deleted` ON `bacnet_readers` (`is_deleted`);--> statement-breakpoint
CREATE TABLE `__new_iot_device_controllers` (
	`id` text PRIMARY KEY NOT NULL,
	`organization_id` text NOT NULL,
	`site_id` text NOT NULL,
	`iot_device_id` text NOT NULL,
	`ip_address` text NOT NULL,
	`port` integer DEFAULT 47808 NOT NULL,
	`device_id` integer NOT NULL,
	`name` text NOT NULL,
	`description` text,
	`is_active` integer DEFAULT true NOT NULL,
	`metadata` text,
	`is_deleted` integer DEFAULT false NOT NULL,
	`created_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	`updated_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	FOREIGN KEY (`organization_id`) REFERENCES `organizations`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`site_id`) REFERENCES `sites`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`iot_device_id`) REFERENCES `iot_devices`(`id`) ON UPDATE no action ON DELETE cascade
);
--> statement-breakpoint
INSERT INTO `__new_iot_device_controllers`("id", "organization_id", "site_id", "iot_device_id", "ip_address", "port", "device_id", "name", "description", "is_active", "metadata", "is_deleted", "created_at", "updated_at") SELECT "id", "organization_id", "site_id", "iot_device_id", "ip_address", "port", "device_id", "name", "description", "is_active", "metadata", "is_deleted", "created_at", "updated_at" FROM `iot_device_controllers`;--> statement-breakpoint
DROP TABLE `iot_device_controllers`;--> statement-breakpoint
ALTER TABLE `__new_iot_device_controllers` RENAME TO `iot_device_controllers`;--> statement-breakpoint
CREATE INDEX `idx_controllers_org_site_device` ON `iot_device_controllers` (`organization_id`,`site_id`,`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_controllers_deleted` ON `iot_device_controllers` (`is_deleted`);--> statement-breakpoint
CREATE TABLE `__new_controller_points` (
	`id` text PRIMARY KEY NOT NULL,
	`organization_id` text NOT NULL,
	`site_id` text NOT NULL,
	`iot_device_id` text NOT NULL,
	`controller_id` text NOT NULL,
	`point_name` text,
	`point_type` text NOT NULL,
	`object_identifier` text,
	`instance_number` integer NOT NULL,
	`writable` integer DEFAULT false NOT NULL,
	`units` text,
	`description` text,
	`metadata` text,
	`is_deleted` integer DEFAULT false NOT NULL,
	`created_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	`updated_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	FOREIGN KEY (`organization_id`) REFERENCES `organizations`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`site_id`) REFERENCES `sites`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`iot_device_id`) REFERENCES `iot_devices`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`controller_id`) REFERENCES `iot_device_controllers`(`id`) ON UPDATE no action ON DELETE cascade
);
--> statement-breakpoint
INSERT INTO `__new_controller_points`("id", "organization_id", "site_id", "iot_device_id", "controller_id", "point_name", "point_type", "object_identifier", "instance_number", "writable", "units", "description", "metadata", "is_deleted", "created_at", "updated_at") SELECT "id", "organization_id", "site_id", "iot_device_id", "controller_id", "point_name", "point_type", "object_identifier", "instance_number", "writable", "units", "description", "metadata", "is_deleted", "created_at", "updated_at" FROM `controller_points`;--> statement-breakpoint
DROP TABLE `controller_points`;--> statement-breakpoint
ALTER TABLE `__new_controller_points` RENAME TO `controller_points`;--> statement-breakpoint
CREATE INDEX `idx_points_controller` ON `controller_points` (`controller_id`);--> statement-breakpoint
CREATE INDEX `idx_points_org_site_device` ON `controller_points` (`organization_id`,`site_id`,`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_points_deleted` ON `controller_points` (`is_deleted`);--> statement-breakpoint
CREATE TABLE `__new_iot_device_configs` (
	`id` text PRIMARY KEY NOT NULL,
	`project_id` text NOT NULL,
	`organization_id` text NOT NULL,
	`site_id` text NOT NULL,
	`iot_device_id` text NOT NULL,
	`config_data` text NOT NULL,
	`version` integer DEFAULT 1 NOT NULL,
	`is_active` integer DEFAULT true NOT NULL,
	`created_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	`updated_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	FOREIGN KEY (`project_id`) REFERENCES `projects`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`organization_id`) REFERENCES `organizations`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`site_id`) REFERENCES `sites`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`iot_device_id`) REFERENCES `iot_devices`(`id`) ON UPDATE no action ON DELETE cascade
);
--> statement-breakpoint
INSERT INTO `__new_iot_device_configs`("id", "project_id", "organization_id", "site_id", "iot_device_id", "config_data", "version", "is_active", "created_at", "updated_at") SELECT "id", "project_id", "organization_id", "site_id", "iot_device_id", "config_data", "version", "is_active", "created_at", "updated_at" FROM `iot_device_configs`;--> statement-breakpoint
DROP TABLE `iot_device_configs`;--> statement-breakpoint
ALTER TABLE `__new_iot_device_configs` RENAME TO `iot_device_configs`;--> statement-breakpoint
CREATE INDEX `idx_configs_device` ON `iot_device_configs` (`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_configs_org_site_device` ON `iot_device_configs` (`organization_id`,`site_id`,`iot_device_id`);--> statement-breakpoint
CREATE TABLE `__new_projects` (
	`id` text PRIMARY KEY NOT NULL,
	`site_id` text NOT NULL,
	`iot_device_id` text,
	`name` text NOT NULL,
	`description` text,
	`workflow_config` text,
	`created_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	`updated_at` text DEFAULT (strftime('%Y-%m-%dT%H:%M:%fZ', 'now')) NOT NULL,
	FOREIGN KEY (`site_id`) REFERENCES `sites`(`id`) ON UPDATE no action ON DELETE cascade,
	FOREIGN KEY (`iot_device_id`) REFERENCES `iot_devices`(`id`) ON UPDATE no action ON DELETE set null
);
--> statement-breakpoint
INSERT INTO `__new_projects`("id", "site_id", "iot_device_id", "name", "description", "workflow_config", "created_at", "updated_at") SELECT "id", "site_id", "iot_device_id", "name", "description", "workflow_config", "created_at", "updated_at" FROM `projects`;--> statement-breakpoint
DROP TABLE `projects`;--> statement-breakpoint
ALTER TABLE `__new_projects` RENAME TO `projects`;--> statement-breakpoint
CREATE INDEX `idx_projects_site_id` ON `projects` (`site_id`);--> statement-breakpoint
CREATE INDEX `idx_projects_iot_device_id` ON `projects` (`iot_device_id`);--> statement-breakpoint
CREATE INDEX `idx_projects_created_at` ON `projects` (`created_at`);--> statement-breakpoint
CREATE INDEX `idx_projects_updated_at` ON `projects` (`updated_at`);
