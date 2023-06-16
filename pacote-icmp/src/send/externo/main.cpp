//
// Created by plinio on 16/06/23.
//

#include "icmp_packet.h"

int main() {
    const char* destinationIp = "172.217.19.206";
    const char* payload = "Hello, Google!";

    icmp_packet icmpPacket(destinationIp, payload);
    icmpPacket.buildICMPHeader(ICMP_ECHO, 0, 4321, 2);
    icmpPacket.send();

    return 0;
}
