//
// Created by plinio on 09/06/23.
//

#include "client.h"
#include "server.h"

int main() {
    std::string serverAddress = "192.168.0.1";  // Server IP address

    // Create and run the client
    Client client(serverAddress);
    client.start();

    // Create and run the server
    Server server;
    server.start();

    return 0;
}
