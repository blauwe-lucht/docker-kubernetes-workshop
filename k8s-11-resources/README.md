# Resources

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://kuard.local> in your browser.

Inspect the resource requests and limits on the Pods:

```bash
kubectl describe pods -l app=kuard
```

If your cluster has the metrics server installed, you can view live usage:

```bash
kubectl top pods -l app=kuard
```

### Exceed the memory limit

Open a second terminal to watch the Pods:

```bash
kubectl get pods -l app=kuard -w
```

In the browser, go to the **Memory** tab and allocate 500 MiB. That is more than the `200Mi` limit, so the kernel kills the container. Kubernetes restarts it in the same Pod: `RESTARTS` goes up by one for that Pod.

See why the container was restarted:

```bash
kubectl describe pods -l app=kuard
```

The Pod that restarted shows `Last State: Terminated` with `Reason: OOMKilled` and `Exit Code: 137`.

A container that exceeds its CPU limit is not killed. It is throttled: it simply gets less CPU time.

## Clean up

```bash
kubectl delete -f kuard.yml
```
