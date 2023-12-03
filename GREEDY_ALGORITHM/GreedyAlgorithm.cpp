#include "GreedyAlgorithm.h"

#include "PeaUtils.h"

ShortestPathResults* GreedyAlgorithm::solve(TspMatrix* matrix) {
    unsigned long long totalCost = 0;
    int* path = new int[matrix->getN()];
    bool* visited = new bool[matrix->getN()];
    for (int i = 0; i < matrix->getN(); i++) {
        visited[i] = false;
    }

    path[0] = 0;
    for (int i = 0; i < matrix->getN() - 1; i++) {
        auto min = minumumWithIndex(matrix->getN(), matrix->getMatrices()[i], visited);
        totalCost += min.first;
        path[i + 1] = min.second;
        visited[min.second] = true;
    }
    int last = path[matrix->getN() - 1];
    totalCost += matrix->getMatrices()[last][0];
    return new ShortestPathResults(totalCost, matrix->getN(), path, 0);

}

std::pair<int, int> GreedyAlgorithm::minumumWithIndex(int n, int* row, bool* visited) {
    int minimum = row[0];
    int minimumIndex = 0;
    if (minimum == -1) {
        minimum = row[1];
        minimumIndex = 1;
    }
    for (int i = 0; i < n; i++) {
        if (row[i] > -1 && row[i] < minimum && !visited[i]) {
            minimum = row[i];
            minimumIndex = i;
        }
    }
    return std::pair<int, int>(minimum, minimumIndex);
}
