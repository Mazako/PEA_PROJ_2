#include <iostream>
#include "TabuSearch.h"
#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"

ShortestPathResults *TabuSearch::solve(TspMatrix *matrix, int limitInMinutes) {
    int n = matrix->getN();

    int *bestPath = PeaUtils::generateRandomPath(n);
    long long bestCost = matrix->calculateCost(bestPath);

    int *currentPath = PeaUtils::copyArray(n, bestPath);
    long long currentCost = bestCost;

    int *neighbour = nullptr;
    long long neighbourCost;

    int maxLoops = 1000000000;
    int maxLoopsWithoutProgress = 500;
    int tabuListSize = 3 * n;

    auto tabu = PeaUtils::generateEmptyMatrix(n);

    int v1 = 0;
    int v2 = 0;
    int iter = 0;
    int unsatisfiedRuns = 0;
    while (iter < maxLoops) {
        neighbour = PeaUtils::copyArray(n, currentPath);
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                PeaUtils::swap(i, j, neighbour);
                neighbourCost = matrix->calculateCost(neighbour);

                if (tabu[i][j] == 0  || tabu[j][i] == 0 || neighbourCost < bestCost) {
                    if (neighbourCost < currentCost) {
                        delete currentPath;
                        currentPath = PeaUtils::copyArray(n, neighbour);
                        currentCost = neighbourCost;
                        v1 = i;
                        v2 = j;
                    }
                }
                PeaUtils::swap(j, i, neighbour);
            }
        }

        if (currentCost < bestCost) {
            delete bestPath;
            bestPath = PeaUtils::copyArray(n, currentPath);
            bestCost = currentCost;
            std::cout << "HIT: " << bestCost << std::endl;
            tabu[v1][v2] = tabuListSize;
            tabu[v2][v1] = tabuListSize;
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
            currentPath = PeaUtils::generateRandomPath(n);
            currentCost = matrix->calculateCost(currentPath);
            unsatisfiedRuns = 0;
            tabu = PeaUtils::generateEmptyMatrix(n);
        }

            iter++;
    }
}
