# Namespaces

## Prerequisites

The nginx ingress controller must be running. It is set up in the [Ingress example](../k8s-ingress/).

Add both hostnames to your hosts file so they resolve locally.

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

## Apply

```bash
kubectl apply -f dev.yml
kubectl apply -f prod.yml
```

## See the effect

Open <http://kuard.dev.local> and <http://kuard.prod.local> in your browser. Both run the same application and use the same resource names (`kuard`), but are fully isolated from each other.

Notice that without `-n`, kubectl only shows resources in the default namespace:

```bash
kubectl get pods
```

You need to specify a namespace to see what is running:

```bash
kubectl get pods -n dev
kubectl get pods -n prod
```

Or list across all namespaces at once:

```bash
kubectl get pods -A
```

The single shared ingress controller routes traffic to the correct namespace based on the hostname — there is no separate controller per environment.

## Clean up

```bash
kubectl delete -f dev.yml
kubectl delete -f prod.yml
```
