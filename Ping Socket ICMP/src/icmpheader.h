//
// Created by plinio on 09/06/23.
//

#ifndef ICMPHEADER_H
#define ICMPHEADER_H

#include <cstdint>

class ICMPHeader {
public:
    ICMPHeader();
    void setType(uint8_t type);
    void setCode(uint8_t code);
    void setData(uint32_t data);
    uint8_t getType() const;
    uint8_t getCode() const;
    uint32_t getData() const;
    void calculateChecksum();

private:
    uint16_t calculateChecksum(uint16_t *data, int length);

private:
    uint8_t type;         // ICMP message type
    uint8_t code;         // ICMP message code
    uint16_t checksum;    // ICMP checksum
    uint32_t data;        // Data for ICMP message content (here, using a 32-bit integer)

private:
    static constexpr int ICMP_DATA_SIZE = 32;
};

#endif // ICMPHEADER_H
