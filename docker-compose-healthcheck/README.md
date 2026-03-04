# Docker Compose healthcheck

Demonstrates how to configure a healthcheck for a container in Docker Compose.
The `kuard` service is considered healthy when its `/healthy` endpoint responds successfully.

The `/healthy` endpoint can be toggled on and off via the kuard web UI at <http://localhost:8080>, making it easy to observe how Docker reacts to a failing healthcheck.

## Run

`docker compose up -d`

## Check health status

Watch the `STATUS` column change from `starting` to `healthy`.

**Linux/Mac:**

```bash
watch 'docker compose ps --format "table {{.Name}}\t{{.Status}}"'
```

**Windows (PowerShell):**

```powershell
while ($true) { docker compose ps --format "table {{.Name}}\t{{.Status}}"; Start-Sleep 2; Clear-Host }
```

## Clean up

`docker compose down`
