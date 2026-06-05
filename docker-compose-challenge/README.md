# Docker Compose challenge

Build a multi-container setup with an nginx reverse proxy that routes traffic to two web applications based on the hostname.

## Applications

| Application | Image | Hostname |
|---|---|---|
| Game Collection | `tcgarcao/game-collection` | `game-collection.local` |
| Samtris | `blauwelucht/samtris` | `samtris.local` |

## Requirements

- nginx acts as the reverse proxy and is the **only** container with a published port (port 80).
- `game-collection.local` routes to the Game Collection container.
- `samtris.local` routes to the Samtris container.
- The Game Collection high scores are persisted in a named volume mounted at `/app/highscores`.

## Setup

Add the following entries to your hosts file so your browser resolves the local domains:

**Linux / macOS** — `/etc/hosts`:

```
127.0.0.1 game-collection.local
127.0.0.1 samtris.local
```

**Windows** — `C:\Windows\System32\drivers\etc\hosts`:

```
127.0.0.1 game-collection.local
127.0.0.1 samtris.local
```

## Hints

- Use the provided `nginx.conf` as a starting point. Replace `site1`/`site2` with the actual service names and set the correct ports. Mount the finished config into the nginx container at `/etc/nginx/nginx.conf`.
- The Game Collection container listens on port **80**; Samtris listens on port **8080**.
- Docker Compose service names act as DNS hostnames inside the Compose network, so `proxy_pass http://game-collection:80` works if your service is named `game-collection`.

## Verify

```bash
docker compose up -d
```

Open <http://game-collection.local> and <http://samtris.local> in your browser.

Play a game and score some points, then restart the stack and verify the high scores survived:

```bash
docker compose restart
```

## Clean up

```bash
docker compose down --volumes
```
