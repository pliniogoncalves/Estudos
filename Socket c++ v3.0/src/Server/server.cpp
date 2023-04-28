/*
 * socket c++
 * Simple chat program server.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"

Server::Server() {
    // Creating the socket
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Setting the server address
    m_server.sin_family = AF_INET;
    m_server.sin_addr.s_addr = INADDR_ANY; // any network interface
    m_server.sin_port = htons(8888); // server port

    // Bind socket to server address
    if (bind(m_sock, (sockaddr*)&m_server, sizeof(m_server)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // listen from socket
    if (listen(m_sock, 5) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }
}

Server::~Server() {
    stop();
}

void Server::start() {
    std::cout << "Waiting for connections..." << std::endl;

    // accepting connections
    socklen_t client_len = sizeof(m_client);
    m_client_sock = accept(m_sock, (sockaddr*)&m_client, &client_len);
    if (m_client_sock == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        exit(1);
    }

    std::cout << "Connection established with the client" << std::endl;

    // chat loop
    std::string message;
    do {
        // receiving message from client
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        if (recv(m_client_sock, buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "Error receiving message from client" << std::endl;
            exit(1);
        }
        std::cout << "Client: " << buffer << std::endl;

        // server message reading
        std::cout << "Enter the message: ";
        std::getline(std::cin, message);

        // sending the message
        if (send(m_client_sock, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Error sending response to client" << std::endl;
            exit(1);
        }

    } while (message.find("#") == std::string::npos); // continues until the received message contains the '#' character
}

void Server::stop() {
    // Client and server socket closure
    close(m_client_sock);
    close(m_sock);
}
