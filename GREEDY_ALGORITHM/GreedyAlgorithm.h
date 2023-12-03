#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H
#include <vector>

#include "ShortestPathResults.h"
#include "TspMatrix.h"

class GreedyAlgorithm {
    GreedyAlgorithm();
    static std::pair<int, int> minumumWithIndex(int n, int* row, bool* visited);
public:
    static ShortestPathResults* solve(TspMatrix* matrix);

};


#endif //GREEDYALGORITHM_H
