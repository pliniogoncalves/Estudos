//
// Created by plinio on 02/06/23.
//
#include <gtest/gtest.h>
#include "server.h"

class ServerTest : public testing::Test {
protected:
    void SetUp() override {
        // Set up the server with a specific port for testing
        server = new Server(12345);
    }

    void TearDown() override {
        // Clean up the server object
        delete server;
    }

    Server* server;
};

TEST_F(ServerTest, StartTest) {
    // Check if the client starts successfully
    EXPECT_TRUE(server->start());
}

TEST_F(ServerTest, SocketCreationTest) {
    // Check if the server socket is created
    ASSERT_EQ(server->getSocket(), -1);
    ASSERT_EQ(server->getServerPort(), 12345);
}