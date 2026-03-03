# Simple Dockerfile

## Build

`docker build -t modified-nginx .`

## Run

`docker run --rm --name modified-nginx -d -p 8080:80 modified-nginx`

## Clean up

`docker stop modified-nginx`
