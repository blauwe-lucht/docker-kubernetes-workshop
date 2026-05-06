# Deployment

## Apply

```bash
kubectl apply -f kuard.yml
```

## Access the application

Use `kubectl port-forward` to reach a pod without exposing it via a Service:

```bash
kubectl port-forward deployment/kuard 8080:8080
```

Open <http://localhost:8080> in your browser. The page shows the running pod's name and the image version (blue).

Press `Ctrl+C` to stop port-forwarding.

## Upgrade the image

Edit `kuard.yml` and change the image tag from `blue` to `green`:

```yaml
image: ongoonku/kuard-amd64:green
```

Apply the update and watch Kubernetes roll it out. Pick one to try each approach:

```bash
kubectl apply -f kuard.yml && kubectl rollout status deployment/kuard
kubectl apply -f kuard.yml && kubectl get pods -w
kubectl apply -f kuard.yml && kubectl get events -w
```

> **Note:** if you leave port-forwarding running during the upgrade, the connection will drop — the pod it was connected to gets replaced as part of the rolling update. This is expected behaviour, and a good illustration of what a rolling update actually does.

Once the rollout is complete, port-forward again to confirm the new version is running:

```bash
kubectl port-forward deployment/kuard 8080:8080
```

Open <http://localhost:8080> — the page now shows version `green`.

Another version you can try is `purple`.

## Clean up

```bash
kubectl delete -f kuard.yml
```
