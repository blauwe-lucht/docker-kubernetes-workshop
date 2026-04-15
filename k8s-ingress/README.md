# Ingress

## Prerequisites

Add `kuard.local` to your hosts file so the Ingress hostname resolves locally.

**Linux/Mac:**

```bash
echo "127.0.0.1 kuard.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 kuard.local >> C:\Windows\System32\drivers\etc\hosts
```

### Docker Desktop

Traefik is not included with Docker Desktop. Install it via Helm:

```bash
helm repo add traefik https://traefik.github.io/charts
helm repo update
helm install traefik traefik/traefik --namespace traefik --create-namespace
```

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Open <http://kuard.local> in your browser.

## Clean up

```bash
kubectl delete -f kuard.yml
```
