# Docker & Kubernetes Workshop

Hands-on demos, one folder per topic (`docker-*`, `dockerfile-*`, `k8s-*`), listed in workshop order in [README.md](README.md).

- [todo.md](todo.md) — planned demos and open work
- [decisions.md](decisions.md) — decisions and their reasons

## Conventions

- Each demo has a `README.md` with Prerequisites (if any), Apply, See the effect, Clean up.
- Students use Rancher Desktop (k3s, Traefik) on Windows 11 with WSL2. The author tests on k3s on Linux. Demos must work on both.
- Default app image: `blauwelucht/kuard-amd64:1`. Client/utility pods: `busybox:1.37`.
- Challenges give hints in the README, never a solution file.
- All exercises after the Readiness probe demo give every container `resources`, a `livenessProbe` and a `readinessProbe` (kuard: `/healthy` and `/ready`, see `k8s-secret/kuard.yml`). Utility clients that only `sleep` (e.g. busybox) use `exec: ["true"]` probes.

## Current state

- `k8s-networkpolicy/` is done and tested on k3s; still to be verified on Rancher Desktop.
- RBAC (`k8s-rbac/`) is planned in [todo.md](todo.md) and on hold.
