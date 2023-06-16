//
// Created by plinio on 16/06/23.
//

#include "icmp_receiver.h"

ICMPPacketReceiver::ICMPPacketReceiver() {
    socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socketfd < 0) {
        std::cerr << "Failed to create raw socket." << std::endl;
        return;
    }
}

bool ICMPPacketReceiver::receive() {
    while (true) {
        struct sockaddr_in senderAddress;
        socklen_t senderAddressLength = sizeof(senderAddress);

        int bytesRead = recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&senderAddress, &senderAddressLength);
        if (bytesRead < 0) {
            std::cerr << "Failed to receive ICMP packet." << std::endl;
            return false;
        }

        printPacket(buffer, bytesRead);
    }

    return true;
}

void ICMPPacketReceiver::printPacket(const char* packet, int packetLength) {
    struct ip* ipHeader = (struct ip*)packet;
    int ipHeaderLength = ipHeader->ip_hl * 4;
    struct icmphdr* icmpHeader = (struct icmphdr*)(packet + ipHeaderLength);

    if (icmpHeader->type == ICMP_ECHOREPLY) {
        std::cout << "Received ICMP Echo Reply" << std::endl;
        std::cout << "Source IP: " << inet_ntoa(ipHeader->ip_src) << std::endl;
        std::cout << "Destination IP: " << inet_ntoa(ipHeader->ip_dst) << std::endl;

        // Extract and print payload
        int payloadLength = packetLength - ipHeaderLength - sizeof(struct icmphdr);
        const char* payload = packet + ipHeaderLength + sizeof(struct icmphdr);
        std::cout << "Payload: " << std::string(payload, payloadLength) << std::endl;
    }
}