# Startup probe

A startup probe protects slow-starting containers from the liveness probe. While the startup probe is still checking, the liveness probe is disabled. Once the startup probe succeeds, the liveness probe takes over.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Watch the pod come up:

```bash
kubectl get pods -w
```

Once it shows `Running`, follow the logs in a second terminal:

```bash
kubectl logs -f kuard
```

You'll see the startup probe checking every 5 seconds. Try opening <http://kuard.local>. What's happening?

The startup probe is waiting for `/tmp/started` to exist inside the container. Until it does, the pod is not ready. Create the file:

```bash
kubectl exec kuard -- touch /tmp/started
```

Watch the pod become ready. The site should now load. The startup probe has handed control to the liveness probe.

## Clean up

```bash
kubectl delete -f kuard.yml
```
