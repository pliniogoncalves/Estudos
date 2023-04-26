// Arquivo: server.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Creating the socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // any network interface
    server.sin_port = htons(8888); // server port

    // Bind socket to server address
    if (bind(sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // listen from socket
    if (listen(sock, 5) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    // accepting connections
    sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int client_sock = accept(sock, (sockaddr*)&client, &client_len);
    if (client_sock == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }

    // Receiving the message from the client
    char message[1024];
    if (recv(client_sock, message, 1024, 0) == -1) {
        std::cerr << "Error receiving message from client" << std::endl;
        return 1;
    }
    std::cout << "Message received from customer: " << message << std::endl;

    // Sending the response to the client
    std::string response = "Hello, client!";
    if (send(client_sock, response.c_str(), response.size(), 0) == -1) {
        std::cerr << "Error sending response to client" << std::endl;
        return 1;
    }

    // Client and server socket closure
    close(client_sock);
    close(sock);

    return 0;
}
