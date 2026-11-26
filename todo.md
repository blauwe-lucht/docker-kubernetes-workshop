# Workshop todo

## README reordering

- [ ] Move Kustomize entry in `README.md` to after Secret (before Helm)

## Existing demos

- [ ] `k8s-18-persistent-volume` — check how to access the hostPath data on Windows (path is inside the Rancher Desktop VM, not directly on the host filesystem)
- [ ] Check all demos after Readiness probe for `resources`, `livenessProbe` and `readinessProbe` on every container (see [CLAUDE.md](CLAUDE.md))

## New demos

### Vertical Pod Autoscaler (`k8s-17-vertical-pod-autoscaler/`)

On hold. Position: right after Horizontal Pod Autoscaler; renumber the folders after it.

- [ ] Install VPA with the official chart (`helm repo add autoscalers https://kubernetes.github.io/autoscaler`, chart `autoscalers/vertical-pod-autoscaler`)
- [ ] `kuard.yml` with oversized requests; `vpa.yml` with `updateMode: "Off"`, then switch to `InPlaceOrRecreate` (resize without restart, Kubernetes 1.33+)
- [ ] `README.md` — HPA vs VPA, update modes, never both on the same CPU/memory metric
- [ ] Verify: updater minimum replicas for in-place, minimum Kubernetes version on Rancher Desktop (VPA 1.8.x supports 1.36–1.38)
- [ ] Author's k3s: delete the leftover VPA CRDs (not Helm-managed) before installing

### RBAC (`k8s-rbac/`)

On hold. Position: after NetworkPolicy, before Kustomize.

- [ ] `kuard.yml` — ServiceAccount, Role (namespace-scoped), RoleBinding; show a pod running as that ServiceAccount
- [ ] `README.md` — demonstrate `kubectl auth can-i` before and after the binding; explain ClusterRole vs Role, ClusterRoleBinding vs RoleBinding

### Sealed Secrets (`k8s-sealed-secrets/`)

Position: after Secret, before NetworkPolicy.

- [ ] `README.md` — install the Sealed Secrets controller via Helm; install `kubeseal` CLI
- [ ] `sealedsecret.yml` — a SealedSecret that decrypts to the same Secret as the existing Secret demo
- [ ] Show that committing a SealedSecret to git is safe; show that the plain Secret is created automatically by the controller
- [ ] Note: Vault integration to be added later as a separate demo (`k8s-vault/`)

### CRDs (`k8s-crd/`)

Position: after Kubernetes Dashboard (final topic).

- [ ] `README.md` — explain what a CRD is and why it exists; show how operators like Sealed Secrets and the Gateway API use CRDs under the hood
- [ ] A simple CRD + custom resource example to make the concept concrete before pointing at real-world examples

### Pod Security (`k8s-security-context/`)

Position: after Namespaces, before Resources.

- [ ] `kuard.yml` — Pod with `securityContext` (runAsNonRoot, dropped capabilities, read-only root filesystem)
- [ ] `README.md` — apply Pod Security Admission labels to the namespace (`restricted` level) and show a non-compliant Pod get rejected, then fix it with the `securityContext` above

### Observability — Prometheus & metrics-server (`k8s-observability/`)

Position: after Kustomize, before Horizontal Pod Autoscaler.

- [ ] `README.md` — install metrics-server (if not already assumed by the HPA demo) and Prometheus via Helm; use `kubectl top` and a basic PromQL query to show CPU/memory metrics being collected
- [ ] Note: this demo should come before Horizontal Pod Autoscaler since HPA depends on metrics-server being present

### Pod Scheduling — Affinity & Taints (`k8s-scheduling/`)

Position: after DaemonSet, before StatefulSet simple.

- [ ] `kuard.yml` — nodeAffinity example (preferred and required) plus a taint + toleration pair
- [ ] `README.md` — on the single-node cluster: show a Pod stuck in `Pending` for an unmet required affinity or a taint without toleration, then fix it
- [ ] Optional multi-node part via [kind](k8s-31-kind/) (self-study): Pods spread over nodes and avoid a tainted node

## README final order (Kubernetes section)

1. Pod
2. ReplicaSet
3. Service
4. Deployment
5. Ingress
6. Custom images (local registry)
7. Ingress challenge
8. Ingress — path-based routing
9. Gateway API
10. Namespaces
11. Pod Security *(new)*
12. Resources
13. Liveness probe
14. Readiness probe
15. Startup probe
16. Kustomize
17. Observability — Prometheus & metrics-server *(new)*
18. Horizontal Pod Autoscaler
19. Volumes
20. Persistent Volumes
21. ConfigMap
22. Secret
23. External Secrets
24. Job / CronJob
25. DaemonSet
26. Pod Scheduling — Affinity & Taints *(new)*
27. StatefulSet simple
28. StatefulSet RabbitMQ
29. NetworkPolicy *(new)*
30. RBAC *(new)*
31. Helm
32. Kubernetes Dashboard
33. CRDs *(new)*
34. kind *(self-study)*
