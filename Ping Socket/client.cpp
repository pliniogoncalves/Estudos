//
// Created by plinio on 07/06/23.
//

#include "client.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234

void Client::connectToServer() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return;
    }

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return;
    }

    char buffer[1024];

    generateRandomKey();
    // Encrypt the ping request before sending
    unsigned char encryptedBuffer[1024];
    encrypt(reinterpret_cast<unsigned char*>(buffer), encryptedBuffer, strlen(buffer));

    //std::strcpy(buffer, "PING");

    //std::cout << "Ping sent to server: " << buffer << std::endl;

    auto start = std::chrono::steady_clock::now();

    if (send(clientSocket, encryptedBuffer, strlen(buffer), 0) < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return;
    }

    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, encryptedBuffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return;
    }

    // Decrypt the ping reply
    unsigned char decryptedBuffer[1024];
    decrypt(encryptedBuffer, decryptedBuffer, strlen(buffer));

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Ping reply received from server: " << decryptedBuffer << std::endl;
    std::cout << "Round-trip time: " << duration << " ms" << std::endl;

    // Execute the ping command to capture TTL
    std::string pingCommand = "ping -c 1 " + std::string(SERVER_IP);
    std::array<char, 128> pingBuffer;
    std::string pingResult;

    // Open a pipe to execute the ping command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(pingCommand.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Failed to open pipe" << std::endl;
        return;
    }

    // Read the output of the ping command
    while (fgets(pingBuffer.data(), static_cast<int>(pingBuffer.size()), pipe.get()) != nullptr) {
        pingResult += pingBuffer.data();
    }

    std::cout << "Ping output: " << pingResult;

    // Parse the TTL value from the ping output
    size_t ttlPos = pingResult.find("ttl=");
    if (ttlPos != std::string::npos) {
        std::string ttl = pingResult.substr(ttlPos + 4);
        std::cout << "TTL: " << ttl;
    }

    // Parse the icmp_seq value from the ping output
    size_t icmpSeqPos = pingResult.find("icmp_seq=");
    if (icmpSeqPos != std::string::npos) {
        size_t icmpSeqEndPos = pingResult.find(" ", icmpSeqPos);
        if (icmpSeqEndPos != std::string::npos) {
            std::string icmpSeq = pingResult.substr(icmpSeqPos + 10, icmpSeqEndPos - icmpSeqPos - 10);
            std::cout << "icmp_seq: " << icmpSeq;
        }
    }

    close(clientSocket);
}

void Client::generateRandomKey() {
    if (RAND_bytes(reinterpret_cast<unsigned char*>(&aesKey), sizeof(aesKey)) != 1) {
        std::cerr << "Failed to generate random key" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        std::cerr << "Failed to generate random IV" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Client::encrypt(unsigned char* plaintext, unsigned char* ciphertext, size_t length) {
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(&aesKey), 128, &aesKey);
    AES_cbc_encrypt(plaintext, ciphertext, length, &aesKey, iv, AES_ENCRYPT);
}

void Client::decrypt(unsigned char* ciphertext, unsigned char* plaintext, size_t length) {
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(&aesKey), 128, &aesKey);
    AES_cbc_encrypt(ciphertext, plaintext, length, &aesKey, iv, AES_DECRYPT);
}