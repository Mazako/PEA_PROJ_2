#include <iostream>

#include "PeaUtils.h"

int main() {
    auto matrix = PeaUtils::readMatrixFromAtspFile("../RESOURCES/ftv55.atsp");
    std::cout<< matrix->getMatrices()[1][0];
}
