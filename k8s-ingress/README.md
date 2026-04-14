# Ingress

## Prerequisites

### Rancher Desktop

Disable the built-in Traefik ingress controller in **Preferences > Kubernetes** by unchecking **Enable Traefik**.

### Both platforms

Install the nginx ingress controller:

```bash
kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.12.1/deploy/static/provider/cloud/deploy.yaml
```

Add `kuard.local` to your hosts file so the Ingress hostname resolves locally.

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

Open <http://kuard.local> in your browser.

## Clean up

```bash
kubectl delete -f kuard.yml
```
