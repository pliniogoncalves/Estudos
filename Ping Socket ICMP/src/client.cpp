//
// Created by plinio on 09/06/23.
//

#include "client.h"

Client::Client(const std::string& serverAddress) :
serverAddress(serverAddress)
{

}

void Client::start() {
    // Create a raw socket
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return;
    }

    std::cout << "Ping started." << std::endl;

    // Manually enter ICMP values
    uint8_t type, code;
    uint32_t data;

    std::cout << "Enter ICMP type: ";
    std::cin >> type;

    std::cout << "Enter ICMP code: ";
    std::cin >> code;

    std::cout << "Enter ICMP data: ";
    std::cin >> data;

    // Create an instance of the ICMP class
    ICMP icmp;
    icmp.setType(type);
    icmp.setCode(code);
    icmp.setData(data.c_str(), data.length());
    icmp.calculateChecksum();

    // Destination IP address
    struct sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    inet_pton(AF_INET, serverAddress.c_str(), &(destAddr.sin_addr));

    // Send the ICMP packet
    int bytesSent = sendto(sockfd, &icmp, sizeof(ICMP), 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
    if (bytesSent < 0) {
        std::cerr << "Failed to send packet." << std::endl;
        close(sockfd);
        return;
    }

    std::cout << "ICMP packet sent successfully." << std::endl;

    // Close the socket
    close(sockfd);
}


