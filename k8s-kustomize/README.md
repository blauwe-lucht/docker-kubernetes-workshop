# Kustomize

Kustomize lets you define a base configuration once and overlay environment-specific changes on top, without duplicating YAML. It is built into kubectl — no extra tools needed.

This example deploys the same application to `dev` and `prod` namespaces. The base defines the shared configuration; each overlay changes only what differs.

| | dev | prod |
| --- | --- | --- |
| | dev | prod |
|---|---|---|
| Namespace | `dev` | `prod` |
| Replicas | 1 | 3 |
| Host | `kuard.dev.local` | `kuard.prod.local` |
| Environment | `dev` | `prod` |
| CPU limit | `0.1` | `0.2` |
| Memory limit | `100Mi` | `200Mi` |

## Prerequisites

The Traefik ingress controller must be running. On Rancher Desktop it is included by default. Docker Desktop users should follow the setup instructions in the [Ingress example](../k8s-ingress/).

Add both hostnames to your hosts file if you haven't already:

**Linux/Mac:**

```bash
echo "127.0.0.1 kuard.dev.local" | sudo tee -a /etc/hosts
echo "127.0.0.1 kuard.prod.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 kuard.dev.local >> C:\Windows\System32\drivers\etc\hosts
echo 127.0.0.1 kuard.prod.local >> C:\Windows\System32\drivers\etc\hosts
```

## Preview

See what Kustomize will generate before applying it:

```bash
kubectl kustomize overlays/dev
kubectl kustomize overlays/prod
```

## Apply

```bash
kubectl apply -k overlays/dev
kubectl apply -k overlays/prod
```

Open <http://kuard.dev.local> and <http://kuard.prod.local> in your browser.

## Clean up

```bash
kubectl delete -k overlays/dev
kubectl delete -k overlays/prod
```
