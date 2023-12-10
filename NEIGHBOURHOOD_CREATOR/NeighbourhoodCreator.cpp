#include <iostream>
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

int* NeighbourhoodCreator::randomTwoOptSwap(int n, int* array) {
    int* newNeighbour = new int[n];
    auto v = randomVertices(n - 1);
    for (int i = 0; i <= v.first; i++) {
        newNeighbour[i] = array[i];
    }
    for (int i = 0; i <= v.second - v.first; i++) {
        newNeighbour[v.first + 1 + i] = array[v.second - i];
    }

    for (int i = v.second + 1; i < n; i++) {
        newNeighbour[i] = array[i];
    }

    return newNeighbour;

}

int *NeighbourhoodCreator::randomTwoSwap(int n, int *array) {
    int* newNeighbour = PeaUtils::copyArray(n, array);
//    std::cout << PeaUtils::arrayToString(n, newNeighbour) << std::endl;
    auto v = randomVertices(n - 1);
//    std::cout << "v1: " << v.first << " v2 " << v.second << std::endl;
    PeaUtils::swap(v.first, v.second, newNeighbour);
    return newNeighbour;
}

void NeighbourhoodCreator::twoOptSwap(int n, int v2, int v1, int **arrayPtr) {
    int* array = *arrayPtr;
    int* newNeighbour = new int[n];
    for (int i = 0; i <= v1; i++) {
        newNeighbour[i] = array[i];
    }
    for (int i = 0; i <= v2 - v1; i++) {
        newNeighbour[v1 + 1 + i] = array[v2 - i];
    }

    for (int i = v1 + 1; i < n; i++) {
        newNeighbour[i] = array[i];
    }
    delete array;
    *arrayPtr = newNeighbour;
}


NeighbourhoodCreator::NeighbourhoodCreator() = default;
