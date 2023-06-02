//
// Created by plinio on 02/06/23.
//
#include "client.h"
#include "server.h"

int main() {
    Server server(12345);
    server.start();
    Client client("127.0.0.1", 12345);

    // server connection
    if (!client.start()) {
        return 1;
    }

    // Ping loop with termination condition
    int numPings = 0;
    const int MAX_PINGS = 10;  // Maximum number of ICMP ping packets to send
    // Ping loop
    do{
        // Sending ICMP PING
        if (!client.sendPing()) {
            return 1;
        }

        // Receiving ICMP reply
        bool receivedReply = client.receivePingReply();
        if (receivedReply) {
            std::cout << "Received ICMP reply" << receivedReply << std::endl;
        } else {
            std::cout << "Did not receive ICMP reply" << std::endl;
        }

        numPings++;

    } while (numPings < MAX_PINGS); //continues until the received message contains the '#' character

    // socket closing
    client.stop();
    server.stop();
    return 0;
}