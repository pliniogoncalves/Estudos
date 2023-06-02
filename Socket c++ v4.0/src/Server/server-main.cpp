/*
 * socket c++
 * Ping ICMP program server-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"
#include "server.cpp"

int main() {

    Server server(1234);
    server.start();
    server.stop();

    return 0;
}

