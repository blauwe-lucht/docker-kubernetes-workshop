#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "Listening on port 8080" << std::endl;

    std::string body = "<h1>Hello, World from C++!</h1>\n";
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: " +
        std::to_string(body.size()) + "\r\n"
                                      "\r\n" +
        body;

    while (true)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);
        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }
}
