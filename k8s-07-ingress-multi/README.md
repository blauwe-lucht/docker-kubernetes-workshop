# Ingress — path-based routing

A single Ingress routes two URL paths to two different backends. The path prefix is stripped before the request reaches each pod, so the pod sees `/` rather than `/blue` or `/green`.

```text
kuard.local/blue  →  strip /blue  →  blue  (blue page)
kuard.local/green →  strip /green →  green (green page)
```

Each backend is an `nginx:alpine` container that serves a single inline HTML page — no external assets, so prefix stripping works cleanly.

Kubernetes Ingress has no built-in strip-prefix mechanism. This demo adds a Traefik `Middleware` resource and wires it to the Ingress via an annotation.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1`. If you completed the Ingress demo already, skip this step.

**Linux/Mac:**

```bash
echo "127.0.0.1 kuard.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 kuard.local >> C:\Windows\System32\drivers\etc\hosts
```

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://kuard.local/blue> and <http://kuard.local/green>. Each shows a different coloured page, confirming the request reached the correct backend with the prefix stripped.

## Clean up

```bash
kubectl delete -f kuard.yml
```
