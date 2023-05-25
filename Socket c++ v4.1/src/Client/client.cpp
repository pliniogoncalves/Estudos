/*
 * socket c++
 * Ping ICMP program client.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "client.h"

Client::Client(const std::string& server_address, int server_port) :
        clientSocket(-1),
        serverAddress(server_address),
        serverPort(server_port)
{

}

Client::~Client()
{
    disconnect();
}

bool Client::start() {
    // Create a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    // Setting the server address
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverAddress.c_str());
    server.sin_port = htons(serverPort);

    // server connection
    if (connect(clientSocket, (sockaddr*)&server, sizeof(server)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        close(clientSocket);
        return false;
    }
    std::cout << "Connected to the server.\n";
    return true;
}


void Client::disconnect() {
    // Disconnect from the server
    if (clientSocket != -1) {
        close(clientSocket);
        clientSocket = -1;
        std::cout << "Disconnected from the server.\n";
    }
}

void Client::sendEncryptedPackage(const std::string& message) {
    // Send the encrypted message to the server
    ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent < 0) {
        std::cout << "Failed to send encrypted package.\n";
    }

    std::cout << "Client sent encrypted message: " << message << "\n";
}

std::string Client::receiveDecryptedPackage() {
    // Receive the decrypted package from the server
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        std::cout << "Failed to receive decrypted package.\n";
        return "";
    }

    std::string decryptedMessage(buffer);
    return decryptedMessage;
}

bool Client::sendPing() {
    if (sendPingRequest()) {
        if (receivePingResponse()) {
            std::cout << "Ping successful!\n";
            return true;
        } else {
            std::cout << "Ping failed: no response received.\n";
            return false;
        }
    } else {
        std::cout << "Ping failed: unable to send ping request.\n";
        return false;
    }
}

bool Client::sendPingRequest() {
    // Create a raw socket for ICMP protocol
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, TP);
    if (socketDescriptor < 0) {
        std::cout << "Failed to create raw socket for ICMP.\n";
        return false;
    }

    // Set destination address
    sockaddr_in destAddress;
    destAddress.sin_family = AF_INET;
    destAddress.sin_addr.s_addr = inet_addr(serverAddress.c_str());

    // Create ICMP Echo Request
    icmp echoRequest;
    echoRequest.icmp_type = ICMP_ECHO;
    echoRequest.icmp_code = 0;
    echoRequest.icmp_id = htons(getpid() & 0xFFFF);
    echoRequest.icmp_seq = htons(1);
    echoRequest.icmp_cksum = 0;
    echoRequest.icmp_cksum = in_cksum(reinterpret_cast<uint16_t*>(&echoRequest), sizeof(icmp));

    // Send the ICMP Echo Request
    ssize_t bytesSent = sendto(socketDescriptor, &echoRequest, sizeof(icmp), 0, reinterpret_cast<sockaddr*>(&destAddress), sizeof(destAddress));
    if (bytesSent <= 0) {
        std::cout << "Failed to send ICMP Echo Request.\n";
        close(socketDescriptor);
        return false;
    }

    close(socketDescriptor);
    return true;
}

bool Client::receivePingResponse() {
    // Create a raw socket for ICMP protocol
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketDescriptor < 0) {
        std::cout << "Failed to create raw socket for ICMP.\n";
        return false;
    }

    // Set timeout for receiving socket data
    timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));

    // Buffer to hold the received packet
    char buffer[IP_MAXPACKET];

    // Receive the ICMP Echo Reply
    ssize_t bytesRead = recv(socketDescriptor, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        close(socketDescriptor);
        return false;
    }

    close(socketDescriptor);
    return true;
}

// Function to calculate the checksum of the ICMP packet
uint16_t Client::in_cksum(uint16_t* addr, int len) {
    int nleft = len;
    uint32_t sum = 0;
    uint16_t* w = addr;
    uint16_t answer = 0;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        *(unsigned char*)(&answer) = *(unsigned char*)w;
        sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;

    return answer;
}

