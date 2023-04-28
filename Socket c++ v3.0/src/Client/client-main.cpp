/*
 * socket c++
 * Simple chat program client-main.cpp
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

    // chat loop
    std::string message;
    do{
        // client message reading
        std::cout << "Enter the message: ";
        std::getline(std::cin, message);

        // sending the message
        if (!client.SendMessage(message)) {
            return 1;
        }

        // Receipt of reply
        std::string reply = client.ReceiveMessage();
        if (reply.empty()) {
            return 1;
        }
        std::cout << "Server: " << reply << std::endl;

    } while (message.find("#") == std::string::npos); //continues until the received message contains the '#' character

    // socket closing
    client.Close();

    return 0;
}