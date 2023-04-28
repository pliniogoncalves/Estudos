/*
 * socket c++
 * Simple chat program client.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "client.h"

Client::Client(const std::string& server_address, int server_port) :
        sock_(-1),
        server_address_(server_address),
        server_port_(server_port)
{}

bool Client::Connect() {
    // Creating the socket
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_address_.c_str());
    server.sin_port = htons(server_port_);

    // server connection
    if (connect(sock_, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        return false;
    }
    return true;
}

bool Client::SendMessage(const std::string& message) {
    // sending the message
    if (send(sock_, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Error sending message" << std::endl;
        return false;
    }
    return true;
}

std::string Client::ReceiveMessage() {
    // Receipt of reply
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    if (recv(sock_, buffer, sizeof(buffer), 0) == -1) {
        std::cerr << "Error receiving reply" << std::endl;
        return "";
    }
    return buffer;
}

void Client::Close() {
    // socket closing
    close(sock_);
}
