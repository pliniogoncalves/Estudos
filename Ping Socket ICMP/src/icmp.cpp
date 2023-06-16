//
// Created by plinio on 09/06/23.
//
#include "icmp.h"
ICMP::ICMP() {}

void ICMP::setType(uint8_t type) {
    packet.setType(type);
}

void ICMP::setCode(uint8_t code) {
    packet.setCode(code);
}

void ICMP::setData(const char* data, size_t length) {
    if (length <= packet.ICMP_DATA_SIZE) {
        std::memcpy(packet.data, data, length);
        packet.dataLength = static_cast<uint8_t>(length);
    }
}

void ICMP::calculateChecksum() {
    packet.calculateChecksum();
}