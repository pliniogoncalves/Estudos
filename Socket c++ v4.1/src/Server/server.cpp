/*
 * socket c++
 * Ping ICMP program server.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"

Server::Server(int server_port) :
        m_sock(-1),
        m_server_port(server_port)
{

}

Server::~Server()
{
    Stop();
}

void Server::Start()
{
    // Creating the socket
    m_sock = socket(AF_INET,SOCK_STREAM, 0);
    if (m_sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(m_server_port);

    // Binding the socket to the server address
    if (bind(m_sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // Listening for connections
    if (listen(m_sock, 1) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }

    // Accepting connections
    sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int client_sock = accept(m_sock, (sockaddr*)&client, &client_len);
    if (client_sock == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        exit(1);
    }

    std::cout << "Connection established with the client" << std::endl;

    // Generate AES key and initialization vector (IV)
    const int AES_KEY_SIZE = 16; // 128-bit key size
    uint8_t aesKey[AES_KEY_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];
    RAND_bytes(aesKey, AES_KEY_SIZE);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // Receiving and processing ICMP packets
    const int BUFFER_SIZE = 1024;
    uint8_t buffer[BUFFER_SIZE];

    // Ping loop with termination condition
    int numPings = 0;
    const int MAX_PINGS = 10;  // Maximum number of ICMP ping packets to send
    do {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_len = recv(client_sock, buffer, sizeof(buffer), 0);
        if (recv_len == -1) {
            std::cerr << "Error receiving ICMP packet" << std::endl;
            break;
        }else{
            std::cerr << "receiving ICMP packet: " << recv_len << std::endl;
        }

        // Decrypt the received packet
        std::vector<uint8_t> decrypted = decryptAES(buffer, recv_len, aesKey, iv);
        // Display the decrypted message
        displayDecryptedMessage(decrypted);

        //extract the packet header and payload
        // Sending a response encrypted packet (if required)
        // Here's an example of creating a response packet and encrypting it
        std::vector<uint8_t> responsePayload = {0x01, 0x02, 0x03}; // Example response payload
        std::vector<uint8_t> responsePacket(responsePayload.size());
        std::copy(responsePayload.begin(), responsePayload.end(), responsePacket.begin());

        std::vector<uint8_t> encrypted = encryptAES(responsePacket.data(), responsePacket.size(), aesKey, iv);

        ssize_t sent_len = send(client_sock, encrypted.data(), encrypted.size(), 0);
        if (sent_len == -1) {
            std::cerr << "Error sending packet" << std::endl;
            break;
        }else{
            std::cerr << "sending packet: " << sent_len << std::endl;
        }

        numPings++;

    }while(numPings < MAX_PINGS);

    // Closing the client socket
    close(client_sock);
}

void Server::Stop()
{
    // Closing the server socket
    if (m_sock != -1) {
        close(m_sock);
        m_sock = -1;
    }
}

// AES encryption
std::vector<uint8_t> Server::encryptAES(const uint8_t* plaintext, size_t plaintextLength, const uint8_t* key, const uint8_t* iv)
{
    std::vector<uint8_t> ciphertext(plaintextLength + AES_BLOCK_SIZE); // Allocate space for padding

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext.data(), nullptr, plaintext, plaintextLength);
    int ciphertextLength;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + plaintextLength, &ciphertextLength);
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(plaintextLength + ciphertextLength);

    return ciphertext;
}
// AES decryption
std::vector<uint8_t> Server::decryptAES(const uint8_t* ciphertext, size_t ciphertextLength, const uint8_t* key, const uint8_t* iv)
{
    std::vector<uint8_t> plaintext(ciphertextLength);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv);
    int decryptedLength;
    EVP_DecryptUpdate(ctx, plaintext.data(), &decryptedLength, ciphertext, ciphertextLength);
    int plaintextLength;
    EVP_DecryptFinal_ex(ctx, plaintext.data() + decryptedLength, &plaintextLength);
    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(decryptedLength + plaintextLength);

    return plaintext;
}

void Server::displayDecryptedMessage(const std::vector<uint8_t>& plaintext)
{
    // Convert the vector of uint8_t to a string
    std::string message(plaintext.begin(), plaintext.end());

    // Print the decrypted message
    std::cout << "Decrypted Message: " << message << std::endl;
}

