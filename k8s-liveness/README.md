# Liveness probe

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open a terminal to watch the Pod for restarts:

```bash
kubectl get pod healthcheckdemo -w
```

In a second terminal, forward the Pod's port to your machine:

```bash
kubectl port-forward pod/healthcheckdemo 8080:8080
```

Open <http://localhost:8080> in your browser. Go to the **Liveness Probe** tab and click **Fail**. After one failed check (see `failureThreshold` in the manifest), Kubernetes will restart the container. You will see the restart count increment in the first terminal.

## Clean up

```bash
kubectl delete -f kuard.yml
```
