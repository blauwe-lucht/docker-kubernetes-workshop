# Docker & Kubernetes Workshop

A collection of examples to get started with Docker and Kubernetes.

## Examples

### [Simple Dockerfile](./dockerfile-simple/)

Build and run a custom Nginx container using a Dockerfile.

### [Rootless Dockerfile](./dockerfile-rootless/)

Run an Nginx container as a non-root user using the nginx-unprivileged base image.

### [Multi-stage Dockerfile](./dockerfile-multistage/)

Use a build stage to compile a C++ binary and copy it to a minimal final image.

### [Simple Docker Compose](./docker-compose-simple/)

Run a simple multi-container setup using Docker Compose.

### [Docker Compose with build](./docker-compose-build/)

Build an image from a Dockerfile and run it with Docker Compose.

### [Docker Compose restart policies](./docker-compose-restart/)

Control when Docker automatically restarts containers using restart policies.

### [Docker Compose healthcheck](./docker-compose-healthcheck/)

Add a healthcheck to a container so Docker knows when it is ready.

### [Docker Compose resource limits](./docker-compose-limits/)

Set CPU and memory limits and reservations for a container.

### [Docker Compose replicas](./docker-compose-replicas/)

Run multiple replicas of a container behind an nginx load balancer.
