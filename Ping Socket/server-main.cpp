//
// Created by plinio on 07/06/23.
//

#include "server.h"
#include <iostream>

int main() {
    Server server;

    std::cout << "Server starting..." << std::endl;
    server.start();

    return 0;
}
