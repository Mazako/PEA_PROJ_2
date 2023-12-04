#ifndef NEIGHBOURHOODCREATOR_H
#define NEIGHBOURHOODCREATOR_H
#include <utility>


class NeighbourhoodCreator {
    NeighbourhoodCreator();
    static std::pair<int, int> randomVertices(int n);
public:
    static int* twoOptSwap(int n, int* array);
    static int* randomTwoSwap(int n, int* array);
};



#endif //NEIGHBOURHOODCREATOR_H
