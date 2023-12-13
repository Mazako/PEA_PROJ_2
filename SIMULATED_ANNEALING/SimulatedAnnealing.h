#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H
#include "ShortestPathResults.h"
#include "TspMatrix.h"


class SimulatedAnnealing {
    SimulatedAnnealing();
    static double initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix, double tau);
    static bool isAccepted(double delta, double temparature);
public:
    static ShortestPathResults *
    solve(TspMatrix *matrix, int limitInMinutes, double tau, double innerLoopFactor,
          double coolingFactor, bool verbose, bool greedyStart);

};



#endif //SIMULATEDANNEALING_H
