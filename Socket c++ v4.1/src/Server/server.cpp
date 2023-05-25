/*
 * socket c++
 * Ping ICMP program server.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"

Server::Server(int server_port) :
        serverSocket(-1),
        clientSocket(-1),
        serverPort(server_port),
        isRunning_(false)
{

}

Server::~Server(){
    stop();
}

void Server::start() {
    if (!bindAndListen()) {
        exit(1);
    }

    isRunning_ = true;
    std::cout << "Server started and listening on port " << serverPort << ".\n";

}

void Server::stop() {
    // Closing the server socket
    if (isRunning_) {
        close(serverSocket);
        isRunning_ = false;
        std::cout << "Server stopped.\n";
    }
}

void Server::acceptClient() {

    // Accept a client connection
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    clientSocket = accept(serverSocket, (sockaddr * ) & clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        exit(1);
    }

    std::cout << "Connection established with the client" << std::endl;
}

void Server::disconnectClient() {
    // Disconnect the client
    close(clientSocket);
    std::cout << "Client disconnected from server.\n";
}

std::string Server::receiveEncryptedPackage() {
    std::string encryptedPackage = receivePackage();
    if (!encryptedPackage.empty()) {
        std::cout << "Server received encrypted package: " << encryptedPackage << "\n";
    }

    return encryptedPackage;
}

void Server::sendDecryptedPackage() {
    std::string decryptedMessage = decryptPackage();
    // Send the decrypted package back to the client
    ssize_t bytesSent = send(clientSocket, decryptedMessage.c_str(), decryptedMessage.size(), 0);
    if (bytesSent < 0) {
        std::cout << "Failed to send decrypted package.\n";
    }

    std::cout << "Server sent decrypted message: " << decryptedMessage << "\n";
}

void Server::handlePingRequest() {
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    char buffer[IP_MAXPACKET];
    ssize_t bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
    if (bytesRead <= 0) {
        std::cout << "Failed to receive ping request.\n";
        exit(1);
    }


    std::cout << "Received ping request from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << ".\n";

    // Construct ICMP Echo Reply packet
    icmp* echoReply = reinterpret_cast<icmp*>(buffer);
    echoReply->icmp_type = ICMP_ECHOREPLY;
    echoReply->icmp_cksum = 0;
    echoReply->icmp_cksum = in_cksum(reinterpret_cast<uint16_t*>(echoReply), bytesRead);

    // Send the ICMP Echo Reply packet back to the client
    ssize_t bytesSent = sendto(serverSocket, buffer, bytesRead, 0, reinterpret_cast<sockaddr*>(&clientAddress), sizeof(clientAddress));
    if (bytesSent <= 0) {
        std::cout << "Failed to send ping response.\n";
        return;
    }

    std::cout << "Sent ping response to " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << ".\n";
}

bool Server::bindAndListen(){
    // Create a socket for the server
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Setting the server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(serverPort);

    // Binding the socket to the server address
    if (bind(serverSocket, (sockaddr * ) & serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // Listening for connections
    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }

    std::cout << "Server started " << serverPort << "\n";

    return true;
}

std::string Server::receivePackage() {
    // Receive the encrypted package from the client
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    ssize_t recv_len = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recv_len == -1) {
        std::cerr << "Error receiving encrypted packet" << std::endl;
        exit(1);
    }

    std::string encryptedPackage(buffer);
    return encryptedPackage;
}

std::string Server::decryptPackage() {
    // Decrypt the package
    std::string decrypted = receivePackage() + " [decrypted]";
    return decrypted;
}

// Function to calculate the checksum of the ICMP packet
uint16_t Server::in_cksum(uint16_t* addr, int len) {
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



