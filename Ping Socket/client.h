//
// Created by plinio on 07/06/23.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <openssl/aes.h>
#include <openssl/rand.h>

class Client {
public:
    void connectToServer();
    void generateRandomKey();
    void encrypt(unsigned char* plaintext, unsigned char* ciphertext, size_t length);
    void decrypt(unsigned char* ciphertext, unsigned char* plaintext, size_t length);

private:
    AES_KEY aesKey;
    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];
};

#endif  // CLIENT_H

