//
// Created by plinio on 07/06/23.
//

#include "server.h"

#define SERVER_PORT 1234

void Server::start() {
    int serverSocket, clientSocket;
    sockaddr_in serverAddress{}, clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind the address to the socket" << std::endl;
        return;
    }

    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Failed to listen for connections" << std::endl;
        return;
    }

    std::cout << "Server listening on port " << SERVER_PORT << std::endl;

    clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return;
    }

    void generateRandomKey();

    char buffer[1024];
    unsigned char encryptedBuffer[1024];
    // Receive the encrypted ping reply
    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, encryptedBuffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return;
    }

    // Decrypt the ping reply
    unsigned char decryptedBuffer[1024];
    decrypt(encryptedBuffer, decryptedBuffer, strlen(buffer));

    std::cout << "Ping received from client: " << decryptedBuffer << std::endl;

    // Parse the received message
    std::string pingMessage(buffer);
    std::strcpy(buffer, "PONG");

    encrypt(reinterpret_cast<unsigned char*>(buffer), encryptedBuffer, strlen(buffer));

    if (send(clientSocket, encryptedBuffer, strlen(buffer), 0) < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return;
    }

    std::cout << "Ping reply sent to client" << std::endl;

    close(clientSocket);
    close(serverSocket);
}

void Server::encrypt(unsigned char* plaintext, unsigned char* ciphertext, size_t length) {
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(&aesKey), 128, &aesKey);
    AES_cbc_encrypt(plaintext, ciphertext, length, &aesKey, iv, AES_ENCRYPT);
}

void Server::decrypt(unsigned char* ciphertext, unsigned char* plaintext, size_t length) {
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(&aesKey), 128, &aesKey);
    AES_cbc_encrypt(ciphertext, plaintext, length, &aesKey, iv, AES_DECRYPT);
}

void Server::generateRandomKey() {
    if (RAND_bytes(reinterpret_cast<unsigned char*>(&aesKey), sizeof(aesKey)) != 1) {
        std::cerr << "Failed to generate random key" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        std::cerr << "Failed to generate random IV" << std::endl;
        exit(EXIT_FAILURE);
    }
}