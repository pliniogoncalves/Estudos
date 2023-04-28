/*
 * socket c++
 * Simple chat program client.h
 * Plinio Ricardo Gonçalves
 *
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    Client(const std::string& server_address, int server_port);
    bool Connect();
    bool SendMessage(const std::string& message);
    std::string ReceiveMessage();
    void Close();
private:
    int sock_;
    std::string server_address_;
    int server_port_;
};

#endif
