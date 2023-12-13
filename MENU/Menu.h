#ifndef PEA_PROJ_2_MENU_H
#define PEA_PROJ_2_MENU_H
#include "TspMatrix.h"

class Menu {
    int timeLimitInMinutes = 2;
    bool verbose = true;
    bool useGreedyStart = false;
    TspMatrix* currentMatrix = nullptr;
    //SA PARAMS
    double tau = 0.2;
    double innerLoopFactor = 1;
    double coolingFactor = 0.995;
    //TS PARAMS
    int unsatisfiedIterationsBeforeReset = 1000;

    void readMatrixFromFile();
    void setSaParams();
    void setTsParams();
    void setGlobalSettings();
    void showAllSettings();
    void performTabuSearch();
    void performSimulatedAnnealing();

public:
    Menu();
    void init();
};


#endif //PEA_PROJ_2_MENU_H
