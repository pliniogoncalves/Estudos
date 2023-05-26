/*
 * socket c++
 * Ping ICMP program client.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "client.h"
#include "ICMPHeader.h"
#include "IPHeader.h"

Client::Client(const std::string& server_address, int server_port) :
        m_sock(-1),
        m_server_address(server_address),
        m_server_port(server_port)
{

}

Client::~Client()
{
    Close();
}

bool Client::Connect() {
    // Creating the socket
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(m_server_address.c_str());
    server.sin_port = htons(m_server_port);

    // server connection
    if (connect(m_sock, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        return false;
    }
    return true;
}

void Client::SendPing()
{
    // Creating the ICMP packet
    const int PACKET_SIZE = 64; // Set the packet size as needed
    char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

    // Generate AES key and initialization vector (IV)
    const int AES_KEY_SIZE = 16; // 128-bit key size
    uint8_t aesKey[AES_KEY_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];
    RAND_bytes(aesKey, AES_KEY_SIZE);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // IP header
    IPHeader* ip_header = reinterpret_cast<IPHeader*>(packet);
    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(PACKET_SIZE);
    ip_header->ip_id = htons(0);
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_p = IPPROTO_ICMP;
    ip_header->ip_sum = 0;
    ip_header->ip_src = 0;
    ip_header->ip_dst = inet_addr(m_server_address.c_str());

    // ICMP header
    ICMPHeader* icmp_header = reinterpret_cast<ICMPHeader*>(packet + sizeof(IPHeader));
    icmp_header->type = ICMP_ECHO;
    icmp_header->code = 0;
    icmp_header->checksum = 0;
    icmp_header->id = 0;
    icmp_header->sequence = 0;

    // Calculate ICMP checksum
    icmp_header->checksum = CalculateChecksum(reinterpret_cast<uint16_t*>(icmp_header), sizeof(ICMPHeader));

    // Send encrypted packet to the server
    std::vector<uint8_t> plaintext = {0x01, 0x02, 0x03}; // Example plaintext
    std::vector<uint8_t> encrypted = encryptAES(plaintext.data(), plaintext.size(), aesKey, iv);

    ssize_t sent_len = send(m_sock, encrypted.data(), encrypted.size(), 0);
    if (sent_len == -1) {
        std::cerr << "Error sending packet" << std::endl;
        exit(1);
    } else{
        std::cerr << "Sending packet: " << sent_len << std::endl;
    }

}


void Client::Close() {
    if (m_sock != -1) {
        close(m_sock);
        m_sock = -1;
    }
}

uint16_t Client::CalculateChecksum(uint16_t* buffer, int size) {
    unsigned long checksum = 0;
    while (size > 1) {
        checksum += *buffer++;
        size -= sizeof(uint16_t);
    }
    if (size) {
        checksum += *(reinterpret_cast<uint8_t*>(buffer));
    }
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum += (checksum >> 16);
    return static_cast<uint16_t>(~checksum);
}

void Client::ReceivePingReply() {
    // Generate AES key and initialization vector (IV)
    const int AES_KEY_SIZE = 16; // 128-bit key size
    uint8_t aesKey[AES_KEY_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];
    RAND_bytes(aesKey, AES_KEY_SIZE);
    RAND_bytes(iv, AES_BLOCK_SIZE);

    // Receiving the ICMP reply
    const int BUFFER_SIZE = 1024;
    uint8_t buffer[BUFFER_SIZE];
    ssize_t recv_len = recv(m_sock, buffer, sizeof(buffer), 0);
    if (recv_len == -1) {
        std::cerr << "Error receiving packet" << std::endl;
        exit(1);
    }

    std::vector<uint8_t> decrypted = decryptAES(buffer, recv_len, aesKey, iv);
    // Display the decrypted message
    displayDecryptedMessage(decrypted);

}

// AES encryption
std::vector<uint8_t> Client::encryptAES(const uint8_t* plaintext, size_t plaintextLength, const uint8_t* key, const uint8_t* iv)
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
std::vector<uint8_t> Client::decryptAES(const uint8_t* ciphertext, size_t ciphertextLength, const uint8_t* key, const uint8_t* iv)
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

void Client::displayDecryptedMessage(const std::vector<uint8_t>& plaintext)
{
    // Convert the vector of uint8_t to a string
    std::string message(plaintext.begin(), plaintext.end());

    // Print the decrypted message
    std::cout << "Receiver Decrypted Message: " << message << std::endl;
}
