# Kubernetes Dashboard

## Installation

``` bash
helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard/
helm install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard --create-namespace --namespace kubernetes-dashboard
kubectl apply -f dashboard/dashboard-adminuser.yaml
kubectl -n kubernetes-dashboard create token admin-user
# Copy the output of the last command, this is the bearer token we need to log in.
kubectl -n kubernetes-dashboard port-forward svc/kubernetes-dashboard-kong-proxy 8443:443
```

You can now point your browser at <https://localhost:8443>. Use the bearer token to log in.

## Uninstallation

``` bash
helm uninstall kubernetes-dashboard --namespace kubernetes-dashboard
```
