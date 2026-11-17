# Decisions

## NetworkPolicy demo

- **Three namespaces (`backend`, `frontend`, `other`)**: one allowed and one blocked client make the effect of a policy visible side by side.
- **busybox clients instead of kuard**: busybox has `wget` and is already used in the Job demo.
- **Default deny first, then an allow policy**: teaches the common pattern and that policies are additive.
- **No Ingress in this demo**: a default deny also blocks traffic from the ingress controller, which would distract from the point.
- **Egress as the first challenge**: students discover that DNS to CoreDNS must be allowed explicitly.
- **Same-namespace access as a second challenge**: shows that a default deny also blocks Pods in the policy's own namespace, and practises `podSelector` in `from`. The clients live in `challenge.yml` so the main demo stays focused on namespaces.
