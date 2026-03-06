# Dockerfile challenge

Build a Docker image that serves the bingo tracker (`index.html`).

Anything you can think of to reduce the image size is allowed.

## Requirements

- The application must be reachable on port 8080
- The container must run rootless (no root processes inside the container)
- The image must be as small as possible

## Verify

```bash
docker build -t bingo .
docker run --rm -d -p 8080:8080 --name bingo bingo
```

Open <http://localhost:8080> in your browser to verify the bingo tracker loads.

```bash
docker stop bingo
```
