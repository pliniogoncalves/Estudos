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
        client.SendPing();

        // Receiving ICMP reply
        client.ReceivePingReply();

        numPings++;

    } while (numPings < MAX_PINGS);

    // socket closing
    client.Close();

    return 0;
}