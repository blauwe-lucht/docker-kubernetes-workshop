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

---

## Healthcheck-based dependencies

`compose-depends.yml` demonstrates how a service can wait for another service to become healthy before starting, using `depends_on` with `condition: service_healthy`.

The `slow-starter` service takes 20 seconds to become healthy (it creates `/tmp/healthy` after sleeping). The `dependent` service will not start until `slow-starter` is healthy.

### Run

`docker compose -f compose-depends.yml up`

Watch `slow-starter` move through `starting` → `healthy`, after which `dependent` starts and exits.

### Clean up

When started with '-d':

`docker compose -f compose-depends.yml down`

Otherwise, just press Ctrl-C and wait for a bit.
