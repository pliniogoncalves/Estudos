/*
 * socket c++
 * Simple chat program (client).cpp
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
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // server address
    server.sin_port = htons(8888); // server port

    // server connection
    if (connect(sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        return 1;
    }

    // chat loop
    std::string message;
    do{
        // client message reading
        std::cout << "Enter the message: ";
        std::getline(std::cin, message);

        // sending the message
        if (send(sock, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Error sending message" << std::endl;
            return 1;
        }

        // Receipt of reply
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        if (recv(sock, buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "Error receiving reply" << std::endl;
            return 1;
        }
        std::cout << "Server: " << buffer << std::endl;

    }while (message.find("#") == std::string::npos); //continues until the received message contains the '#' character

    // socket closing
    close(sock);

    return 0;
}
