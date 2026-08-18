# Dynamically Provisioned Persistent Volume

Demonstrates dynamic provisioning: a PersistentVolumeClaim references a StorageClass
and Kubernetes automatically creates the PersistentVolume — no manual PV needed.

The `local-path` StorageClass is built into K3s (Rancher Desktop). On a production
cluster, replace `local-path` with your platform's StorageClass (e.g. `rook-ceph-block`
or `longhorn`) — everything else stays the same.

## Apply

`kubectl apply -f kuard.yml`

## Watch the PV get created automatically

`kubectl get pv,pvc`

## Create content

Open a shell on one of the pods and write something to /mnt.

## Open kuard

Visit <http://kuard.local> and use the File System browser under `/mnt` to view file contents.

## Verify persistence across restarts

`kubectl rollout restart deployment/kuard`

Refresh <http://kuard.local> — the file is still there.

## Clean up

`kubectl delete -f kuard.yml`
