#include "SimulatedAnnealing.h"
#include "PeaUtils.h"
#include "NeighbourhoodCreator.h"
#include "GreedyAlgorithm.h"
#include <iostream>

SimulatedAnnealing::SimulatedAnnealing() = default;

ShortestPathResults *SimulatedAnnealing::solve(TspMatrix *matrix) {
    int n = matrix->getN();
    auto bestPath = GreedyAlgorithm::solve(matrix)->getPath();
    std::cout << GreedyAlgorithm::solve(matrix)->toString() << std::endl;
    auto bestCost = matrix->calculateCost(bestPath);
    std::cout << bestCost << std::endl;
    auto temperature = initialTemperature(n, bestPath, bestCost, matrix);
    auto currentCost = bestCost;
    auto currentPath = PeaUtils::copyArray(n, bestPath);

    std::cout << "T: " << temperature << std::endl;
    int maxInnerLoopRuns = 100 * n;
    while (temperature > 0.000001) {
        int totalRuns = 0;
        while (totalRuns < maxInnerLoopRuns) {

            auto neighbour = NeighbourhoodCreator::twoOptSwap(n, currentPath);
            auto cost = matrix->calculateCost(currentPath);
            auto delta = cost - currentCost;
            if (delta <= 0) {
                delete currentPath;
                currentPath = PeaUtils::copyArray(n, neighbour);
                currentCost = cost;
                if (cost < bestCost) {
                    bestCost = cost;
                    delete bestPath;
                    bestPath = PeaUtils::copyArray(n, neighbour);
                }
            } else if (isAccepted(cost, currentCost, temperature)) {
                delete currentPath;
                currentPath = PeaUtils::copyArray(n, neighbour);
                currentCost = cost;
            }
            delete neighbour;
            totalRuns++;
//            std::cout << "Kandydat: " << currentCost << " TEMPERATURA: " << temperature <<  std::endl;
        }
        std::cout << "NAJLEPSZY KOSZT: " << bestCost << " TEMPERATURA: " << temperature <<  std::endl;
        temperature *= 0.9999;
    }

    return new ShortestPathResults(bestCost, n, bestPath, 0);
}


double SimulatedAnnealing::initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix) {
    std::vector<long long> costs;
    for (int i = 0; i < 100; i++) {
        auto neighbour = NeighbourhoodCreator::twoOptSwap(n, path);
        auto neighbourCost = matrix->calculateCost(neighbour);
        costs.push_back(neighbourCost - cost);
    }
    double avg = PeaUtils::calculateAverage(costs);
    return std::abs(-avg / std::log(0.5));

}

bool SimulatedAnnealing::isAccepted(long long int newCost,
                                    long long int currentCost, double temparature) {
    double exp1 = std::exp((double) (currentCost - newCost) / temparature);
    double rand = PeaUtils::randomFormalDouble();
    return rand < exp1;
}
