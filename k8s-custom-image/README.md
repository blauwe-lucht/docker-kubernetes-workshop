# Custom images (local registry)

Building an image with `docker build` only puts it in your container engine's local image store. Rancher Desktop lets you pick `dockerd` or `containerd` as the Container Engine, but its bundled Kubernetes (k3s) always pulls images through its own containerd — so whether that store is the same one Kubernetes reads from depends on which engine you picked. Running a local registry sidesteps the question entirely: push once, and Kubernetes pulls from it like it would from Docker Hub.

## How it fits together

```text
docker build → localhost:5000/modified-nginx:1 → docker push
                                                        ↓
                                          local registry (compose.yml)
                                                        ↓
                                Kubernetes pulls localhost:5000/modified-nginx:1
                                                        ↓
                                  Deployment → Service → Ingress → http://custom.local
```

## Prerequisites

Add `custom.local` to your hosts file.

**Linux/Mac:**

```bash
echo "127.0.0.1 custom.local" | sudo tee -a /etc/hosts
```

**Windows** (run as Administrator):

```cmd
echo 127.0.0.1 custom.local >> C:\Windows\System32\drivers\etc\hosts
```

## Run the local registry

```bash
docker compose up -d
```

Pushed images are stored in the `registry-data` volume, so they survive `docker compose down`/`up` — you don't need to re-push after restarting the registry.

## Build and push the custom image

Reuse the modified Nginx image from [../dockerfile-simple](../dockerfile-simple/), tagged for the local registry:

```bash
docker build -t localhost:5000/modified-nginx:1 ../dockerfile-simple
docker push localhost:5000/modified-nginx:1
```

To test if the image is actually present in the registry, run

```bash
curl http://localhost:5000/v2/_catalog
curl http://localhost:5000/v2/modified-nginx/tags/list
```

## Deploy

```bash
kubectl apply -f custom-app.yml
```

## See the effect

Open <http://custom.local> in your browser. This is the exact image you just built and pushed — not one from Docker Hub.

## Update and redeploy

Change [../dockerfile-simple/index.html](../dockerfile-simple/index.html), then:

### The fast and ugly way

```bash
docker build -t localhost:5000/modified-nginx:1 ../dockerfile-simple
docker push localhost:5000/modified-nginx:1
kubectl rollout restart deployment/custom-app
```

The tag `1` is reused on every rebuild, so `custom-app.yml` sets `imagePullPolicy: Always` to make sure Kubernetes fetches the new image instead of reusing the cached one.

### The proper way

```bash
docker build -t localhost:5000/modified-nginx:2 ../dockerfile-simple
docker push localhost:5000/modified-nginx:2
```

Change the manifest to use the new version (left as an exercise), then

```bash
kubectl apply -f custom-app.yml
```

## Clean up

```bash
kubectl delete -f custom-app.yml
docker compose down -v
```
