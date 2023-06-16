//
// Created by plinio on 09/06/23.
//

#include "icmpheader.h"

ICMPHeader::ICMPHeader() {}

void ICMPHeader::setType(uint8_t type) {
    this->type = type;
}

void ICMPHeader::setCode(uint8_t code) {
    this->code = code;
}

void ICMPHeader::setData(uint32_t data) {
    this->data = data;
}

void ICMPHeader::calculateChecksum() {
    checksum = 0;
    checksum = calculateChecksum(reinterpret_cast<uint16_t *>(this), sizeof(ICMPHeader));
}

uint8_t ICMPHeader::getType() const {
    return type;
}

uint8_t ICMPHeader::getCode() const {
    return code;
}

uint32_t ICMPHeader::getData() const {
    return data;
}

uint16_t ICMPHeader::calculateChecksum(uint16_t *data, int length) {
    uint32_t sum = 0;
    while (length > 1) {
        sum += *data++;
        length -= 2;
    }
    if (length == 1) {
        sum += *(reinterpret_cast<uint8_t *>(data));
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return static_cast<uint16_t>(~sum);
}