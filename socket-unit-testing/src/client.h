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
#include <cstdint>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

class Client {
public:
    Client(const std::string& server_address, int server_port);
    ~Client();
    bool start();
    void sendPing();
    void receivePingReply();
    void stop();
    void displayDecryptedMessage(const std::vector<uint8_t>& plaintext);

private:
    int m_sock;
    std::string m_server_address;
    int m_server_port;
    uint16_t calculateChecksum(uint16_t* buffer, int size);

    std::vector<uint8_t> encryptAES(const uint8_t* plaintext, size_t plaintextLength, const uint8_t* key, const uint8_t* iv);
    std::vector<uint8_t> decryptAES(const uint8_t* ciphertext, size_t ciphertextLength, const uint8_t* key, const uint8_t* iv);

};

#endif
