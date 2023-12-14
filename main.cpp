#include <iostream>

#include "PeaUtils.h"
#include "GreedyAlgorithm.h"
#include "NeighbourhoodCreator.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
#include "menu.h"
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
        } else {
            return -1;
        }


        ofstream stream;
        string timeCause = result->isNoTimeCause() ? "true" : "false";
        stream.open("result.txt", ios::out);
        stream << result->getCost() << " " << timeCause << endl;

    } else {
        menu();
//    auto matrix = PeaUtils::readMatrixFromXmlFile("../RESOURCES/rbg358.xml");
//    cout << SimulatedAnnealing::solve(matrix, 2, 0.0000001, 0.5, 0.999, true, true);
//    TabuSearch::solve(matrix, 6, 1000, true, true);

    }

}

void menu() {
    Menu().init();
}
