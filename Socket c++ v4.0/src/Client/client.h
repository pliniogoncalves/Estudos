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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>

class Client {
public:
    Client(const std::string& server_address, int server_port);
    ~Client();
    bool Connect();
    bool SendPing();
    bool ReceivePingReply();
    void Close();

private:
    int m_sock;
    std::string m_server_address;
    int m_server_port;
    uint16_t CalculateChecksum(uint16_t* buffer, int size);

};

#endif
