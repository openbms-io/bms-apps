# Story 1.7: Nginx Proxy Configuration

Status: ready-for-dev

## Story

As a developer,
I want the control-sequence-api routed through the nginx proxy,
so that Designer can access the API through the unified gateway.

## Acceptance Criteria

1. Add `/control-sequence` location to nginx.conf.template
2. Add CONTROL_SEQUENCE_HOST and CONTROL_SEQUENCE_PORT to .env
3. Route `/control-sequence/*` → `http://${CONTROL_SEQUENCE_HOST}:${CONTROL_SEQUENCE_PORT}`
4. Update infra README with new service documentation
5. Verify proxy routing works with curl test

## Tasks / Subtasks

- [ ] Task 1: Add environment variables to .env (AC: #2)

  - [ ] Add `CONTROL_SEQUENCE_HOST=host.docker.internal`
  - [ ] Add `CONTROL_SEQUENCE_PORT=8001`
  - [ ] Verify port matches tech spec (8001)

- [ ] Task 2: Add nginx location block (AC: #1, #3)

  - [ ] Add `/control-sequence` location to nginx.conf.template
  - [ ] Configure rewrite rule to strip `/control-sequence` prefix
  - [ ] Set proxy_pass to `http://${CONTROL_SEQUENCE_HOST}:${CONTROL_SEQUENCE_PORT}`
  - [ ] Add standard proxy headers (Host, X-Real-IP, X-Forwarded-For, X-Forwarded-Proto)
  - [ ] Follow existing building-semantics pattern

- [ ] Task 3: Update infra README (AC: #4)

  - [ ] Document new `/control-sequence` route
  - [ ] Document CONTROL_SEQUENCE_HOST and CONTROL_SEQUENCE_PORT variables
  - [ ] Add example curl command for health check

- [ ] Task 4: Verify proxy routing (AC: #5)
  - [ ] Start control-sequence-api on port 8001 (from Story 1.6)
  - [ ] Start nginx proxy with docker-compose
  - [ ] Test with curl: `curl http://localhost:3000/control-sequence/docs`
  - [ ] Verify Swagger UI loads through proxy

## Dev Notes

### Architecture Pattern

Follow the existing building-semantics proxy pattern:

```nginx
# Building Semantics API: /building-semantics → http://${BUILDING_SEMANTICS_HOST}:${BUILDING_SEMANTICS_PORT}
location /building-semantics {
  rewrite ^/building-semantics(/.*)$ $1 break;
  proxy_pass http://${BUILDING_SEMANTICS_HOST}:${BUILDING_SEMANTICS_PORT};
  proxy_http_version 1.1;
  proxy_set_header Host $host;
  proxy_set_header X-Real-IP $remote_addr;
  proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
  proxy_set_header X-Forwarded-Proto $scheme;
}
```

### Configuration

| Variable                | Value                  | Description                                |
| ----------------------- | ---------------------- | ------------------------------------------ |
| `CONTROL_SEQUENCE_HOST` | `host.docker.internal` | Control Sequence API host                  |
| `CONTROL_SEQUENCE_PORT` | `8001`                 | Control Sequence API port (from tech spec) |

### Routing

| Path                              | Target                                                       |
| --------------------------------- | ------------------------------------------------------------ |
| `/control-sequence/*`             | `http://${CONTROL_SEQUENCE_HOST}:${CONTROL_SEQUENCE_PORT}/*` |
| `/control-sequence/docs`          | Swagger UI                                                   |
| `/control-sequence/api/v1/health` | Health endpoint                                              |

### Project Structure Notes

Files to modify:

- `infra/proxy/nginx.conf.template` - Add location block
- `infra/.env` - Add environment variables
- `infra/README.md` - Update documentation (if exists)

### References

- [Tech Spec Section 3.3 - Configuration](./specs/control-sequence-api-tech-spec.md#33-configuration)
- [Existing nginx.conf.template](../../infra/proxy/nginx.conf.template)
- [Existing .env](../../infra/.env)

### Learnings from Previous Story

**From Story 1.6 (Status: drafted)**

Previous story not yet implemented. This story depends on Story 1.6 (Project Setup) being complete before verification testing can occur.

- Control Sequence API will run on port 8001
- API base path is `/api/v1/`
- Health endpoint at `/api/v1/health`
- Swagger UI at `/docs`

[Source: stories/story-1.6-project-setup-scaffolding.md]

## Dev Agent Record

### Context Reference

- [story-1.7-nginx-proxy-configuration.context.xml](./story-1.7-nginx-proxy-configuration.context.xml)

### Agent Model Used

Claude Opus 4

### Debug Log References

### Completion Notes List

### File List
