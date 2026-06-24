# Vertical Pod Autoscaler

The Vertical Pod Autoscaler (VPA) watches a workload's actual CPU and memory consumption and automatically right-sizes the resource requests on each pod. This is the complement to the HPA: instead of scaling *out* (more replicas), VPA scales *up* (bigger requests per pod).

The VPA has three components:

- **Recommender** — watches metrics and calculates recommendations
- **Updater** — applies recommendations to running pods
- **Admission controller** — patches new pods with the recommended requests at creation time (not installed in this demo)

This demo uses `InPlaceOrRecreate` mode: VPA tries to resize the pod's resources without restarting it, and falls back to evicting and recreating the pod if in-place resize is not supported.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Install the VPA controller

```bash
helm repo add fairwinds-stable https://charts.fairwinds.com/stable
helm install vpa fairwinds-stable/vpa --namespace vpa --create-namespace --set admissionController.enabled=false
kubectl rollout status deployment vpa-recommender -n vpa
```

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://kuard.local> and browse around for a minute to generate some traffic. The VPA recommender samples from the metrics server every 15 seconds, so a recommendation appears within 1–2 minutes.

In a separate terminal, watch for pod changes:

```bash
kubectl get pods -w
```

Once VPA has a recommendation it will apply it — either in-place (no restart) or by replacing the pod. Check the recommendation:

```bash
kubectl describe vpa kuard
```

Look for the `Recommendation` block in the output:

```
Status:
  Recommendation:
    Container Recommendations:
      Container Name: kuard
      Lower Bound:
        Cpu:     10m
        Memory:  20Mi
      Target:
        Cpu:     25m
        Memory:  100Mi
      Upper Bound:
        Cpu:     100m
        Memory:  200Mi
```

- **Target** — the requests VPA is applying
- **Lower Bound** — the minimum it considers safe
- **Upper Bound** — the maximum it expects to be needed
- **Uncapped Target** — the target before the `minAllowed`/`maxAllowed` bounds in the manifest are applied

Then confirm the pod's actual requests have been updated:

```bash
kubectl get pod -l app=kuard -o jsonpath='{.items[0].spec.containers[0].resources}'
```

Compare these to the original values in the Deployment (`cpu: 0.1`, `memory: 100Mi`) to see what VPA changed.

## Clean up

```bash
kubectl delete -f kuard.yml
helm uninstall vpa -n vpa
kubectl delete namespace vpa
```
