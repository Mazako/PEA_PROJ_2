#include "SimulatedAnnealing.h"
#include "PeaUtils.h"
#include "NeighbourhoodCreator.h"
#include "GreedyAlgorithm.h"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

SimulatedAnnealing::SimulatedAnnealing() = default;

ShortestPathResults *SimulatedAnnealing::solve(TspMatrix *matrix, int limitInSeconds, double tau,
                                               double innerLoopFactor,
                                               double coolingFactor, bool verbose, bool greedyStart) {
    std::vector<std::string> logger;
    cout << "Matrix name: " << matrix->getName() << endl;
    cout << "Limit: " << limitInSeconds << ", tau: " << tau << ", loopFactor: " << innerLoopFactor << ", coolingFactor: " << coolingFactor << endl;
    int n = matrix->getN();
    int* route;
    if (greedyStart) {
        auto greedy = GreedyAlgorithm::solve(matrix);
        route = PeaUtils::copyArray(n, greedy->getPath());
        delete greedy;
    } else {
        route = PeaUtils::generateRandomPath(n);
    }

    auto cost = matrix->calculateCost(route);
    cout << "GREEDY COST: " << GreedyAlgorithm::solve(matrix)->getCost() << endl;
    int* newRoute = PeaUtils::copyArray(n, route);
    long long newCost = cost;


    auto temperature = initialTemperature(n, route, cost, matrix, tau);

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "T: " << temperature << std::endl;
    int maxInnerLoopRuns = (n * (n - 1)) / 2;
    maxInnerLoopRuns *= innerLoopFactor;
    bool running = true;
    while (temperature > 0.0000001 && running) {
        int totalRuns = 0;
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
                    auto current = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
                    std::string message;
                    message.append(std::to_string(cost)).append(";").append(std::to_string(temperature))
                           .append(";").append(std::to_string(duration));
                    logger.emplace_back(message);
                    if (verbose) {
                        std::cout << "BEST COST: " << cost << " T: " << temperature << " TIME: " << duration <<  std::endl;
                    }

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
        temperature *= coolingFactor;
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - start).count() >= limitInSeconds) {
            if (verbose) {
                cout << "TIME LIMIT EXCEEDED" << endl;
            }
            running = false;
            logger.emplace_back("TIME LIMIT EXCEDED");
        }
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(currentTime - start).count();
    auto path = PeaUtils::saveResultsToFile(n, route, matrix->getName(), "SA");
    PeaUtils::saveLogsToFile(logger, path + "_LOGS");
    delete[] newRoute;
    cout << "T: " << temperature << std::endl;
    cout << "exp(-1/Tk) = " << std::exp(-1.0 / temperature) << std::endl;
    return new ShortestPathResults(cost, n, route, time, false, path);
}


double SimulatedAnnealing::initialTemperature(int n, int *path, long long int cost, TspMatrix *matrix, double tau) {
    std::vector<long long> costs;
    for (int i = 0; i < 100; i++) {
        auto neighbour = NeighbourhoodCreator::randomTwoSwap(n, path);
        auto neighbourCost = matrix->calculateCost(neighbour);
        costs.push_back(std::abs(neighbourCost - cost));
    }
    double avg = PeaUtils::calculateAverage(costs);
    return -avg / std::log(tau);

}

bool SimulatedAnnealing::isAccepted(double delta, double temparature) {
    double exp1 = std::exp((-delta) / temparature);
    double rand = PeaUtils::randomFormalDouble();
    bool accepted = rand < exp1;
    return accepted;
}

