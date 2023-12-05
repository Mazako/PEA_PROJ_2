#include "SimulatedAnnealing.h"
#include "PeaUtils.h"
#include "NeighbourhoodCreator.h"
#include "GreedyAlgorithm.h"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

SimulatedAnnealing::SimulatedAnnealing() = default;

ShortestPathResults *SimulatedAnnealing::solve(TspMatrix *matrix, int limitInMinutes, double tau,
                                               double innerLoopFactor, double coolingFactor) {
    cout << "Limit: " << limitInMinutes << ", tau: " << tau << ", loopFactor: " << innerLoopFactor << ", coolingFactor: " << coolingFactor << endl;
    int n = matrix->getN();
    auto route = PeaUtils::generateRandomPath(n);
    auto cost = matrix->calculateCost(route);
    cout << "GREEDY COST: " << GreedyAlgorithm::solve(matrix)->getCost();
    int* newRoute = PeaUtils::copyArray(n, route);
    long long newCost = cost;


    auto temperature = initialTemperature(n, route, cost, matrix, tau);

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "T: " << temperature << std::endl;
    int maxInnerLoopRuns = (n * (n - 1)) / 2;
    maxInnerLoopRuns *= innerLoopFactor;
    while (temperature > 0.0000001) {
        int totalRuns = 0;
        int accepted = 0;
        while (totalRuns < maxInnerLoopRuns) {
            auto neighbour = NeighbourhoodCreator::randomTwoSwap(n, newRoute);
            auto neighbourCost = matrix->calculateCost(neighbour);
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
//                    std::cout << "NAJLEPSZY KOSZT: " << cost << " TEMPERATURA: " << temperature << std::endl;

                }
            } else if (isAccepted((double) delta, temperature)) {
                delete newRoute;
                newRoute = PeaUtils::copyArray(n, neighbour);
                newCost = neighbourCost;
            }
            delete neighbour;
            totalRuns++;
        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::minutes>(currentTime - start).count() > limitInMinutes) {
            cout << "TIME LIMIT EXCEEDED" << endl;
            return new ShortestPathResults(cost, n, route, 0, true);
        }
        temperature *= coolingFactor;
    }

    return new ShortestPathResults(cost, n, route, 0, false);
}


double SimulatedAnnealing::initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix, double tau) {
    std::vector<long long> costs;
    for (int i = 0; i < 100; i++) {
        auto neighbour = NeighbourhoodCreator::randomTwoSwap(n, path);
        auto neighbourCost = matrix->calculateCost(neighbour);
        costs.push_back(std::abs(neighbourCost - cost));
    }
    double avg = PeaUtils::calculateAverage(costs);
    return std::abs(avg / std::log(tau));

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

