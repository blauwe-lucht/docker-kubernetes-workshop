# Docker & Kubernetes Workshop

Hands-on demos, one folder per topic, listed in workshop order in [README.md](README.md). `vagrant-vmware-win11/` is the author's Windows test VM, not a demo.

- [todo.md](todo.md) — planned demos and open work
- [decisions.md](decisions.md) — decisions and their reasons

## Conventions

- Folder name: `<section>-NN-<description>`, numbered per section (`docker`, `docker-compose`, `k8s`) in `README.md` order. Inserting a demo renumbers the folders after it, including all links to them.
- Each demo has a `README.md` with Prerequisites (if any), Apply, See the effect, Clean up.
- Students use Rancher Desktop (k3s, Traefik) on Windows 11 with WSL2. The author tests on k3s on Linux. Demos must work on both.
- Default app image: `blauwelucht/kuard-amd64:1`. Client/utility pods: `busybox:1.37`.
- Challenges give hints in the README, never a solution file.
- All exercises after the Readiness probe demo give every container `resources`, a `livenessProbe` and a `readinessProbe` (kuard: `/healthy` and `/ready`, see `k8s-21-secret/kuard.yml`). Utility clients that only `sleep` (e.g. busybox) use `exec: ["true"]` probes.

## Current state

- `k8s-28-networkpolicy/` is done and tested on k3s; still to be verified on Rancher Desktop.
- RBAC (no folder yet) is planned in [todo.md](todo.md) and on hold.
