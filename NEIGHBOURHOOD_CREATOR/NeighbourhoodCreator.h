#ifndef NEIGHBOURHOODCREATOR_H
#define NEIGHBOURHOODCREATOR_H
#include <utility>


class NeighbourhoodCreator {
    NeighbourhoodCreator();
public:
    static std::pair<int, int> randomVertices(int n);
    static int* randomTwoOptSwap(int n, int* array);
    static int* randomTwoSwap(int n, int* array);
};



#endif //NEIGHBOURHOODCREATOR_H
