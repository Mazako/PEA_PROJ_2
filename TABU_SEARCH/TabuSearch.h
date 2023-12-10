
#ifndef PEA_PROJ_2_TABUSEARCH_H
#define PEA_PROJ_2_TABUSEARCH_H
#include "ShortestPathResults.h"
#include "TspMatrix.h"

class TabuSearch {

public:
    static ShortestPathResults *solve(TspMatrix* matrix, int limitInMinutes);
};


#endif //PEA_PROJ_2_TABUSEARCH_H
