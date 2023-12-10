#include <iostream>
#include "TabuSearch.h"
#include "PeaUtils.h"
#include "GreedyAlgorithm.h"

ShortestPathResults *TabuSearch::solve(TspMatrix *matrix, int limitInMinutes) {
    int n = matrix->getN();

    int *bestPath = PeaUtils::generateRandomPath(n);
    long long bestCost = matrix->calculateCost(bestPath);

    int *currentPath = PeaUtils::copyArray(n, bestPath);
    long long currentCost = bestCost;

    int *neighbour = nullptr;
    long long neighbourCost;

    int maxLoops = 1000000000;
    int maxLoopsWithoutProgress = 100;
    int tabuListSize = 3 * n;

    auto tabu = PeaUtils::generateEmptyMatrix(n);
    auto frequencies = PeaUtils::generateEmptyMatrix(n);

    int v1 = 0;
    int v2 = 0;
    int iter = 0;
    int unsatisfiedRuns = 0;
    while (iter < maxLoops) {
        neighbour = PeaUtils::copyArray(n, currentPath);
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n; j++) {
                PeaUtils::swap(i, j, neighbour);
                neighbourCost = matrix->calculateCost(neighbour);

                if (tabu[neighbour[i]][neighbour[j]] <= iter || tabu[neighbour[j]][neighbour[i]] <= iter ||
                    neighbourCost < bestCost) {
                    if (neighbourCost < currentCost) {
                        delete currentPath;
                        currentPath = PeaUtils::copyArray(n, neighbour);
                        currentCost = neighbourCost;
                        v1 = std::min(neighbour[i], neighbour[j]);
                        v2 = std::max(neighbour[i], neighbour[j]);

                    }
                } else {
                    double penalScore;
                    if (frequencies[neighbour[i]][neighbour[j]] != 0) {
                        penalScore = neighbourCost + (10 * frequencies[neighbour[i]][neighbour[j]]);
                    } else {
                        penalScore = neighbourCost + (10 * frequencies[neighbour[j]][neighbour[i]]);
                    }
                    if(penalScore < currentCost) {
                        std::cout << "PENAL HIT" << std::endl;
                        delete currentPath;
                        currentPath = PeaUtils::copyArray(n, neighbour);
                        currentCost = neighbourCost;
                        v1 = std::min(neighbour[i], neighbour[j]);
                        v2 = std::max(neighbour[i], neighbour[j]);

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
            tabu[v1][v2] = iter + tabuListSize;
            tabu[v2][v1] = iter + tabuListSize;
            frequencies[v1][v2]++;
            unsatisfiedRuns = 0;
        } else {
            unsatisfiedRuns++;
        }

        if (unsatisfiedRuns == maxLoopsWithoutProgress) {
//            std::cout << "SHUFLE" << std::endl;
            delete currentPath;
            currentPath = PeaUtils::generateRandomPath(n);
            currentCost = matrix->calculateCost(currentPath);
            unsatisfiedRuns = 0;
            tabu = PeaUtils::generateEmptyMatrix(n);
        }
        iter++;
    }
}
