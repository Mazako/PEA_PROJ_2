cmake_minimum_required(VERSION 3.25.2)
project(PEA_PROJ_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(PEA_UTILS
        SHORTEST_PATH_RESULTS
        TSP_MATRIX
        TSP_MATRIX_SET
        GREEDY_ALGORITHM
        SIMULATED_ANNEALING
        NEIGHBOURHOOD_CREATOR
        TABU_SEARCH
        MENU)

add_executable(PEA_PROJ_2 main.cpp
        PEA_UTILS/PeaUtils.cpp
        PEA_UTILS/PeaUtils.h
        SHORTEST_PATH_RESULTS/ShortestPathResults.h
        SHORTEST_PATH_RESULTS/ShortestPathResults.cpp
        TSP_MATRIX/TspMatrix.cpp
        TSP_MATRIX/TspMatrix.h
        TSP_MATRIX_SET/RandomTspMatrixSet.cpp
        TSP_MATRIX_SET/RandomTspMatrixSet.h
        GREEDY_ALGORITHM/GreedyAlgorithm.cpp
        GREEDY_ALGORITHM/GreedyAlgorithm.h
        NEIGHBOURHOOD_CREATOR/NeighbourhoodCreator.cpp
        NEIGHBOURHOOD_CREATOR/NeighbourhoodCreator.h
        SIMULATED_ANNEALING/SimulatedAnnealing.cpp
        SIMULATED_ANNEALING/SimulatedAnnealing.h
        TABU_SEARCH/TabuSearch.cpp
        TABU_SEARCH/TabuSearch.h
        MENU/Menu.cpp
        MENU/Menu.h)