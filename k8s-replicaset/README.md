# ReplicaSet

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

```bash
kubectl get pods
```

Delete one of the Pods and watch the ReplicaSet immediately replace it:

```bash
kubectl delete pod <pod-name>
kubectl get pods -w
```

## Clean up

```bash
kubectl delete -f kuard.yml
```
