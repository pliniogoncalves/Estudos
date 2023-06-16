//
// Created by plinio on 09/06/23.
//

#include "server.h"

Server::Server() {}

void Server::start() {
    // Create a raw socket
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return;
    }

    std::cout << "Server is listening for ICMP packets." << std::endl;

   // while (true) {
        // Buffer to receive the ICMP packet
        char buffer[4096];
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        // Receive ICMP packet
        ssize_t bytesRead = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (bytesRead < 0) {
            std::cerr << "Failed to receive packet." << std::endl;
            close(sockfd);
            return;
        }

        std::cout << "Received ICMP packet from client: " << inet_ntoa(clientAddr.sin_addr) << std::endl;

        // Process the received ICMP packet
        // You can access the ICMP header and message contents using the buffer

        // For example, assuming the buffer contains only the ICMP packet without any IP headers:
        if (bytesRead >= sizeof(ICMPHeader)) {
            ICMPHeader* icmpHeader = reinterpret_cast<ICMPHeader*>(buffer);
            std::cout << "ICMP Type: " << static_cast<uint8_t>(icmpHeader->getType()) << std::endl;
            std::cout << "ICMP Code: " << static_cast<uint8_t>(icmpHeader->getCode()) << std::endl;
            std::cout << "ICMP Data: " << icmpHeader->getData() << std::endl;
            // ...
        }
    //}

    // Close the socket
    close(sockfd);
}