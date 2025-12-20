Infra for Phase 7.1 — Local MQTT + Proxy

Overview

- Broker: NanoMQ (TCP 1883, WebSocket 8083)
- Proxy: Nginx on 3000
  - / → Next.js (dev) at host 3003
  - /mqtt (WebSocket) → NanoMQ 8083
  - /building-semantics → Building Semantics API at host 8000
  - /control-sequence → Control Sequence API at host 8001

Why Nginx reverse proxy?

- Same-origin simplicity: the Designer UI and MQTT share the same origin (`http://localhost:3000`), so no CORS, CSP, or mixed‑content headaches.
- WebSocket upgrade: cleanly upgrades `/mqtt` to a WS connection and forwards to the broker (`ws://nanomq:8083/mqtt`).
- Stable endpoint: the app always targets `/mqtt` regardless of where the broker runs or which ports it uses.
- Dev UX: you keep running Next.js locally on 3001, while the proxy presents a single entrypoint at 3000.
- Future TLS: one place to terminate HTTPS and expose `wss://…/mqtt` without touching app code or the broker.

Files

- docker-compose.yml — defines broker + proxy services
- .env — default ports (edit as needed)
- broker/nanomq.conf — NanoMQ config enabling TCP + WS
- proxy/nginx.conf — reverse proxy routes

Quick start

1. From repo root
   cd infra
   docker compose up -d

2. Verify

   - TCP: mqttx or mosquitto_sub → localhost:1883
   - WS: open ws://localhost:3000/mqtt in a client (e.g., MQTT.js)

3. Dev app
   - Run Next.js on host port 3001
   - Access app at http://localhost:3000 (proxied)
   - Browser MQTT: connect to wss://localhost:3000/mqtt (or ws:// for http)

Port summary

- Broker TCP: 1883 (mapped from container)
- Broker WS: 8083 (mapped from container, proxied at /mqtt)
- Proxy: 3000 (public entry for browser and app)
- Building Semantics API: 8000 (proxied at /building-semantics)
- Control Sequence API: 8001 (proxied at /control-sequence)

Environment variables (.env)

| Variable                | Default              | Description                 |
| ----------------------- | -------------------- | --------------------------- |
| MQTT_TCP_PORT           | 1883                 | MQTT broker TCP port        |
| MQTT_WS_PORT            | 8083                 | MQTT broker WebSocket port  |
| PROXY_PORT              | 3000                 | Nginx proxy port            |
| NEXT_HOST               | host.docker.internal | Next.js host                |
| NEXT_PORT               | 3003                 | Next.js port                |
| BUILDING_SEMANTICS_HOST | host.docker.internal | Building Semantics API host |
| BUILDING_SEMANTICS_PORT | 8000                 | Building Semantics API port |
| CONTROL_SEQUENCE_HOST   | host.docker.internal | Control Sequence API host   |
| CONTROL_SEQUENCE_PORT   | 8001                 | Control Sequence API port   |

Testing proxy routes

```bash
# Health check for Control Sequence API
curl http://localhost:3000/control-sequence/health

# Swagger UI for Control Sequence API
open http://localhost:3000/control-sequence/docs
```

Notes

- host.docker.internal: On macOS/Windows Docker Desktop it resolves automatically. For Linux, this compose sets an extra_hosts mapping to host-gateway so the proxy can reach your host at port 3001. If your engine doesn’t support host-gateway, edit proxy/nginx.conf and replace host.docker.internal with your host IP, then restart the proxy.
- Anonymous access is enabled for local dev. Secure before deploying.
