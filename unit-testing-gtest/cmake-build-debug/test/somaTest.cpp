//
// Created by plinio on 19/04/23.
//

#include "soma.cpp"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>


TEST(SomaTeste, TestePositivo) {
    EXPECT_EQ(Soma(2, 2), 4);
    EXPECT_EQ(Soma(10, 20), 30);
}

TEST(SomaTeste, TesteNegativo) {
    EXPECT_EQ(Soma(-5, 10), 5);
    EXPECT_EQ(Soma(-10, -20), -30);
}