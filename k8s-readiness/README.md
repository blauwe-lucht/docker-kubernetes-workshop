# Readiness probe

## Prerequisites

The nginx ingress controller must be running and `kuard.local` must resolve to `127.0.0.1` in your hosts file. Both are set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open a terminal to watch the Pods:

```bash
kubectl get pods -w
```

Open <http://kuard.local> in your browser. Go to the **Readiness Probe** tab and click **Fail**. After one failed check (see `failureThreshold` in the manifest), Kubernetes marks the Pod as not ready and stops routing traffic to it. You will see the `READY` column drop in the first terminal.

Click **Succeed** to restore the Pod to ready state.

## Clean up

```bash
kubectl delete -f kuard.yml
```
