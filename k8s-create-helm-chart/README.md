# Creating a Helm Chart

The [Helm example](../k8s-helm/) installs a chart someone else wrote. This demo goes the other way: it's a small, complete Helm chart for kuard, written from scratch, meant as a starting point for your own application chart.

It packages the same Deployment/ConfigMap/Secret/Service/Ingress from the [Secret example](../k8s-secret/), but templated so common per-environment differences — environment, image version, a startup argument — become a values file (or `-n` flag) instead of copy-pasted YAML files.

Prefer a values file (`-f demo-values.yml`) over ad hoc `--set` flags. This is the Infrastructure-as-Code principle at work: a file is versionable, reviewable in a PR/MR, and reproducible by anyone who checks it out — a `--set` flag someone typed once lives only in their shell history. [demo-values.yml](demo-values.yml) in this directory sets every configurable value in the chart as a working example.

The Ingress host is driven by `environment`, a value — deliberately *not* derived from the Kubernetes namespace. Namespace naming conventions (`<app>-<env>`, platform-mandated prefixes, collision-avoidance since namespace names are cluster-wide unique) don't always make a sensible subdomain, so this chart keeps "where it's deployed" (`-n <namespace>`) and "what it's called" (`environment`) as two independent choices — see `demo-values.yml`, which is deployed into namespace `kuard-demo` but sets `environment: demo`.

## What's in the chart

```text
k8s-create-helm-chart/
  demo-values.yml         # example values file — every configurable item, set explicitly
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

Namespace isn't a value here — it's set with `helm install/upgrade -n <namespace>` like any Helm chart, same as always. It's independent of `environment` below.

| Value | Default | Effect |
| --- | --- | --- |
| `environment` | `dev` | Builds the Ingress host: `prd` → the bare `kuard.local`, anything else → `<environment>.kuard.local`. Not tied to the Kubernetes namespace — see above. |
| `image.tag` | `blue` | kuard version to run — `blue`, `green`, or `purple` (see [k8s-deploy](../k8s-deploy/)); enforced by `values.schema.json`. The image repository itself is fixed (not a value) — the chart's probes, env vars, and startup command are all specific to kuard, so swapping in an unrelated image wouldn't work anyway. |
| `startParam` | `""` (empty) | Argument passed to the `/kuard` binary on startup. Left empty, no `command`/`args` override is rendered at all. |
| `bindMounts` | `[]` (none) | Extra host bind mounts (`hostPath` volumes), each `{name, hostPath, mountPath, readOnly}`; enforced by `values.schema.json`. |
| `replicaCount`, `service.*`, `ingress.*`, `resources.*`, `config.*`, `secret.*` | see `values.yaml` | Standard knobs, same idea as the values above. |

Liveness/readiness probes (`/healthy`, `/ready`) are fixed in the template, not values — they're kuard's actual endpoints, so there's no valid alternative to configure them to.

`secret.yaml` writes `secret.user`/`secret.password` under `stringData` rather than `data`, unlike the plain manifest in [k8s-secret](../k8s-secret/). `stringData` is write-only — Kubernetes base64-encodes it automatically when the Secret is created, so the chart doesn't need a `{{ ... | b64enc }}` in the template. `kubectl get secret -o yaml` still shows base64-encoded `data`, same as the k8s-secret demo.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file — set up in the [Ingress example](../k8s-ingress/). That's only used when `environment: prd`. The default (`environment: dev`) and the values-file walkthrough below (`environment: demo`) need their own entries:

```text
127.0.0.1 dev.kuard.local
127.0.0.1 demo.kuard.local
```

## Explore the chart before installing

```bash
helm lint ./kuard -f demo-values.yml
helm template kuard ./kuard -f demo-values.yml                                    # render manifests locally
helm install kuard ./kuard -f demo-values.yml --dry-run=client --debug            # render + validate against the cluster
```

## Install with defaults

```bash
helm install kuard ./kuard
```

Open <http://dev.kuard.local> — `environment` defaults to `dev`, regardless of which namespace this landed in (here, `default`, since `-n` wasn't passed).

## Install using the values file

```bash
helm install kuard-demo ./kuard --namespace kuard-demo --create-namespace -f demo-values.yml
```

Open <http://demo.kuard.local>.

## Change a value

Edit `demo-values.yml` (e.g. bump `replicaCount`, change `image.tag`) and re-apply:

```bash
helm upgrade kuard-demo ./kuard --namespace kuard-demo -f demo-values.yml
```

## Test, inspect, roll back

```bash
helm test kuard-demo --namespace kuard-demo
helm get values kuard-demo --namespace kuard-demo
helm history kuard-demo --namespace kuard-demo
helm rollback kuard-demo --namespace kuard-demo
```

## Clean up

```bash
helm uninstall kuard
helm uninstall kuard-demo --namespace kuard-demo
kubectl delete namespace kuard-demo
```
