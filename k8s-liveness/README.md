# Liveness probe

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open a terminal to watch the Pods:

```bash
kubectl get pods -w
```

Open <http://kuard.local> in your browser. Go to the **Liveness Probe** tab and click **Fail**. After one failed check (see `failureThreshold` in the manifest), Kubernetes will restart the container. You will see the restart count increment in the first terminal.

## Clean up

```bash
kubectl delete -f kuard.yml
```
