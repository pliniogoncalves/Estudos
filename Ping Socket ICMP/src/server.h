//
// Created by plinio on 09/06/23.
//

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include "icmp.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server {
public:
    Server();
    void start();
};


#endif //SERVER_H
