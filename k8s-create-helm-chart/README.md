# Creating a Helm Chart

The [Helm example](../k8s-helm/) installs a chart someone else wrote. This demo goes the other way: it's a small, complete Helm chart for kuard, written from scratch, meant as a starting point for your own application chart.

It packages the same Deployment/ConfigMap/Secret/Service/Ingress from the [Secret example](../k8s-secret/), but templated so common per-environment differences — namespace, image version, a startup argument — become `--set`/`-n` flags instead of copy-pasted YAML files.

The Ingress host is derived from `.Release.Namespace` (set with `helm install -n`), not a separate value — one flag drives both where resources land and what hostname reaches them, so there's nothing to keep in sync by hand.

## What's in the chart

```text
kuard/
  Chart.yaml            # chart metadata
  values.yaml            # default configuration
  values.schema.json     # validates values (e.g. image.tag must be blue/green/purple)
  templates/
    _helpers.tpl          # name/label/host helpers shared by every template
    deployment.yaml
    service.yaml
    ingress.yaml
    configmap.yaml
    secret.yaml
    NOTES.txt              # printed after install/upgrade
    tests/test-connection.yaml   # `helm test` hook
```

`_helpers.tpl` defines the standard `app.kubernetes.io/*` labels and a `kuard.fullname` helper, the same pattern `helm create` scaffolds — worth reusing as-is in your own chart.

## Configurable values

Namespace isn't a value here — it's set with `helm install/upgrade -n <namespace>` like any Helm chart, and drives the Ingress host: `default` → `kuard.local`, anything else → `<namespace>.kuard.local`.

| Value | Default | Effect |
| --- | --- | --- |
| `image.tag` | `blue` | kuard version to run — `blue`, `green`, or `purple` (see [k8s-deploy](../k8s-deploy/)); enforced by `values.schema.json`. The image repository itself is fixed (not a value) — the chart's probes, env vars, and startup command are all specific to kuard, so swapping in an unrelated image wouldn't work anyway. |
| `startParam` | `""` (empty) | Argument passed to the `/kuard` binary on startup. Left empty, no `command`/`args` override is rendered at all. |
| `replicaCount`, `service.*`, `ingress.*`, `resources.*`, `config.*`, `secret.*` | see `values.yaml` | Standard knobs, same idea as the values above. |

Liveness/readiness probes (`/healthy`, `/ready`) are fixed in the template, not values — they're kuard's actual endpoints, so there's no valid alternative to configure them to.

`secret.yaml` writes `secret.user`/`secret.password` under `stringData` rather than `data`, unlike the plain manifest in [k8s-secret](../k8s-secret/). `stringData` is write-only — Kubernetes base64-encodes it automatically when the Secret is created, so the chart doesn't need a `{{ ... | b64enc }}` in the template. `kubectl get secret -o yaml` still shows base64-encoded `data`, same as the k8s-secret demo.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file — set up in the [Ingress example](../k8s-ingress/). If you try the namespace override below, add `staging.kuard.local` too:

```bash
echo "127.0.0.1 staging.kuard.local" | sudo tee -a /etc/hosts
```

## Explore the chart before installing

```bash
helm lint ./kuard
helm template kuard ./kuard                                    # render manifests locally
helm install kuard ./kuard --dry-run --debug                   # render + validate against the cluster
```

## Install with defaults

```bash
helm install kuard ./kuard
```

Open <http://kuard.local>.

## Install into another namespace

```bash
helm install kuard-staging ./kuard \
  --namespace staging --create-namespace \
  --set image.tag=green
```

Open <http://staging.kuard.local>.

## Try the other values

```bash
helm upgrade kuard ./kuard --set startParam=hello-from-helm
helm upgrade kuard ./kuard --set image.tag=purple
helm upgrade kuard ./kuard --set replicaCount=1
```

Or point at a custom file instead of individual `--set` flags:

```bash
helm upgrade kuard ./kuard -f my-values.yml
```

## Test, inspect, roll back

```bash
helm test kuard
helm get values kuard
helm history kuard
helm rollback kuard
```

## Clean up

```bash
helm uninstall kuard
helm uninstall kuard-staging --namespace staging
kubectl delete namespace staging
```

## Ideas for extending this into your own chart

This chart deliberately stays small. A few directions worth exploring for your own application, each already demoed elsewhere in this repo:

- **Horizontal Pod Autoscaling** — add an `autoscaling.enabled` value and an `hpa.yaml` template; see [k8s-horizontal-pod-autoscaler](../k8s-horizontal-pod-autoscaler/).
- **Real secrets** — `secret.yaml` here commits plaintext values to `values.yaml`, which is fine for a demo but not for anything real. See [k8s-external-secrets](../k8s-external-secrets/) for pulling secrets from a proper store instead.
- **Blue/green or canary routing** — this chart deploys one version at a time; see [k8s-ingress-multi](../k8s-ingress-multi/) for splitting traffic across versions.
- **Multiple environments** — keep a `values-staging.yml` / `values-production.yml` per environment and layer them with `-f values.yml -f values-staging.yml`, rather than relying only on `--set`.
- **Dependencies** — if your app needs a database or cache, add it as a chart dependency in `Chart.yaml` (`dependencies:`) instead of hand-rolling its manifests.
- **CI/CD** — package (`helm package`), push to a chart repo or OCI registry, and deploy via GitOps; see the (in-progress) GitOps demo notes for this repo.
