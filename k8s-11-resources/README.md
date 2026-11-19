# Resources

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://kuard.local> in your browser.

Inspect the resource limits and readiness probe on the Pods:

```bash
kubectl describe pods -l app=kuard
```

If your cluster has the metrics server installed, you can view live usage:

```bash
kubectl top pods -l app=kuard
```

## Clean up

```bash
kubectl delete -f kuard.yml
```
