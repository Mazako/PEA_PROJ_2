#include "NeighbourhoodCreator.h"

#include "PeaUtils.h"

std::pair<int, int> NeighbourhoodCreator::randomVertices(int n) {
    int v1 = PeaUtils::randomInt(n);
    int v2 = PeaUtils::randomInt(n);
    while (v1 == v2) {
        v2 = PeaUtils::randomInt(n);
    }
    return std::pair<int, int>(std::min(v1, v2), std::max(v1, v2));
}

int* NeighbourhoodCreator::twoOptSwap(int n, int* array) {
    int* newNeighbour = new int[n];
    auto v = randomVertices(n - 1);
    for (int i = 0; i < v.first; i++) {
        newNeighbour[i] = array[i];
    }
    for (int i = v.first + 1; i <= v.second; i++) {
        newNeighbour[i] = array[v.second - i];
    }

    for (int i = v.second + 1; i < n; i++) {
        newNeighbour[i] = array[i];
    }

    return array;

}