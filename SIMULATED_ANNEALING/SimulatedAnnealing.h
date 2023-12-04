#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H
#include "ShortestPathResults.h"
#include "TspMatrix.h"


class SimulatedAnnealing {
    SimulatedAnnealing();
    static int* generateRandomPath(int n);
    static double initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix);
    static bool isAccepted(long long int newCost, long long int currentCost, double temparature);
public:
    static ShortestPathResults* solve(TspMatrix* matrix);

};



#endif //SIMULATEDANNEALING_H
