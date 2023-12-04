#include "SimulatedAnnealing.h"
#include "PeaUtils.h"
#include "NeighbourhoodCreator.h"
#include "GreedyAlgorithm.h"
#include <iostream>

using std::cout;
using std::endl;

SimulatedAnnealing::SimulatedAnnealing() = default;

ShortestPathResults *SimulatedAnnealing::solve(TspMatrix *matrix) {
    int n = matrix->getN();
    auto route = GreedyAlgorithm::solve(matrix)->getPath();
    auto cost = matrix->calculateCost(route);

    int* newRoute = PeaUtils::copyArray(n, route);
    long long newCost = cost;

    auto temperature = initialTemperature(n, route, cost, matrix);


    std::cout << "T: " << temperature << std::endl;
    int maxInnerLoopRuns = n * 30;
    while (temperature > 0.000001) {
        int totalRuns = 0;
        int accepted = 0;
        while (totalRuns < maxInnerLoopRuns) {
            auto neighbour = NeighbourhoodCreator::twoOptSwap(n, newRoute);
            auto neighbourCost = matrix->calculateCost(neighbour);
//            cout << "CURRENT: " << newCost << " NEIGHBOUR << " << neighbourCost << endl;
            long long delta = neighbourCost - newCost;
            if (delta <= 0) {
                delete newRoute;
                newRoute = PeaUtils::copyArray(n, neighbour);
                newCost = neighbourCost;
                if (newCost < cost) {
                    delete route;
                    route = PeaUtils::copyArray(n, newRoute);
                    cost = newCost;
                    accepted++;
                    cout << "HIT" << endl;
                }
            } else if (isAccepted((double) delta, temperature)) {
                delete newRoute;
                newRoute = PeaUtils::copyArray(n, neighbour);
                newCost = neighbourCost;
            }
            delete neighbour;
            totalRuns++;
        }
//        std::cout << "NAJLEPSZY KOSZT: " << cost << " TEMPERATURA: " << temperature << std::endl;
        temperature *= 0.95;
    }

    return new ShortestPathResults(cost, n, route, 0);
}


double SimulatedAnnealing::initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix) {
    std::vector<long long> costs;
    for (int i = 0; i < 100; i++) {
        auto neighbour = NeighbourhoodCreator::randomTwoSwap(n, path);
        auto neighbourCost = matrix->calculateCost(neighbour);
        costs.push_back(std::abs(neighbourCost - cost));
    }
    double avg = PeaUtils::calculateAverage(costs);
    return std::abs(-avg / std::log(0.5));

}

bool SimulatedAnnealing::isAccepted(double delta, double temparature) {
    double exp1 = std::exp((-delta) / temparature);
    double rand = PeaUtils::randomFormalDouble();
    bool accepted = rand < exp1;
    if (accepted) {
//        cout << rand << " " << exp1 << endl;
    }
    return accepted;
}

