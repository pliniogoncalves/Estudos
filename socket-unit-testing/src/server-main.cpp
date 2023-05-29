/*
 * socket c++
 * Ping ICMP program server-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"
#include "server.cpp"

int main() {
    // server object creation
    int server_port = 8888;
    Server server(server_port);

    // server connection
    server.start();

    // socket closing
    server.stop();

    return 0;
}

