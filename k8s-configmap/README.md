# ConfigMap

A ConfigMap stores configuration data as key-value pairs, separate from the container image. This lets you keep the same image across environments and inject different configuration at deploy time.

This demo defines a ConfigMap with two simple values (`param1`, `param2`) and a small config file (`config.yml`), then consumes it from a kuard Deployment in two ways at once:

- `param1` and `param2` are injected as environment variables and passed to the container's startup command.
- The whole ConfigMap is also mounted as a volume at `/config`, so every key (including `config.yml`) shows up there as a file.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Check that the ConfigMap exists and inspect its contents:

```bash
kubectl get configmap test-config -o yaml
```

Open <http://kuard.local> in your browser and go to the **Server Env** tab. You should see `PARAM1` and `PARAM2` set to the values from the ConfigMap.

Then check the **File System Browser** tab and navigate to `/config`. You'll find `param1`, `param2`, and `config.yml` each present as a separate file, one per key in the ConfigMap.

The File System Browser does not show the actual directory&file structure that Kubernetes creates.
Open a shell in one of the containers and see the actual structure with:

```bash
ls -al /config
```

You can change a config value without touching the image:

```bash
kubectl edit configmap test-config
```

Environment variables are only read when a container starts, so a running Pod won't pick up the change — you'd need to restart it (e.g. `kubectl rollout restart deployment/kuard`). Mounted volume files, however, update in place after a short delay, without restarting the Pod.

## Clean up

```bash
kubectl delete -f kuard.yml
```
