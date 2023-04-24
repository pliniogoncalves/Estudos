#include "Sorting.h"
#include "BruteForce.h"
#include "QuickSort.h"
#include <iostream>
#include <memory>

int main(){

    // Using smart pointers to create BruteForce and QuickSort objects

    SortingPtr ordination1 = std::make_shared<BruteForce>();
    SortingPtr ordination2 = std::make_shared<QuickSort>();

    //Example of using sorting classes

    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    std::vector<int> arr(size);

    // Prompts the user to input array elements
    std::cout << "Enter the array values: " << std::endl;
    for(int i =0; i < size; i++){
        std::cin >> arr[i];
    }
    std::cout << std::endl;

    ordination1 ->ordination(arr);
    std::cout << "Array Sorted by BruteForce: ";
    for (int num: arr)
        std::cout << num << " ";
    std::cout << std::endl;

    ordination2->ordination(arr);
    std::cout << "Array sorted by QuickSort: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
