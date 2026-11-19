# Multi-stage Dockerfile

Demonstrates a multi-stage build: a full build image compiles the binary, and only
the binary is copied to a minimal final image.

- **Build stage**: `almalinux:9` with `gcc-c++` installed to compile the C++ server.
- **Final stage**: `almalinux:9-minimal` — no compiler, no build tools, just the binary.

## Build naive image

`docker build -t naive -f Dockerfile.naive .`

## Run naive image

`docker run --rm -d --name naive -p 8080:8080 naive`

## Build smart multistage image

`docker build -t multistage .`

## Run multistage image

`docker run --rm -d --name multistage -p 8080:8080 multistage`

Then visit <http://localhost:8080>.

## Check size difference

`docker image ls naive`
`docker image ls multistage`

## Clean up

`docker stop naive`
`docker stop multistage`
`docker rmi naive`
`docker rmi multistage`
