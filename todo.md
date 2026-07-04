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
6. Custom images (local registry)
7. Ingress challenge
8. Ingress — path-based routing
9. Gateway API
10. Namespaces
11. Resources
12. Liveness probe
13. Readiness probe
14. Startup probe
15. Kustomize
16. Horizontal Pod Autoscaler
17. Volumes
18. Persistent Volumes
19. ConfigMap
20. Secret
21. External Secrets
22. Job / CronJob
23. DaemonSet
24. StatefulSet simple
25. StatefulSet RabbitMQ
26. NetworkPolicy *(new)*
27. RBAC *(new)*
28. Helm
29. Kubernetes Dashboard
30. CRDs *(new)*
