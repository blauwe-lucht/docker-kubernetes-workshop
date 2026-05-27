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

## README final order (Kubernetes section)

1. Pod
2. ReplicaSet
3. Service
4. Deployment
5. Ingress
6. Ingress challenge
7. Ingress — path-based routing
8. Gateway API
9. Namespaces
10. Resources
11. Liveness probe
12. Readiness probe
13. Startup probe
14. Kustomize
15. Horizontal Pod Autoscaler
16. Volumes
17. Persistent Volumes
18. ConfigMap
19. Secret
20. External Secrets
21. Job / CronJob
22. DaemonSet
23. StatefulSet simple
24. StatefulSet RabbitMQ
25. NetworkPolicy *(new)*
26. RBAC *(new)*
27. Helm
28. Kubernetes Dashboard
29. CRDs *(new)*
