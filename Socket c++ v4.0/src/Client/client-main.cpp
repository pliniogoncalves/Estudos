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
    Client client("127.0.0.1", 8888);

    // server connection
    if (!client.Connect()) {
        return 1;
    }

    // Ping loop with termination condition
    int numPings = 0;
    const int MAX_PINGS = 10;  // Maximum number of ICMP ping packets to send
    // Ping loop
    do{
        // Sending ICMP PING
        if (!client.SendPing()) {
            return 1;
        }

        // Receiving ICMP reply
        bool receivedReply = client.ReceivePingReply();
        if (receivedReply) {
            std::cout << "Received ICMP reply" << std::endl;
        } else {
            std::cout << "Did not receive ICMP reply" << std::endl;
        }

        numPings++;

    } while (numPings < MAX_PINGS); //continues until the received message contains the '#' character

    // socket closing
    client.Close();

    return 0;
}