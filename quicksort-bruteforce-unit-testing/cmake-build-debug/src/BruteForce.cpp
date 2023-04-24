#include "BruteForce.h"

void BruteForce::ordination(std::vector<int>& arr)
{
    // Implementation of the brute force sorting algorithm

    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        // Loop through the array to the penultimate element
        for(int j = 0; j < n-i-1; j++) {
            // Loops through the array to the element that needs to be sorted
            if(arr[j] > arr[j+1]) {
                // Swap adjacent elements
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}