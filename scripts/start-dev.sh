#!/usr/bin/env bash
set -euo pipefail

# Configuration
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
INFRA_DIR="$ROOT_DIR/infra"
BMS_LOG_LEVEL="${BMS_LOG_LEVEL:-WARNING}"  # Default: WARNING (quiet)
KEEP_INFRA="${KEEP_INFRA:-false}"          # Default: stop infra on exit

# --- Utility Functions (Single Responsibility) ---

need_cmd() {
  command -v "$1" >/dev/null 2>&1 || {
    echo "Missing required command: $1"
    exit 1
  }
}

compose() {
  if command -v docker >/dev/null 2>&1 && docker compose version >/dev/null 2>&1; then
    docker compose "$@"
  elif command -v docker-compose >/dev/null 2>&1; then
    docker-compose "$@"
  else
    echo "docker compose not found. Install Docker Desktop or docker-compose."
    exit 1
  fi
}

wait_port() {
  local host="$1"
  local port="$2"
  local name="$3"
  local tries=60
  for i in $(seq 1 "$tries"); do
    if nc -z "$host" "$port" >/dev/null 2>&1; then
      echo "✔ $name is ready on $host:$port"
      return 0
    fi
    sleep 0.5
  done
  echo "✖ Timeout waiting for $name on $host:$port"
  return 1
}

# --- Prerequisite Checks ---

check_prerequisites() {
  echo "▶ Checking prerequisites..."
  need_cmd docker
  need_cmd nc
  need_cmd pnpm

  echo "▶ Ensuring Docker daemon is available..."
  if ! docker info >/dev/null 2>&1; then
    echo "Docker is not running. Please start Docker Desktop and retry."
    exit 1
  fi
}

# --- Infrastructure Management ---

start_infrastructure() {
  echo "▶ Bringing up infra (NanoMQ + proxy) if needed..."
  pushd "$INFRA_DIR" >/dev/null
  compose up -d
  popd >/dev/null

  echo "▶ Waiting for broker (TCP 1883) and proxy (HTTP 3000)..."
  wait_port localhost 1883 "MQTT broker (NanoMQ)" || true
  wait_port localhost 3000 "Reverse proxy (Nginx)" || true
}

stop_infrastructure() {
  echo "▶ Stopping infrastructure (NanoMQ + proxy)..."
  pushd "$INFRA_DIR" >/dev/null
  compose down
  popd >/dev/null
}

# --- Service Startup Functions ---

start_bms_iot_app() {
  local log_level="$1"

  if [ "$log_level" = "DEBUG" ] || [ "$log_level" = "ALL" ]; then
    # Show all logs (DEBUG and above)
    PYTHONPATH=.:apps/bms-iot-app python -m src.cli run-main 2>&1 | sed 's/^/[BMS-IoT] /' &
  else
    # Show only WARNING, ERROR, CRITICAL (with line buffering)
    PYTHONPATH=.:apps/bms-iot-app python -m src.cli run-main 2>&1 |
      grep --line-buffered -E "(WARNING|ERROR|CRITICAL)" | sed 's/^/[BMS-IoT] /' &
  fi
}

start_designer_app() {
  PORT=3003 pnpm --filter designer dev 2>&1 | sed 's/^/[Designer] /' &
}

# --- Shutdown Management ---

setup_shutdown_trap() {
  local pid_python="$1"
  local pid_designer="$2"

  trap "
    echo ''
    echo '▶ Shutting down services...'
    kill $pid_python $pid_designer 2>/dev/null || true
    if [ \"$KEEP_INFRA\" != \"true\" ]; then
      stop_infrastructure
    else
      echo '▶ Keeping infrastructure running (KEEP_INFRA=true)'
    fi
    exit
  " INT TERM
}

# --- Main Execution ---

main() {
  check_prerequisites
  start_infrastructure

  echo "▶ Starting services in parallel..."
  echo "   Log Level: $BMS_LOG_LEVEL (override with: BMS_LOG_LEVEL=DEBUG)"
  echo "   Keep Infra: $KEEP_INFRA (override with: KEEP_INFRA=true)"
  echo "   Access the app at http://localhost:3000 (proxied)"
  echo "   Browser MQTT connects to ws://localhost:3000/mqtt"
  echo "   Press Ctrl+C to stop all services"
  echo ""

  cd "$ROOT_DIR"

  # Start both services and capture PIDs
  start_bms_iot_app "$BMS_LOG_LEVEL"
  PID_PYTHON=$!

  start_designer_app
  PID_DESIGNER=$!

  # Setup clean shutdown
  setup_shutdown_trap "$PID_PYTHON" "$PID_DESIGNER"

  echo "▶ Services started:"
  echo "   - BMS IoT App (PID: $PID_PYTHON, Log Level: $BMS_LOG_LEVEL)"
  echo "   - Designer (PID: $PID_DESIGNER, Port: 3003)"
  echo ""

  # Wait for both processes
  wait
}

# Run main function
main
