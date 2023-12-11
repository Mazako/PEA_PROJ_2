#include <iostream>
#include "TabuSearch.h"
#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"

ShortestPathResults *TabuSearch::solve(TspMatrix *matrix, int limitInMinutes) {
    std::cout << "TABU SEARCH: GREEDY COST - " << GreedyAlgorithm::solve(matrix)->getCost() << std::endl;
    int n = matrix->getN();

    int *bestPath = PeaUtils::generateRandomPath(n);
    long long bestCost = matrix->calculateCost(bestPath);

    int *currentPath = PeaUtils::copyArray(n, bestPath);
    long long currentCost = bestCost;

    int *neighbour = nullptr;
    long long neighbourCost;

    int maxLoopsWithoutProgress = 1000;
    int tabuListSize = sqrt(n);

    auto tabu = PeaUtils::generateEmptyMatrix(n);
    int v1 = 0;
    int v2 = 0;
    int iter = 0;
    int unsatisfiedRuns = 0;
    auto start = std::chrono::high_resolution_clock::now();
    bool running = true;
    while (running) {
        bool improvement = false;
        neighbour = PeaUtils::copyArray(n, currentPath);
        int *localBest = nullptr;
        long long localCost = INT64_MAX;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                PeaUtils::swap(i, j, neighbour);
                neighbourCost = matrix->calculateCost(neighbour);

                if (tabu[neighbour[i]][neighbour[j]] == 0 && tabu[neighbour[j]][neighbour[i]] == 0 ||
                    neighbourCost < bestCost) {

                    if (neighbourCost < localCost) {
                        delete localBest;
                        localBest = PeaUtils::copyArray(n, neighbour);
                        localCost = neighbourCost;
                        v1 = neighbour[i];
                        v2 = neighbour[j];

                    }
                }
            }
        }

        delete[] currentPath;
        currentPath = PeaUtils::copyArray(n, localBest);
        currentCost = localCost;
        tabu[v1][v2] = tabuListSize;
        tabu[v2][v1] = tabuListSize;

        if (currentCost < bestCost) {
            delete bestPath;
            bestPath = PeaUtils::copyArray(n, currentPath);
            bestCost = currentCost;
            std::cout << "HIT: " << bestCost << "   " << matrix->calculateCost(bestPath) << std::endl;
            unsatisfiedRuns = 0;
        } else {
            unsatisfiedRuns++;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tabu[i][j] != 0) {
                    tabu[i][j]--;
                }
            }
        }


        if (unsatisfiedRuns == maxLoopsWithoutProgress) {
            delete currentPath;
            int *bestRandomPath = nullptr;
            long long bestRandomCost = INT64_MAX;
            for (int i = 0; i < 100; i++) {
                int *path = PeaUtils::generateRandomPath(n);
                long long cost = matrix->calculateCost(path);
                if (cost < bestRandomCost) {
                    delete[] bestRandomPath;
                    bestRandomPath = PeaUtils::copyArray(n, path);
                    bestRandomCost = cost;
                }
                delete[] path;
            }
            currentPath = bestRandomPath;
            currentCost = matrix->calculateCost(currentPath);
            unsatisfiedRuns = 0;
            for (int i = 0; i < n; i++) {
                delete[] tabu[i];
            }
            delete tabu;
            tabu = PeaUtils::generateEmptyMatrix(n);
        }

        iter++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::minutes>(currentTime - start).count() >= limitInMinutes) {
            std::cout << "TIME LIMIT EXCEEDED" << std::endl;
            running = false;
        }

    }
    return new ShortestPathResults(bestCost, n, bestPath, limitInMinutes, true);
}
