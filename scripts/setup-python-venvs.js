#!/usr/bin/env node
import { execSync } from "child_process";
import fs from "fs";
import path from "path";
import { fileURLToPath } from "url";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const apps = [
  { name: "bms-iot-app", path: "apps/bms-iot-app", extras: "[test]" },
  {
    name: "building-semantics-api-app",
    path: "apps/building-semantics-api-app",
    extras: "[test,dev]",
  },
];

function run(cmd, cwd) {
  console.log(`▶ ${cmd}`);
  execSync(cmd, { stdio: "inherit", cwd });
}

apps.forEach((app) => {
  const venvPath = path.join(app.path, ".venv");

  if (!fs.existsSync(venvPath)) {
    console.log(`\n▶ Creating venv for ${app.name}...`);
    run("python -m venv .venv", app.path);
  } else {
    console.log(`\n▶ Venv exists for ${app.name}, updating...`);
  }

  console.log(`▶ Installing ${app.name}...`);
  run(`.venv/bin/pip install -e '.${app.extras}'`, app.path);
});

// Install shared mqtt_topics package in both venvs
console.log("\n▶ Installing mqtt_topics in both venvs...");
apps.forEach((app) => {
  run(`.venv/bin/pip install -e ../../packages/mqtt_topics`, app.path);
});

console.log("\n✔ Python virtual environments setup complete");
