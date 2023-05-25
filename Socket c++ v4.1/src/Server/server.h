/*
 * socket c++
 * Ping ICMP program server.h
 * Plinio Ricardo Gonçalves
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
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
    void acceptClient();
    void disconnectClient();
    std::string receiveEncryptedPackage();
    void sendDecryptedPackage();
    void handlePingRequest();


private:
    int serverSocket;
    int clientSocket;
    int serverPort;
    bool isRunning_;

    bool bindAndListen();
    std::string receivePackage();
    std::string decryptPackage();
    uint16_t in_cksum(uint16_t* addr, int len);
};

#endif