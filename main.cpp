#include <iostream>

#include "PeaUtils.h"
#include "GREEDY_ALGORITHM/GreedyAlgorithm.h"
#include "NEIGHBOURHOOD_CREATOR/NeighbourhoodCreator.h"

using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    NeighbourhoodCreator::twoOptSwap(6, arr);
}
