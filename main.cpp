#include <iostream>

#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        string fileName = argv[1];
        int limitInMinutes = stoi(argv[2]);
        double tau = stod(argv[3]);
        double innerLoopFactor = stod(argv[4]);
        double coolingFactor = stod(argv[5]);
        auto matrix = PeaUtils::readMatrixFromAtspFile(fileName);
        auto result = SimulatedAnnealing::solve(matrix, limitInMinutes, tau, innerLoopFactor, coolingFactor);

        ofstream stream;
        string timeCause = result->isNoTimeCause() ? "true" : "false";
        stream.open("result.txt", ios::out);
        stream << result->getCost() << " " << timeCause << endl;

    }
//    auto matrix = PeaUtils::readMatrixFromAtspFile("../RESOURCES/rbg358.atsp");
//    cout << SimulatedAnnealing::solve(matrix, 0, 0.5, 1, 0.999)->toString() << endl;
}
