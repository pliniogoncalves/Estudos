//
// Created by plinio on 16/06/23.
//

#include "icmp_packet_receiver.h"

icmp_packet_receiver::icmp_packet_receiver(const std::string& receiverIp):
receiverIp(receiverIp)
{
    socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socketfd < 0) {
        std::cerr << "Failed to create raw socket." << std::endl;
        return;
    }
}

bool icmp_packet_receiver::receive() {
    if (!initializeSocket()) {
        return false;
    }

    while (true) {
        struct sockaddr_in sender;
        socklen_t senderSize = sizeof(sender);

        ssize_t bytesRead = recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sender, &senderSize);
        if (bytesRead <= 0) {
            std::cerr << "Failed to receive ICMP packet." << std::endl;
            return false;
        }

        if (isValidICMPPacket(buffer, bytesRead)) {
            processICMPPacket(buffer, bytesRead);
        }

        processICMPPacket(buffer, bytesRead);
    }

    return true;
}

bool icmp_packet_receiver::initializeSocket() {
    if (socketfd < 0) {
        std::cerr << "Socket not created." << std::endl;
        return false;
    }

    const int enable = 1;
    if (setsockopt(socketfd, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable)) < 0) {
        std::cerr << "Failed to set socket options." << std::endl;
        return false;
    }

    return true;
}

bool icmp_packet_receiver::isValidICMPPacket(const char* packet, ssize_t packetSize) {
    if (packetSize < sizeof(struct icmphdr)) {
        return false;
    }

    struct icmphdr* icmpHeader = (struct icmphdr*)packet;
    if (icmpHeader->type == ICMP_ECHOREPLY) {
        return true;
    }

    return false;
}

void icmp_packet_receiver::processICMPPacket(const char* packet, ssize_t packetSize) {
    struct icmphdr* icmpHeader = (struct icmphdr*)packet;

    // Extract relevant information from the ICMP packet header
    unsigned short id = icmpHeader->un.echo.id;
    unsigned short sequence = icmpHeader->un.echo.sequence;

    // Print received packet information
    std::cout << "Received ICMP Echo Reply packet:" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Sequence: " << sequence << std::endl;

    // Extract and print the payload (if any)
    if (packetSize > sizeof(struct icmphdr)) {
        const char* payload = packet + sizeof(struct icmphdr);
        std::cout << "Payload: " << payload << std::endl;
    }
}
