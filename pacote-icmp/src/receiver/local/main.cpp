//
// Created by plinio on 16/06/23.
//


#include "icmp_packet_receiver.h"

int main() {
    const std::string receiverIp = "127.0.0.1";

    icmp_packet_receiver receiver(receiverIp);
    receiver.receive();

    return 0;
}
