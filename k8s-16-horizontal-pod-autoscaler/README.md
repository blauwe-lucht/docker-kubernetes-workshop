# Horizontal Pod Autoscaler

A HorizontalPodAutoscaler (HPA) changes the number of replicas of a Deployment based on a metric. Here the metric is CPU utilisation: the average CPU usage of the Pods as a percentage of their CPU **request**.

kuard requests `0.1` CPU and the HPA targets 50%, so it adds Pods when they use more than 0.05 CPU on average, up to 10 replicas.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-05-ingress/).

The HPA reads CPU usage from the metrics server. k3s and Rancher Desktop include it. Check that it works:

```bash
kubectl top nodes
```

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open a terminal to watch the HPA:

```bash
kubectl get hpa kuard -w
```

`TARGETS` shows the current CPU utilisation against the 50% target. Without load it stays around 1% and `REPLICAS` stays at 1.

Open <http://kuard.local> in your browser and go to the **KeyGen Workload** tab. Enable it, set the time to run to 180 seconds and submit. kuard now generates keys, which keeps the CPU busy.

Within a minute `TARGETS` rises to about 200%: the Pod uses its full CPU limit of `0.2`, twice its request. `REPLICAS` goes up to 4 or 5. See where the CPU goes:

```bash
kubectl top pods -l app=kuard
```

Only the Pod that runs the workload is busy. The new Pods are idle, so the **average** drops back to about 50% and the HPA stops adding Pods. Scaling out only helps when the load is spread over the Pods, as with real requests through a Service.

After 180 seconds the workload stops. Within a minute the HPA scales back to 1 replica.

See what the HPA decided and why:

```bash
kubectl describe hpa kuard
```

### Behavior

The `behavior` section in `kuard.yml` controls how fast the HPA scales: at most 2 Pods per 5 seconds, both up and down. The `stabilizationWindowSeconds` of 5 seconds keeps the demo quick. Without it, Kubernetes waits 5 minutes before scaling down, to avoid flapping when load goes up and down.

## Clean up

```bash
kubectl delete -f kuard.yml
```
