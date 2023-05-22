/*
 * socket c++
 * Ping ICMP program server.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"

Server::Server(int server_port) :
        m_sock(-1),
        m_server_port(server_port)
{

}

Server::~Server()
{
    Stop();
}

void Server::Start()
{
    // Creating the socket
    m_sock = socket(AF_INET,SOCK_STREAM, 0);
    if (m_sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(m_server_port);

    // Binding the socket to the server address
    if (bind(m_sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // Listening for connections
    if (listen(m_sock, 1) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }

    // Accepting connections
    sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int client_sock = accept(m_sock, (sockaddr*)&client, &client_len);
    if (client_sock == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        exit(1);
    }

    std::cout << "Connection established with the client" << std::endl;

    // Receiving and processing ICMP packets
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_len = recv(client_sock, buffer, sizeof(buffer), 0);
        if (recv_len == -1) {
            std::cerr << "Error receiving ICMP packet" << std::endl;
            break;
        }

        // Process the received ICMP packet as needed
        // For example, you can extract the ICMP header and check its type and code

        // Sending a response ICMP packet (if required)

        // For simplicity, we'll exit the loop after receiving the first packet
        break;
    }

    // Closing the client socket
    close(client_sock);
}

void Server::Stop()
{
    // Closing the server socket
    if (m_sock != -1) {
        close(m_sock);
        m_sock = -1;
    }
}
