#ifndef NEIGHBOURHOODCREATOR_H
#define NEIGHBOURHOODCREATOR_H
#include <utility>


class NeighbourhoodCreator {
    NeighbourhoodCreator();
    static std::pair<int, int> randomVertices(int n);
public:
    static int* randomTwoOptSwap(int n, int* array);
    static int* randomTwoSwap(int n, int* array);
    static void twoOptSwap(int n, int v2, int v1, int **arrayPtr);
};



#endif //NEIGHBOURHOODCREATOR_H
