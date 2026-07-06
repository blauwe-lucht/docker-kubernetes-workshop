# Vagrant VMware Workstation Windows 11 VM

Since my daily machine uses Linux I use this VM to test stuff in Rancher Desktop on Windows.

## Prerequisites

- VMware Workstation Pro (free), needs a Broadcom account.
- Vagrant
- Vagrant reload plugin
- CPU with virtualization support enabled (in BIOS)

## Instructions

1. ```vagrant up --provider vmware_desktop``` (Note: for some reason this didn't work from vscode), the VM will reboot a couple of times, wait Vagrant to be done.
2. Double-click the Rancher Desktop icon, a configuration dialog appear, leave everything at default and press OK.
3. Wait for the installation of Kubernetes to complete, everything is done when the progress bar in the bottom right is gone. When a popup with network access appears, press Allow.
4. Test the installation by opening a PowerShell and entering ```docker version``` or ```kubectl version```.
