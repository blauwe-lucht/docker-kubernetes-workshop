FROM alpine:3.23 AS builder
RUN apk add --no-cache gcc linux-headers minify
WORKDIR /src
COPY server.c syscall.h index.html ./
RUN minify index.html | gzip -9n > index.html.gz
# Without libc there is no startup code, stack protector runtime or need for unwind tables; -n drops page alignment padding.
RUN gcc -std=c23 -Os -s -static -nostdlib -fno-pie -no-pie \
        -fno-stack-protector -fno-asynchronous-unwind-tables -fno-ident \
        -Wl,--build-id=none -Wl,-n \
        -o server server.c

FROM scratch
COPY --from=builder /src/server /server
USER 65534:65534
EXPOSE 8080
ENTRYPOINT ["/server"]
