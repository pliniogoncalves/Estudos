#include <gtest/gtest.h>
#include "BruteForce.h"

// Tests the BruteForce::ordination function.
TEST(BruteForceTest, OrdinationTest) {
    // Test case 1: Test sorting an empty vector
    std::vector<int> arr1 = {};
    BruteForce bf1;
    bf1.ordination(arr1);
    ASSERT_TRUE(arr1.empty());

    // Test case 2: Test sorting a vector with one element
    std::vector<int> arr2 = {5};
    BruteForce bf2;
    bf2.ordination(arr2);
    ASSERT_EQ(arr2.size(), 1);
    ASSERT_EQ(arr2[0], 5);

    // Test case 3: Test sorting a vector with multiple elements
    std::vector<int> arr3 = {4, 7, 1, 9, 2};
    BruteForce bf3;
    bf3.ordination(arr3);
    ASSERT_EQ(arr3.size(), 5);
    ASSERT_EQ(arr3[0], 1);
    ASSERT_EQ(arr3[1], 2);
    ASSERT_EQ(arr3[2], 4);
    ASSERT_EQ(arr3[3], 7);
    ASSERT_EQ(arr3[4], 9);
}