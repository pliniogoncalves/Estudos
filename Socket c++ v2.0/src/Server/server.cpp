/*
 * socket c++
 * Simple chat program (server).cpp
 * Plinio Ricardo Gonçalves
 *
 */

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

    std::cout << "waiting for connections..." << std::endl;

    // accepting connections
    sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int client_sock = accept(sock, (sockaddr*)&client, &client_len);
    if (client_sock == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }

    std::cout << "Connection established with the client" << std::endl;

    //chat loop
    std::string message;
    do{
        // receiving message from client
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        if ( recv(client_sock, buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "Error receiving message from client" << std::endl;
            return 1;
        }
        std::cout << "client: " << buffer << std::endl;

        // server message reading
        std::cout << "Enter the message: ";
        std::getline(std::cin, message);

        // sending the message
        if (send(client_sock, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Error sending response to client" << std::endl;
            return 1;
        }

    }while (std::string(message).find("#") == std::string::npos); // continues until the received message contains the '#' character

    // Client and server socket closure
    close(client_sock);
    close(sock);

    return 0;
}
