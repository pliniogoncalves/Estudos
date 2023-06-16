//
// Created by plinio on 16/06/23.
//

#ifndef ICMP_PACKET_RECEIVER_H
#define ICMP_PACKET_RECEIVER_H

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class icmp_packet_receiver {
public:
    icmp_packet_receiver(const std::string& receiverIp);
    bool receive();

private:
    int socketfd;
    char buffer[IP_MAXPACKET];
    std::string receiverIp;

    bool initializeSocket();
    bool isValidICMPPacket(const char* packet, ssize_t packetSize);
    void processICMPPacket(const char* packet, ssize_t packetSize);
};


#endif //ICMP_PACKET_RECEIVER_H
