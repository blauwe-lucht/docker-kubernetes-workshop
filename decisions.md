# Decisions

## NetworkPolicy demo

- **Three namespaces (`backend`, `frontend`, `other`)**: one allowed and one blocked client make the effect of a policy visible side by side.
- **busybox clients instead of kuard**: busybox has `wget` and is already used in the Job demo.
- **Default deny first, then an allow policy**: teaches the common pattern and that policies are additive.
- **No Ingress in this demo**: a default deny also blocks traffic from the ingress controller, which would distract from the point.
- **Egress as the first challenge**: students discover that DNS to CoreDNS must be allowed explicitly.
- **Same-namespace access as a second challenge**: shows that a default deny also blocks Pods in the policy's own namespace, and practises `podSelector` in `from`. The clients live in `challenge.yml` so the main demo stays focused on namespaces.

## Folder numbering

- **`<section>-NN-<description>`, numbered per section in `README.md` order**: the folder list matches the workshop order, so students find the next exercise at a glance.
- **Number the current order, renumber on insert**: planned demos and reorders get their number when they land; renaming later folders is accepted.
- **`k8s-30-create-helm-chart` right after Helm**: it builds on the Helm demo and is listed in `README.md`.
- **`vagrant-vmware-win11` unnumbered**: it is the author's Windows test VM, not an exercise.

## Horizontal Pod Autoscaler demo

- **Load from kuard's KeyGen workload**: it is built into kuard and started from the browser, so no extra load generator is needed. It runs in one Pod, which also shows that the HPA works on the average over all Pods.
