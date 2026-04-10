# Helm

## Install Helm

See <https://helm.sh/docs/intro/install/>

### Windows

``` cmd
winget install Helm.Helm
```

### Linux

``` bash
sudo snap install helm --classic
```

## Add bitnami repo

``` bash
helm repo add bitnami https://charts.bitnami.com/bitnami
```

## Install Helm chart with defaults

``` bash
helm install my-first-helm-release bitnami/nginx
helm list
```

## Update with an actual site

``` bash
helm upgrade my-first-helm-release bitnami/nginx -f helm/values.yml
helm list
```

## Remove release

``` bash
helm delete my-first-helm-release
```
