/*
 * socket c++
 * Ping ICMP program server-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"
#include "server.cpp"

int main() {
    int server_port = 8888;
    Server server(server_port);
    server.Start();
    server.Stop();

    return 0;
}

