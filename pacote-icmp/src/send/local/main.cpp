//
// Created by plinio on 16/06/23.
//

#include "icmp_packet.h"

int main() {
    const char* destinationIp = "127.0.0.1";
    const char* payload = "Hello, ICMP";

    icmp_packet icmpPacket(destinationIp, payload);
    icmpPacket.buildICMPHeader(ICMP_ECHO, 0, 4321, 2);
    icmpPacket.send();

    return 0;
}
