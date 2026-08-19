# Helm

## Install Helm

See <https://helm.sh/docs/intro/install/>

### Windows

``` cmd
winget install Helm.Helm
```

### Linux

``` bash
curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash
```

## Add cloudpirates repo

``` bash
helm repo add cloudpirates https://cloudpirates-io.github.io/helm-charts/
helm repo update cloudpirates
```

## Install Helm chart with defaults

``` bash
helm install my-first-helm-release cloudpirates/nginx
helm list
```

## Update with an actual site

``` bash
helm upgrade my-first-helm-release cloudpirates/nginx -f values.yml
helm list
helm history my-first-helm-release
```

## Roll back to previous version

```bash
helm rollback my-first-helm-release
helm history my-first-helm-release
```

## Remove release

``` bash
helm delete my-first-helm-release
```
