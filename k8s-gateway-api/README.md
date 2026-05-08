# Gateway API

Gateway API is the successor to Ingress. It splits the routing concern into three separate resources with distinct ownership, instead of combining everything in a single `Ingress` object.

| Resource | Owner | Defines |
| --- | --- | --- |
| `GatewayClass` | Infrastructure team | Which controller handles gateways (e.g. Traefik) |
| `Gateway` | Cluster operator | A listener: protocol, port, and which routes may attach |
| `HTTPRoute` | Developer | Routing rules: hostnames, paths, and backend services |

This separation means developers only manage `HTTPRoute`. They never touch load balancer or controller configuration. The `GatewayClass` and `Gateway` are set up once by the platform team and shared across applications.

## Prerequisites

Install the Gateway API CRDs (see [this page](https://github.com/kubernetes-sigs/gateway-api/releases/) for the latest stable release):

```bash
kubectl apply -f https://github.com/kubernetes-sigs/gateway-api/releases/download/v1.5.1/standard-install.yaml
```

Traefik 3.x is included with Rancher Desktop but its Gateway API provider is not enabled by default. Enable it with a `HelmChartConfig` — this is a one-time change per cluster and has no effect on existing Ingress resources:

```bash
kubectl apply -f - <<EOF
apiVersion: helm.cattle.io/v1
kind: HelmChartConfig
metadata:
  name: traefik
  namespace: kube-system
spec:
  valuesContent: |-
    providers:
      kubernetesGateway:
        enabled: true
EOF
```

This triggers a brief Traefik rollout. Once it settles, a `GatewayClass` named `traefik` is created automatically. Verify before continuing:

```bash
kubectl get gatewayclass
```

Add `kuard.local` to your hosts file so the hostname resolves locally.

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

Inspect the resources:

```bash
kubectl get gateway,httproute
kubectl describe httproute kuard
```

## Compare with Ingress

The `HTTPRoute` in this example does the same job as the `Ingress` in the previous example:

**Before — Ingress:**

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
spec:
  ingressClassName: traefik
  rules:
    - host: kuard.local
      http:
        paths:
          - path: /
            pathType: Prefix
            backend:
              service:
                name: kuard
                port:
                  number: 8080
```

**After — HTTPRoute:**

```yaml
apiVersion: gateway.networking.k8s.io/v1
kind: HTTPRoute
spec:
  parentRefs:
    - name: kuard       # which Gateway to attach to
  hostnames:
    - kuard.local
  rules:
    - matches:
        - path:
            type: PathPrefix
            value: /
      backendRefs:
        - name: kuard
          port: 8080
```

The `ingressClassName` is replaced by a `parentRefs` reference to a `Gateway`. The routing rules themselves are equivalent.

## Clean up

```bash
kubectl delete -f kuard.yml
```
