# StatefulSet

A StatefulSet is like a Deployment, but each Pod gets a stable identity: a predictable name, its own persistent storage, and an ordered startup and shutdown sequence. Use StatefulSets for workloads that need to remember who they are — databases, message queues, and other stateful services.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

Watch the Pods start up in order:

```bash
kubectl get pods -w
```

Unlike a Deployment, a StatefulSet starts Pods sequentially: `kuard-0` comes up first, then `kuard-1`, then `kuard-2`.

## Stable names

The Pod names are always `kuard-0`, `kuard-1`, and `kuard-2` — not random suffixes. Each Pod also gets a stable DNS name via the headless service:

``` text
kuard-0.kuard.default.svc.cluster.local
kuard-1.kuard.default.svc.cluster.local
kuard-2.kuard.default.svc.cluster.local
```

## Per-pod storage

Each Pod gets its own PersistentVolumeClaim from the `volumeClaimTemplate`:

```bash
kubectl get pvc
```

You will see `data-kuard-0`, `data-kuard-1`, and `data-kuard-2` — one per Pod. The `local-path` StorageClass is Rancher Desktop's built-in dynamic provisioner; it creates a PersistentVolume automatically for each claim.

## Stable identity after restart

Delete one of the Pods and watch it come back:

```bash
kubectl delete pod kuard-1
kubectl get pods -w
```

The replacement Pod is always named `kuard-1` and is reattached to the same PVC (`data-kuard-1`). In a Deployment, the replacement would get a random name and no memory of the old Pod's storage.

## Clean up

```bash
kubectl delete -f kuard.yml
```

Note that deleting a StatefulSet does **not** delete its PVCs — Kubernetes keeps them to avoid accidental data loss. Delete them explicitly if you no longer need them:

```bash
kubectl delete pvc -l app=kuard
```
