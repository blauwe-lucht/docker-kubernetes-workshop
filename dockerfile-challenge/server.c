#include "syscall.h"

#include <asm/socket.h>
#include <linux/in.h>

#define PORT 8080
#define AF_INET 2
#define SOCK_STREAM 1

static const char header[] =
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Content-Encoding: gzip\r\n"
    "Connection: close\r\n"
    "\r\n";

static const char page[] = {
#embed "index.html.gz"
};

static long listen_on(int port) {
    long server = syscall3(__NR_socket, AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    syscall5(__NR_setsockopt, server, SOL_SOCKET, SO_REUSEADDR, (long)&reuse, sizeof reuse);

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = __builtin_bswap16(port),
        .sin_addr.s_addr = INADDR_ANY,
    };
    if (syscall3(__NR_bind, server, (long)&address, sizeof address) < 0 || syscall3(__NR_listen, server, 16, 0) < 0) {
        return -1;
    }
    return server;
}

static void serve_page(long client) {
    char request[1024];
    // Reading the request first prevents close() from sending a TCP reset that can discard the response.
    syscall3(__NR_read, client, (long)request, sizeof request);
    syscall3(__NR_write, client, (long)header, sizeof header - 1);
    syscall3(__NR_write, client, (long)page, sizeof page);
    syscall3(__NR_close, client, 0, 0);
}

ENTRY_POINT void _start(void) {
    long server = listen_on(PORT);
    if (server < 0) {
        syscall3(__NR_exit, 1, 0, 0);
    }
    for (;;) {
        long client = syscall3(__NR_accept, server, 0, 0);
        if (client >= 0) {
            serve_page(client);
        }
    }
}
