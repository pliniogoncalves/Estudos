// Arquivo: client.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // socket creation
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // server address
    server.sin_port = htons(8888); // server port

    // server connection
    if (connect(sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        return 1;
    }

    // sending the message
    std::string message = "Hello, server!";
    if (send(sock, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Error sending message" << std::endl;
        return 1;
    }

    // Receipt of reply
    char response[1024];
    if (recv(sock, response, 1024, 0) == -1) {
        std::cerr << "Error receiving reply" << std::endl;
        return 1;
    }
    std::cout << "Server response: " << response << std::endl;

    // socket closing
    close(sock);

    return 0;
}
