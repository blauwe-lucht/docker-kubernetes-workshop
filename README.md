# Docker & Kubernetes Workshop

A collection of examples to get started with Docker and Kubernetes.

## Examples

### [Simple Dockerfile](./dockerfile-simple/)

Build and run a custom Nginx container using a Dockerfile.

### [Rootless Dockerfile](./dockerfile-rootless/)

Run an Nginx container as a non-root user using the nginx-unprivileged base image.

### [Multi-stage Dockerfile](./dockerfile-multistage/)

Use a build stage to compile a C++ binary and copy it to a minimal final image.

### [Dockerfile challenge](./dockerfile-challenge/)

Build an image that serves the bingo tracker: rootless and as small as possible.

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

### [Docker Compose complete](./docker-compose-complete/)

A production-like setup combining healthchecks, restart policies, resource limits, replicas, and dependencies.

## Kubernetes examples

### [Pod](./k8s-pod/)

Run a single Pod in Kubernetes.

### [ReplicaSet](./k8s-replicaset/)

Run multiple replicas of a Pod and expose them via a NodePort Service.

### [Service](./k8s-service/)

Expose a ReplicaSet using a NodePort Service so it can be reached from outside the cluster.

### [Deployment](./k8s-deploy/)

Manage a ReplicaSet via a Deployment (the standard way to run workloads in Kubernetes), exposed via a NodePort Service.

### [Ingress](./k8s-ingress/)

Route external HTTP traffic to a Service using an Ingress, with a Deployment behind a ClusterIP Service.

### [Resources](./k8s-resources/)

Set CPU and memory requests and limits on a container.

### [Liveness probe](./k8s-liveness/)

Add a liveness probe so Kubernetes automatically restarts a container when it becomes unhealthy.

### [Readiness probe](./k8s-readiness/)

Add a readiness probe so Kubernetes only routes traffic to a Pod once it is ready to serve requests.

### [Horizontal Pod Autoscaler](./k8s-horizontal-pod-autoscaler/)

Automatically scale the number of replicas up and down based on CPU utilisation.

### [Volumes](./k8s-volumes/)

Mount a host directory and a shared in-memory volume into a Pod using hostPath and emptyDir volumes.

### [Persistent Volumes](./k8s-persistent-volume/)

Decouple storage from the Pod lifecycle using a PersistentVolume and PersistentVolumeClaim.

### [ConfigMap](./k8s-config/)

Externalise configuration from the container image using a ConfigMap, injected as environment variables or a mounted file.

### [Secret](./k8s-secret/)

Store sensitive values such as passwords separately from other configuration using a Secret, injected as environment variables or a mounted file.

### [Helm](./k8s-helm/)

Use Helm to install and manage pre-packaged Kubernetes applications (charts) with a single command.

### [Kubernetes Dashboard](./k8s-dashboard/)

Inspect and manage cluster resources through a web-based UI using the Kubernetes Dashboard, installed via Helm.
