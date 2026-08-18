# Secret

A Secret is Kubernetes' way of storing sensitive values — passwords, tokens, keys — separately from the container image and from regular configuration. It looks and behaves a lot like a ConfigMap (see the [ConfigMap example](../k8s-configmap/)), but its values are base64-encoded and it's treated differently by tooling (e.g. `kubectl get` hides the values by default).

This demo reuses the ConfigMap from the previous example and adds a Secret (`secret-config`) holding a `user` and `password`. The Secret is mounted as a volume at `/secret`, so each key shows up there as a file — the same mechanism used for the ConfigMap at `/config`.

> **Note:** base64 is encoding, not encryption. Anyone with read access to the Secret object (or etcd) can decode the values trivially. Secrets keep sensitive data out of Pod specs and image layers, but on their own they don't protect it at rest — see the [External Secrets example](../k8s-external-secrets/) for pulling real secrets from a proper secret store.

## Prerequisites

`kuard.local` must resolve to `127.0.0.1` in your hosts file. This is set up in the [Ingress example](../k8s-ingress/).

## Apply

```bash
kubectl apply -f kuard.yml
```

## See the effect

Check the Secret — note that `kubectl get` does not print the values in plain text:

```bash
kubectl get secret secret-config -o yaml
```

Decode a value locally:

```bash
kubectl get secret secret-config -o jsonpath='{.data.password}' | base64 -d
```

Open <http://kuard.local> in your browser, go to the **File System Browser** tab, and navigate to `/secret`. You'll find `user` and `password` present as files, decoded — the kubelet decodes Secret data before writing it to the mounted volume, so the container never has to handle base64 itself.

As with the ConfigMap volume, open a shell in a container to see the actual symlinked structure Kubernetes creates:

```bash
kubectl exec -it deployment/kuard -- ls -al /secret
```

You can change a value without touching the image. Secret values in a manifest or with `kubectl edit` still need to be base64-encoded yourself:

```bash
kubectl patch secret secret-config -p "{\"data\":{\"password\":\"$(echo -n newsecret | base64)\"}}"
```

As with the ConfigMap, mounted Secret files update in place after a short delay — no Pod restart needed.

## Clean up

```bash
kubectl delete -f kuard.yml
```
