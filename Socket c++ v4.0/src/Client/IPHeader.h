/*
 * socket c++
 * Ping ICMP program client.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#ifndef IPHEADER_H
#define IPHEADER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>

class IPHeader {
public:
    uint8_t ip_hl : 4; // Header length (5 * 4 bytes = 20 bytes)
    uint8_t ip_v : 4; // IPv4
    uint8_t ip_tos; // Kind of service
    uint16_t ip_len; // Total length
    uint16_t ip_id; // Identification
    uint16_t ip_off; // Fragment offset
    uint8_t ip_ttl; // Time to live
    uint8_t ip_p; // Protocol
    uint16_t ip_sum; // Checksum
    uint32_t ip_src; // Source IP address
    uint32_t ip_dst; // Destination IP address
};



#endif
