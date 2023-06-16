//
// Created by plinio on 09/06/23.
//

#ifndef ICMP_H
#define ICMP_H

#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "icmpheader.h"

class ICMP {
public:
    ICMP();

    void setType(uint8_t type);
    void setCode(uint8_t code);
    void setData(const char* data, size_t length);
    void calculateChecksum();

private:
    ICMPHeader packet;
};


#endif //ICMP_H
