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

Traefik is not included with Docker Desktop. Install the nginx ingress controller instead. Check the [supported versions table](https://github.com/kubernetes/ingress-nginx#supported-versions-table) for the right version for your Kubernetes release, then:

```bash
kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.15.1/deploy/static/provider/cloud/deploy.yaml
```

Then change `ingressClassName: traefik` to `ingressClassName: nginx` in all manifests.

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
