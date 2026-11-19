# Service

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

The Service exposes the ReplicaSet on port 30042. Open <http://localhost:30042> in your browser.
Reload a few times — notice the hostname changing as the Service load balances across replicas.

```bash
kubectl get svc kuard
```

## Clean up

```bash
kubectl delete -f kuard.yml
```
