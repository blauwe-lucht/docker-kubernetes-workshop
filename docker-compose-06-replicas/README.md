# Docker Compose replicas

Demonstrates how to run multiple replicas of a container behind a load balancer.

The `kuard` service runs 3 replicas without a published port. nginx sits in front
and proxies requests to the `kuard` service name — Docker's internal DNS automatically
round-robins across all replicas.

## Run

`docker compose up -d`

Point your browser at <http://localhost:8080>. The hostname shown in the kuard UI
changes between requests, showing that different replicas are serving traffic.

## Clean up

`docker compose down`
