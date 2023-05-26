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
#include <vector>
#include <cstdint>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

class Server {
public:
    Server(int server_port);
    ~Server();

    void Start();
    void Stop();

    void displayDecryptedMessage(const std::vector<uint8_t>& plaintext);

private:
    int m_sock;
    int m_server_port;

    std::vector<uint8_t> encryptAES(const uint8_t* plaintext, size_t plaintextLength, const uint8_t* key, const uint8_t* iv);
    std::vector<uint8_t> decryptAES(const uint8_t* ciphertext, size_t ciphertextLength, const uint8_t* key, const uint8_t* iv);
};

#endif