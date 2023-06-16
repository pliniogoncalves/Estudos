//
// Created by plinio on 16/06/23.
//

#ifndef ICMP_PACKET_H
#define ICMP_PACKET_H

#include <netinet/ip_icmp.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class icmp_packet {
public:
    icmp_packet(const char* destinationIp, const char* payload);
    bool send();

private:
    int socketfd;
    char packet[64];
    struct icmphdr* icmpHeader;
    struct sockaddr_in destination;

    void buildICMPHeader();
    unsigned short calculateChecksum(const void* buffer, int size);
};


#endif //ICMP_PACKET_H
