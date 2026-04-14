# Ingress challenge

This manifest should expose kuard at <http://kuard.local>, but it does not work as intended.

## Apply

```bash
kubectl apply -f kuard.yml
```

Find and fix all the problems so the application loads correctly.

## Analyse

Check whether any Pods are running:

```bash
kubectl get pods
```

Inspect the Deployment if no Pods appear:

```bash
kubectl describe deployment web-app
```

Check whether the Service has any endpoints:

```bash
kubectl get endpoints frontend
```

Inspect the Service to verify its ports and selector:

```bash
kubectl describe service frontend
```

Inspect the Ingress to verify the hostname, backend service name, and port:

```bash
kubectl describe ingress web-ingress
```

Check recent cluster events for errors:

```bash
kubectl get events --sort-by='.lastTimestamp'
```

## Clean up

```bash
kubectl delete -f kuard.yml
```
