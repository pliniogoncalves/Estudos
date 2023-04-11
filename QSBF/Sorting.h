#ifndef QSBF_SORTING_H
#define QSBF_SORTING_H

#include <vector>
#include <memory>

class Sorting {
public:
    virtual ~Sorting() {}
    virtual void ordination(std::vector<int>& arr) = 0;
};

typedef std::shared_ptr<Sorting> SortingPtr;

#endif //QSBF_SORTING_H
