/*
 * socket c++
 * Ping ICMP program client.h
 * Plinio Ricardo Gonçalves
 *
 */

#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <chrono>
#include <thread>

class Client {
public:
    Client(const std::string& server_address, int server_port);
    ~Client();

    bool start();
    void disconnect();
    void sendEncryptedPackage(const std::string& message);
    std::string receiveDecryptedPackage();
    bool sendPing();

private:
    int clientSocket;
    std::string serverAddress;
    int serverPort;

    bool sendPingRequest();
    bool receivePingResponse();

    uint16_t in_cksum(uint16_t* addr, int len);
};

#endif
