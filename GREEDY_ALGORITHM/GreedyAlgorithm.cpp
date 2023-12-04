#include <iostream>
#include "GreedyAlgorithm.h"

#include "PeaUtils.h"

ShortestPathResults* GreedyAlgorithm::solve(TspMatrix* matrix) {
    long long totalCost = 0;
    int* path = new int[matrix->getN()];
    bool* visited = new bool[matrix->getN()];
    visited[0] = true;
    for (int i = 1; i < matrix->getN(); i++) {
        visited[i] = false;
    }

    path[0] = 0;
    int from = 0;
    for (int i = 0; i < matrix->getN() - 1; i++) {
        auto min = minimumWithIndex(matrix->getN(), visited, matrix->getMatrices(), from);
        totalCost += min.first;
        path[i + 1] = min.second;
        visited[min.second] = true;
        from = min.second;
    }
    int last = path[matrix->getN() - 1];
    totalCost += matrix->getMatrices()[last][0];
    delete[] visited;
    return new ShortestPathResults(totalCost, matrix->getN(), path, 0);

}

std::pair<int, int> GreedyAlgorithm::minimumWithIndex(int n, bool *visited, int **matrix, int from) {
    int minimum = INT32_MAX;
    int minimumIndex = -1;
//    if (minimum == -1) {
//        minimum = matrix[from][1];
//        minimumIndex = 1;
//    }
    for (int i = 0; i < n; i++) {
        if (matrix[from][i] < minimum && !visited[i]) {
            minimum = matrix[from][i];
            minimumIndex = i;
        }
    }
    return std::pair<int, int>(minimum, minimumIndex);
}

GreedyAlgorithm::GreedyAlgorithm() = default;
