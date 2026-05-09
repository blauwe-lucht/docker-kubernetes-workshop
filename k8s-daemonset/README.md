# DaemonSet

A DaemonSet ensures that exactly one Pod runs on every node in the cluster. A common use case is log collection: a log collector runs on every node and captures the logs of all Pods scheduled there, then ships them to a central store.

This demo runs a [Fluent Bit](https://fluentbit.io/) DaemonSet that tails all container log files on the node and prints them to its own stdout. A kuard Deployment provides the log traffic to observe.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
kubectl apply -f fluent-bit.yml
```

## See the effect

Check that you have one Fluent Bit Pod per node (and three kuard Pods):

```bash
kubectl get pods -o wide
```

Open a terminal and follow the Fluent Bit log stream:

```bash
kubectl logs daemonset/fluent-bit -f
```

Open <http://kuard.local> in your browser and click around — visit **Memory**, **Liveness Probe**, **Readiness Probe**. Switch back to the first terminal and watch the kuard request logs appear in the Fluent Bit output.

Notice that Fluent Bit is collecting logs from all three kuard Pods through a single log collector on the node. On a multi-node cluster each node would have its own Fluent Bit Pod, and together they would cover every Pod in the cluster.

## Clean up

```bash
kubectl delete -f kuard.yml
kubectl delete -f fluent-bit.yml
```
