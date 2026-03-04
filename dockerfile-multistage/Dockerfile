# Build stage
FROM almalinux:9 AS builder

RUN dnf install -y gcc-c++ && dnf clean all

WORKDIR /app
COPY main.cpp .
RUN g++ -o server main.cpp

# Final stage
FROM almalinux:9-minimal

COPY --from=builder /app/server /server

EXPOSE 8080
CMD ["/server"]
