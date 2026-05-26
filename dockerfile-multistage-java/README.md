# Multi-stage Dockerfile (Java)

Demonstrates a multi-stage build: a full Maven+JDK image compiles the JAR, and only
the JAR is copied to a minimal JRE image.

- **Build stage**: `maven:3.9-eclipse-temurin-21` — full JDK with Maven to compile and package.
- **Final stage**: `eclipse-temurin:21-jre-alpine` — no compiler, no Maven, just the JRE.

## Build naive image

`docker build -t naive-java -f Dockerfile.naive .`

## Run naive image

`docker run --rm -d --name naive-java -p 8080:8080 naive-java`

## Build smart multistage image

`docker build -t multistage-java .`

## Run multistage image

`docker run --rm -d --name multistage-java -p 8081:8080 multistage-java`

Then visit <http://localhost:8081>.

## Check size difference

`docker image ls naive-java`
`docker image ls multistage-java`

## Clean up

`docker stop naive-java`
`docker stop multistage-java`
`docker rmi naive-java`
`docker rmi multistage-java`
