/*
 * socket c++
 * Ping ICMP program client.cpp
 * Plinio Ricardo Gonçalves
 *
 */
#ifndef ICMPHEADER_H
#define ICMPHEADER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>

class ICMPHeader {
public:
    uint8_t type; // Type
    uint8_t code; // Code
    uint16_t checksum; // Checksum
    uint16_t id; // Identifier
    uint16_t sequence; // Sequence number
};

#endif