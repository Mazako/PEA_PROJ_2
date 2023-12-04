#include <iostream>

#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main() {
//    int arr[] = {1, 2, 3, 4, 5, 6};
//    NeighbourhoodCreator::twoOptSwap(6, arr);
    auto matrix = PeaUtils::readMatrixFromAtspFile("../RESOURCES/ftv55.atsp");
    cout << SimulatedAnnealing::solve(matrix)->toString() << endl;
}
