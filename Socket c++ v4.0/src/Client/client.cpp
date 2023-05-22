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

bool Client::SendPing()
{
    // Creating the ICMP packet
    const int PACKET_SIZE = 64; // Set the packet size as needed
    char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

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

    // Sending the ICMP packet
    if (send(m_sock, packet, PACKET_SIZE, 0) == -1) {
        std::cerr << "Error sending ICMP packet" << std::endl;
        return false;
    }

    return true;
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


bool Client::ReceivePingReply() {
    // Receiving the ICMP reply
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    if (recv(m_sock, buffer, sizeof(buffer), 0) == -1) {
        std::cerr << "Error receiving ICMP reply" << std::endl;
        return false;
    }

    // Extracting the ICMP header
    bool isReply = false;
    if (buffer[20] == 0x00 && buffer[21] == 0x00) {
        // ICMP type (echo reply) and code (echo reply)
        isReply = true;
    }

    return isReply;
}

