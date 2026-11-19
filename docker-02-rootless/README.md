# Rootless Dockerfile

Demonstrates running a container as a non-root user using the
[`nginxinc/nginx-unprivileged`](https://hub.docker.com/r/nginxinc/nginx-unprivileged) base image,
which runs nginx without root privileges.

## Build

`docker build -t rootless .`

## Run

`docker run --rm -d --name rootless -p 8080:8080 -v /:/host rootless`
`docker exec -it rootless /bin/sh`

Then inside the shell inside the container:

`whoami`
`ls /host/root`

## Clean up

`docker stop rootless`
`docker rmi rootless`
