# Workshop todo

## README reordering

- [ ] Move Kustomize entry in `README.md` to after Secret (before Helm)

## New demos

### DaemonSet (`k8s-daemonset/`)

Position: after Readiness probe, before Job / CronJob.

- [ ] `kuard.yml` — DaemonSet with a `nodeSelector`-free example so it runs on all nodes; NodePort or port-forward to see the effect
- [ ] `README.md` — explain when to use a DaemonSet (node agents: logging, monitoring, security); show one pod per node with `kubectl get pods -o wide`

### Job and CronJob (`k8s-job/`)

Position: after DaemonSet, before Horizontal Pod Autoscaler.

- [ ] `job.yml` — a one-shot Job that runs a short task to completion
- [ ] `cronjob.yml` — a CronJob that runs the same task on a schedule
- [ ] `README.md` — show `kubectl get jobs`, completed pod status, and how CronJob creates Jobs automatically

### StatefulSet (`k8s-statefulset/`)

Position: after Persistent Volumes, before ConfigMap.

- [ ] `kuard.yml` — StatefulSet with a `volumeClaimTemplate`; show stable pod names and per-pod PVCs
- [ ] `README.md` — contrast with Deployment: stable identity (`kuard-0`, `kuard-1`), ordered rollout, per-pod storage; show that a pod keeps its PVC after restart

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

## README final order (Kubernetes section)

1. Pod
2. ReplicaSet
3. Service
4. Deployment
5. Ingress
6. Ingress challenge
7. Gateway API
8. Namespaces
9. Resources
10. Liveness probe
11. Readiness probe
12. Horizontal Pod Autoscaler
13. Volumes
14. Persistent Volumes
15. ConfigMap
16. DaemonSet *(new)*
17. StatefulSet *(new)*
18. Job / CronJob *(new)*
19. Secret
20. Sealed Secrets *(new)*
21. NetworkPolicy *(new)*
22. RBAC *(new)*
23. Kustomize *(moved)*
24. Helm
25. Kubernetes Dashboard
