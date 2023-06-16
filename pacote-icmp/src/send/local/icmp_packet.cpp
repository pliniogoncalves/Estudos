//
// Created by plinio on 16/06/23.
//

#include "icmp_packet.h"

icmp_packet::icmp_packet(const char* destinationIp, const char* payload) {
    socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socketfd < 0) {
        std::cerr << "Failed to create raw socket." << std::endl;
        return;
    }

    memset(packet, 0, sizeof(packet));
    icmpHeader = (struct icmphdr*)packet;

    strncpy(packet + sizeof(struct icmphdr), payload, sizeof(packet) - sizeof(struct icmphdr));

    memset(&destination, 0, sizeof(destination));
    destination.sin_family = AF_INET;
    if (inet_pton(AF_INET, destinationIp, &(destination.sin_addr)) <= 0) {
        std::cerr << "Invalid IP address." << std::endl;
        return;
    }
}

bool icmp_packet::send() {
    if (socketfd < 0) {
        std::cerr << "Socket not created." << std::endl;
        return false;
    }

    int packetLength = sizeof(struct icmphdr) + strlen(packet + sizeof(struct icmphdr));

    // Calculate and set the ICMP checksum
    icmpHeader->checksum = 0;
    icmpHeader->checksum = calculateChecksum(packet, packetLength);

    // Send the packet
    int bytesSent = sendto(socketfd, packet, packetLength, 0, (struct sockaddr*)&destination, sizeof(destination));
    if (bytesSent <= 0) {
        std::cerr << "Failed to send ICMP packet." << std::endl;
        return false;
    }

    std::cout << "ICMP packet sent successfully." << std::endl;

    return true;
}

void icmp_packet::buildICMPHeader(uint8_t type, uint8_t code, uint16_t id, uint16_t sequence) {
    icmpHeader->type = type; // Echo request
    icmpHeader->code = code;
    icmpHeader->un.echo.id = id; // Customize if desired
    icmpHeader->un.echo.sequence = sequence; // Customize if desired
}

unsigned short icmp_packet::calculateChecksum(const void* buffer, int size) {
    unsigned int checksum = 0;
    unsigned short* ptr = (unsigned short*)buffer;
    int numShorts = size / 2;

    while (numShorts-- > 0) {
        checksum += *ptr++;
    }

    if (size % 2) {
        checksum += *(unsigned char*)ptr;
    }

    checksum = (checksum >> 16) + (checksum & 0xffff);
    checksum += (checksum >> 16);

    return ~checksum;
}

/*
 *
  TYPE (8 bits): identifica o tipo mensagem, por exemplo, se o valor for 8 é uma requisição (echo request). Se o conteúdo for 0 é uma reposta (echo reply).
  CODE (8 bits): utilizado em conjunto com o campo TYPE para identificar o tipo de mensagem ICMP que está sendo enviada.
  CHECKSUM (16 bits): verifica a integridade do pacote ICMP.
  MESSAGE CONTENTS (Tamanho Variável): contém o conteúdo da mensagem ICMP.
 *
 */

