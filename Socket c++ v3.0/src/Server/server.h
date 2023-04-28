/*
 * socket c++
 * Simple chat program server.h
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

class Server {
public:
    Server();
    ~Server();

    void start();
    void stop();

private:
    int m_sock;
    int m_client_sock;
    sockaddr_in m_server;
    sockaddr_in m_client;
};

#endif