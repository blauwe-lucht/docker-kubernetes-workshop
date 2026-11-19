# Docker Compose resource limits

Demonstrates how to set resource limits and reservations for a container in Docker Compose.

- **Limits**: the maximum CPU and memory the container is allowed to use.
- **Reservations**: the minimum CPU and memory guaranteed to the container.

## Run

`docker compose up -d`

Point your browser at <http://localhost:8080> to see the kuard UI.

## Observe resource usage

```bash
docker stats
```

## Clean up

`docker compose down`
