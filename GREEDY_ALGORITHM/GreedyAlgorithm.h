#ifndef GREEDYALGORITHM_H
#define GREEDYALGORITHM_H
#include <vector>

#include "ShortestPathResults.h"
#include "TspMatrix.h"

class GreedyAlgorithm {
    GreedyAlgorithm();
    static std::pair<int, int> minimumWithIndex(int n, bool *visited, int **matrix, int from);
public:
    static ShortestPathResults* solve(TspMatrix* matrix);

};


#endif //GREEDYALGORITHM_H
