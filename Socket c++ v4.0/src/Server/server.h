/*
 * socket c++
 * Ping ICMP program server.h
 * Plinio Ricardo Gonçalves
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>

class Server {
public:
    Server(int server_port);
    ~Server();

    void start();
    void stop();

private:
    int m_sock;
    int m_server_port;
};

#endif