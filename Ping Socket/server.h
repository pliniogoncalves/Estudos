//
// Created by plinio on 07/06/23.
//

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/rand.h>

class Server {
public:
    void generateRandomKey();
    void start();
    void encrypt(unsigned char* plaintext, unsigned char* ciphertext, size_t length);
    void decrypt(unsigned char* ciphertext, unsigned char* plaintext, size_t length);

private:
    AES_KEY aesKey;
    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];
};

#endif  // SERVER_H

