#include <gtest/gtest.h>
#include "QuickSort.h"

TEST(QuickSortTest, PartitionTest) {
QuickSort sorter;
std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
int pivotIndex = sorter.partition(arr, 0, arr.size() - 1);
EXPECT_EQ(pivotIndex, 8);
}