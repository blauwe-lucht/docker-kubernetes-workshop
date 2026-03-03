# Docker Compose with build

Run a container built from the `dockerfile-simple` Dockerfile using Docker Compose.

## Run

`docker compose up -d`

## Update container

Make a change to [../dockerfile-simple/index.html](../dockerfile-simple/index.html), then

`docker compose up -d --build`

## Clean up

`docker compose down`
