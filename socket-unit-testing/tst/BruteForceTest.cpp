#include <gtest/gtest.h>
#include "client.h"
#include "server.h"

TEST(SocketTest, PingReplyTest) {
// Create and start the server
// server object creation
Server server(8888);
server.Start();

// Create and connect the client to the server
Client client("127.0.0.1", 8888);
client.start();

// Send a ping request from the client
client.sendPing();

// Receive the ping reply at the server
bool receivedReply = client.receivePingReply();

// Assert that the server received a ping reply
ASSERT_TRUE(receivedReply);
EXPECT_EQ(receivedReply, true);
}