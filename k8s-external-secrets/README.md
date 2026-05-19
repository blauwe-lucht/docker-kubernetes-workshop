# External Secrets Operator

Kubernetes Secrets are base64-encoded, not encrypted, and should never be committed to git. The External Secrets Operator (ESO) solves this by pulling secret values from an external store — a dedicated system that handles encryption, access control, and auditing.

ESO introduces two resources:

- **ClusterSecretStore** — how to connect to the external store
- **ExternalSecret** — which secrets to pull and how to map them into a Kubernetes Secret

This demo uses [Infisical](https://infisical.com) as the external store, installed locally via Helm.

## How it fits together

```text
Infisical (secrets store)
    ↓  Token Auth (access token)
ClusterSecretStore
    ↓  ExternalSecret
Kubernetes Secret  (secret-config)
    ↓  env vars
kuard pod  →  http://kuard.local  →  Server Env tab
```

## Prerequisites

Add `kuard.local` to your hosts file.

**Linux/Mac:**

```bash
echo "127.0.0.1 kuard.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 kuard.local >> C:\Windows\System32\drivers\etc\hosts
```

## Install

### 1. External Secrets Operator

```bash
helm repo add external-secrets https://charts.external-secrets.io
helm install external-secrets external-secrets/external-secrets --namespace external-secrets --create-namespace
kubectl rollout status deployment external-secrets -n external-secrets
```

### 2. Infisical

Create the namespace and the secrets Infisical needs to start (encryption key and JWT signing secret):

```bash
kubectl apply -f infisical-secrets.yml
```

Install Infisical with its bundled PostgreSQL and Redis:

```bash
helm repo add infisical-helm-charts https://dl.cloudsmith.io/public/infisical/helm-charts/helm/charts/
helm install infisical infisical-helm-charts/infisical-standalone --namespace infisical -f values-infisical.yml
kubectl rollout status deployment/infisical-infisical-standalone-infisical -n infisical
```

### 3. Set up the project and ESO credentials

Apply the setup job. It calls the Infisical bootstrap API to create the admin user, creates the `demo-ws` project, adds the `user` and `password` secrets, and stores the access token as a Kubernetes Secret for ESO to use:

```bash
kubectl apply -f setup.yml
kubectl wait --for=condition=complete job/infisical-setup --namespace infisical --timeout=120s
```

### 4. Wire ESO to Infisical

```bash
kubectl apply -f clustersecretstore.yml
```

### 5. Deploy kuard

```bash
kubectl apply -f kuard.yml
```

`kuard.yml` includes the `ExternalSecret`, which tells ESO which secrets to pull from Infisical and how to map them into a Kubernetes Secret. Check that it synced:

```bash
kubectl get externalsecret secret-config
```

The status should show `Ready`. Open <http://kuard.local> and go to **Server Env**. You should see `SECRET_USER` and `SECRET_PASSWORD` populated from Infisical — the pod config never touches the raw values.

Neither `clustersecretstore.yml` nor `kuard.yml` contains any sensitive data — both are safe to commit to git.

## How ESO authenticates to Infisical

The setup job bootstraps the Infisical instance via API and stores the resulting identity access token in the `infisical-creds` Kubernetes Secret (in the `infisical` namespace). `ClusterSecretStore` uses Token Auth, passing this token on every request to the Infisical API.

## Clean up

```bash
kubectl delete -f kuard.yml
kubectl delete -f clustersecretstore.yml
kubectl delete -f setup.yml
kubectl delete -f infisical-secrets.yml
helm uninstall infisical -n infisical
kubectl delete pvc --all -n infisical
helm uninstall external-secrets -n external-secrets
kubectl delete namespace infisical
kubectl delete namespace external-secrets
```
