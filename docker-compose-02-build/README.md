# Docker Compose with build

Run a container built from the `docker-01-simple` Dockerfile using Docker Compose.

## Run

`docker compose up -d`

## Update container

Make a change to [../docker-01-simple/index.html](../docker-01-simple/index.html), then

`docker compose up -d --build`

## Clean up

`docker compose down`
