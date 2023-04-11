#ifndef QSBF_QUICKSORT_H
#define QSBF_QUICKSORT_H

#include "Sorting.h"

class QuickSort : public Sorting {
public:
    void ordination(std::vector<int>& arr) override;

private:
    int partition(std::vector<int> &arr, int low, int high);
    void quicksort(std::vector<int>& arr, int low, int high);
};

#endif //QSBF_QUICKSORT_H
