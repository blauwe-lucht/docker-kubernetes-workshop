# kind (Kubernetes IN Docker)

Rancher Desktop's built-in cluster is a single node, so any "multi-node" concept — like the DaemonSet demo — is really only ever running on one machine under the hood. `kind` runs each cluster node as its own Docker container, so you can spin up a real multi-node cluster in seconds using the Docker engine you already have.

```text
Docker (dockerd, via Rancher Desktop)
├── workshop-control-plane   (container acting as the control-plane node)
├── workshop-worker          (container acting as a worker node)
└── workshop-worker2         (container acting as a worker node)
```

## Prerequisites

- Rancher Desktop's **Container Engine** must be set to **dockerd (moby)** in Preferences. `kind` talks to the Docker API directly and does not support Rancher Desktop's containerd option.
- Install `kind` — see <https://kind.sigs.k8s.io/docs/user/quick-start/#installation>.

**Windows:**

```cmd
winget install --id Kubernetes.kind -e --source winget --accept-package-agreements --accept-source-agreements
```

**Linux/Mac:** download the binary from the [releases page](https://github.com/kubernetes-sigs/kind/releases), or use your package manager if it ships one.

## Create a multi-node cluster

```bash
kind create cluster --name workshop --config kind-config.yml
```

[kind-config.yml](./kind-config.yml) asks for one control-plane node and two worker nodes — each becomes its own Docker container:

```bash
docker ps
```

`kind` also points `kubectl` at the new cluster automatically:

```bash
kubectl config get-contexts
kubectl config current-context
kubectl get nodes -o wide
```

## Deploy across nodes

```bash
kubectl apply -f kuard.yml
kubectl get pods -o wide
```

Scale up to see it more clearly:

```bash
kubectl scale deployment/kuard --replicas=6
kubectl get pods -o wide
```

Still only the two worker nodes.

## Switch back to Rancher Desktop

```bash
kubectl config get-contexts
kubectl config use-context rancher-desktop
```

## Clean up

```bash
kubectl config use-context rancher-desktop
kind delete cluster --name workshop
docker ps
```
