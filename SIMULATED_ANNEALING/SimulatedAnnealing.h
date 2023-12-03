#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H
#include "ShortestPathResults.h"
#include "TspMatrix.h"


class SimulatedAnnealing {
    SimulatedAnnealing();
public:
    ShortestPathResults* solve(TspMatrix* matrix);

};



#endif //SIMULATEDANNEALING_H
