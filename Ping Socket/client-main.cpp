//
// Created by plinio on 07/06/23.
//
#include "client.h"
#include <iostream>

int main() {
    Client client;

    std::cout << "Client connecting to server..." << std::endl;
    client.connectToServer();

    return 0;
}
