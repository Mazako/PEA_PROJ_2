#include <iostream>

#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"

using namespace std;

void menu();

int main(int argc, char *argv[]) {
    if (argc > 1) {
        string method = argv[1];
        string fileName = argv[2];
        bool greedyStart = stoi(argv[3]) != 0;
        auto matrix = PeaUtils::readMatrixFromAtspFile(fileName);
        int limitInMinutes = stoi(argv[4]);
        ShortestPathResults* result;
        if (method == "SA") {
            double tau = stod(argv[5]);
            double innerLoopFactor = stod(argv[6]);
            double coolingFactor = stod(argv[7]);
            result = SimulatedAnnealing::solve(matrix, limitInMinutes, tau, innerLoopFactor, coolingFactor, false,
                                                    greedyStart);
        } else if (method == "TS") {
            int loops = stoi(argv[5]);
            result = TabuSearch::solve(matrix, limitInMinutes, loops, false, greedyStart);
        }


        ofstream stream;
        string timeCause = result->isNoTimeCause() ? "true" : "false";
        stream.open("result.txt", ios::out);
        stream << result->getCost() << " " << timeCause << endl;

    }
//    auto matrix = PeaUtils::readMatrixFromAtspFile("../RESOURCES/ftv170.atsp");
//    cout << SimulatedAnnealing::solve(matrix, 4, 0.00001, 0.5,
//                                      0.995, true, true)->toString() << endl;
//    TabuSearch::solve(matrix, 1, 10000, true, true);

}
