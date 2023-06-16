//
// Created by plinio on 09/06/23.
//

#ifndef CLIENT_H
#define CLIENT_H

#include "icmp.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    Client(const std::string& serverAddress);
    void start();

private:
    std::string serverAddress;
};


#endif //CLIENT_H
