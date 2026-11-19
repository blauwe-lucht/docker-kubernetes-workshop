# StatefulSet — RabbitMQ with replication

This demo runs a three-node RabbitMQ cluster as a StatefulSet. Each node has its own persistent storage and a stable DNS name via the headless service. Nodes discover each other automatically using DNS peer discovery.

A [Quorum Queue](https://www.rabbitmq.com/docs/quorum-queues) is used to demonstrate replication: messages are written to a majority of nodes using the Raft consensus algorithm, so the cluster survives the loss of a node without losing data.

## Prerequisites

Add `rabbitmq.local` to your hosts file.

**Linux/Mac:**

```bash
echo "127.0.0.1 rabbitmq.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 rabbitmq.local >> C:\Windows\System32\drivers\etc\hosts
```

## Apply

```bash
kubectl apply -f rabbitmq.yml
```

> If you deleted and re-applied the manifest without also deleting the PVCs (see Clean up), RabbitMQ will fail to boot: each node's stored state says it was part of a running cluster and refuses to start until the others are available first. Delete the PVCs before re-applying to get a clean start.

Watch the nodes start up in order (this will take a couple of minutes):

```bash
kubectl get pods -w
```

Once all three Pods are ready, verify the cluster formed correctly:

```bash
kubectl exec rabbitmq-0 -- rabbitmqctl cluster_status
```

You should see all three nodes listed as running members.

## See the effect

Open <http://rabbitmq.local> and log in with **admin / workshop**.

### Create a Quorum Queue

1. Go to **Queues and Streams** → **Add a new queue**
2. Set **Type** to **Quorum**
3. Name it `demo` and click **Add queue**

The queue details show **Leader** (which node owns it) and **Members** (all nodes storing a copy).

### Publish messages

On the queue page, expand **Publish message** and publish a few messages. Note which node is the current leader.

## Display messages

On the queue page, expand **Get messages**, make sure 'Ack Mode' is set to 'Nack message requeue true', enter 10 after 'Messages' and press 'Get Messages(s)'.

### Trigger a failover

Delete the leader node. If the leader is `rabbitmq-0`:

```bash
kubectl delete pod rabbitmq-0
```

Watch the cluster heal:

```bash
kubectl get pods -w
```

Watch <http://rabbitmq.local> (a reload is not needed) — the queue is still there, a new leader has been elected, and all messages are intact. When `rabbitmq-0` comes back it automatically rejoins the cluster.

> The message count may show 0 during leader election. This is a stats reporting gap, not data loss — messages are still consumable throughout. The correct count returns once a new leader is established.

## Bring the cluster down cleanly/remove resources while keeping the data

Using `delete -f` deletes all resources at once, so the pods are killed simultaneously without an ordered shutdown. RabbitMQ's Mnesia database records that other nodes were still running when each node stopped — and on the next start it refuses to boot until those nodes are available again.

The *correct* way is to scale to zero first. StatefulSets scale down in reverse ordinal order: rabbitmq-2 stops first, then rabbitmq-1, then rabbitmq-0. Each node leaves the cluster gracefully before the next is stopped. rabbitmq-0 is the last to stop, so it records itself as having left cleanly and can boot without waiting for the others on the next start.

```bash
kubectl scale statefulset rabbitmq --replicas=0
kubectl get pods -w
# wait for all pods to terminate
kubectl delete -f rabbitmq.yml
```

Bring the cluster back up:

```bash
kubectl apply -f rabbitmq.yml
kubectl get pods -w
```

The messages will still be in the demo message queue.

## Clean up

```bash
kubectl delete -f rabbitmq.yml
kubectl delete pvc -l app=rabbitmq
```
