//
// Created by plinio on 02/06/23.
//
#include <gtest/gtest.h>
#include "client.h"
#include <thread>
#include <chrono>

class ClientTest : public testing::Test {
protected:
    void SetUp() override {
        // Set up the client with a specific server address and port for testing
        client = new Client("127.0.0.1", 12345);
    }

    void TearDown() override {
        // Clean up the client object
        delete client;
    }

    Client* client;
};

TEST_F(ClientTest, StartTest) {
    // Check if the client starts successfully
    EXPECT_TRUE(client->start());
}

TEST_F(ClientTest, SocketCreationTest) {
    // Check if the server socket is created
    ASSERT_EQ(client->getSocket(), -1);
    ASSERT_EQ(client->getServerPort(), 12345);
    ASSERT_EQ(client->getServerAddress(),"127.0.0.1");
}

TEST_F(ClientTest, PingPongTest) {
    // Start the client
    ASSERT_TRUE(client->start());

    // Send a ping from the client
    ASSERT_TRUE(client->sendPing());

    // Wait for a short period of time to allow the server to process the request
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Receive the ping reply
    bool receivedReply = client->receivePingReply();

    // Check if the ping reply was received
    EXPECT_TRUE(receivedReply);

    // Stop the client
    client->stop();
}