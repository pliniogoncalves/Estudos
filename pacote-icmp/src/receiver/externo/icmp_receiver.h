//
// Created by plinio on 16/06/23.
//

#ifndef ICMP_PACKET_RECEIVER_H
#define ICMP_PACKET_RECEIVER_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

class ICMPPacketReceiver {
public:
    ICMPPacketReceiver();
    bool receive();
    void printPacket(const char* packet, int packetLength);

private:
    int socketfd;
    char buffer[IP_MAXPACKET];
};


#endif //ICMP_PACKET_RECEIVER_H
