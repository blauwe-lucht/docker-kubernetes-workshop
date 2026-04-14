# Deployment

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://localhost:30042> in your browser.

Watch a rolling update in action by scaling the Deployment:

```bash
kubectl scale deployment kuard --replicas=5
kubectl get pods -w
```

Kubernetes replaces Pods gradually, keeping the application available throughout.

## Clean up

```bash
kubectl delete -f kuard.yml
```
