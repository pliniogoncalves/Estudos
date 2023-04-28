/*
 * socket c++
 * Simple chat program server-main.cpp
 * Plinio Ricardo Gonçalves
 *
 */

#include "server.h"
#include "server.cpp"

int main() {
    Server server;
    server.start();
    server.stop();

    return 0;
}

