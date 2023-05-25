/*
 * socket c++
 * Ping ICMP program server-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"
#include "server.cpp"

int main() {
    // Create a server object
    Server server(12345);

    // Start the server
    server.start();

    // Accept a client connection
    server.acceptClient();

    // Handle the ping request from the client
    server.handlePingRequest();

    // Receive the encrypted package
    std::string encryptedMessage = server.receiveEncryptedPackage();
    std::cout << "Received encrypted message: " << encryptedMessage << "\n";

    // Send the decrypted package back to the client
    server.sendDecryptedPackage();

    // Disconnect the client
    server.disconnectClient();

    // Stop the server
    server.stop();

    return 0;
}

