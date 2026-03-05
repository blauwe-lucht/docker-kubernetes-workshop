# Docker Compose restart policies

Demonstrates the four restart policies available in Docker Compose.

| Policy | Behavior |
| --- | --- |
| `no` | Never restart (default, not in demo) |
| `always` | Restart on crash or Docker daemon start (e.g. after host reboot), even if manually stopped |
| `on-failure` | Restart only when the container exits with a non-zero code |
| `unless-stopped` | Restart on crash or Docker daemon start (e.g. after host reboot), but not if manually stopped |

## Run

`docker compose up -d`

## Observe

Watch the `on-failure` service restart repeatedly due to its exit code:

```bash
docker compose ps
docker compose logs on-failure
```

Watch restart counts increase:

```bash
watch docker compose ps
```

Stop the `unless-stopped` service manually — it will not restart automatically, but
will restart when the Docker daemon restarts:

```bash
docker compose stop unless-stopped
docker compose ps
```

## Clean up

`docker compose down`
