# Workshop todo

## README reordering

- [ ] Move Kustomize entry in `README.md` to after Secret (before Helm)

## Existing demos

- [ ] `k8s-persistent-volume` — check how to access the hostPath data on Windows (path is inside the Rancher Desktop VM, not directly on the host filesystem)

## New demos

### NetworkPolicy (`k8s-networkpolicy/`)

Position: after Sealed Secrets, before RBAC.

- [ ] `kuard.yml` — two Deployments + Services in separate namespaces; a NetworkPolicy that allows traffic from one and blocks the other
- [ ] `README.md` — demonstrate that without a NetworkPolicy all pods can reach each other; apply the policy and show the block

### RBAC (`k8s-rbac/`)

Position: after NetworkPolicy, before Kustomize.

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

- [ ] `kuard.yml` — nodeAffinity example (preferred and required) plus a taint + toleration pair, using the kind multi-node cluster so placement is actually observable
- [ ] `README.md` — show a Pod landing on the wrong/right node with affinity rules; taint a node and show a Pod without the matching toleration getting scheduled elsewhere

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
25. kind
26. DaemonSet
27. Pod Scheduling — Affinity & Taints *(new)*
28. StatefulSet simple
29. StatefulSet RabbitMQ
30. NetworkPolicy *(new)*
31. RBAC *(new)*
32. Helm
33. Kubernetes Dashboard
34. CRDs *(new)*
