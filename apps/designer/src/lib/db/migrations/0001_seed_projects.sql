-- Seed initial projects only if table is empty
INSERT INTO projects (id, name, description, flow_config, created_at, updated_at)
SELECT '00000000-0000-0000-0000-000000000001', 'Sample Project', 'Seeded project', NULL, strftime('%Y-%m-%dT%H:%M:%fZ', 'now'), strftime('%Y-%m-%dT%H:%M:%fZ', 'now')
WHERE (SELECT COUNT(*) FROM projects) = 0
UNION ALL
SELECT '00000000-0000-0000-0000-000000000002', 'Second Project', 'Another example project', NULL, strftime('%Y-%m-%dT%H:%M:%fZ', 'now'), strftime('%Y-%m-%dT%H:%M:%fZ', 'now')
WHERE (SELECT COUNT(*) FROM projects) = 0;
