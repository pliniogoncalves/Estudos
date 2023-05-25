/*
 * socket c++
 * Ping ICMP program client-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "client.h"
#include "client.cpp"

int main() {
    // client object creation
    Client client("127.0.0.1", 12345);

    // server connection
    if (!client.start()) {
        return 1;
    }

    // Send a ping request to the server
    if (!client.sendPing()) {
        std::cout << "Ping request failed.\n";
        return 1;
    }

    // Send an encrypted package
    std::string message = "This is a secret message.";
    client.sendEncryptedPackage(message);

    // Receive the decrypted package
    std::string decryptedMessage = client.receiveDecryptedPackage();
    std::cout << "Received decrypted message: " << decryptedMessage << "\n";

    // Disconnect from the server
    client.disconnect();

    return 0;
}