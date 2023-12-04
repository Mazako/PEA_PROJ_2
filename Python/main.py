import python_tsp.heuristics as solver
import numpy as np


def read_matrix_from_atsp_file(filename):
    with open(filename, 'r') as file:
        # Skip first 4 lines
        for _ in range(3):
            next(file)

        # Read dimension
        dimension_line = next(file).split()
        dimension = int(dimension_line[1])

        # Skip next 4 lines
        for _ in range(3):
            next(file)

        # Initialize matrix
        matrix = np.zeros((dimension, dimension), dtype=int)
        i, j = 0, 0

        # Read matrix data
        for line in file:
            if line.strip() == "EOF":
                break
            for number in line.split():
                matrix[i][j] = int(number)
                j += 1
                if j % dimension == 0:
                    i += 1
                    j = 0

    return matrix



matrix = read_matrix_from_atsp_file('../RESOURCES/ftv55.atsp')
x0=[0, 33, 2, 13, 35, 4, 6, 5, 47, 31, 46, 55, 34, 1, 3, 48, 29, 27, 49, 43, 44, 28, 53, 45, 30, 26, 25, 24, 42, 21, 50, 23, 54, 22, 41, 40, 20, 18, 39, 38, 10, 51, 14, 12, 15, 16, 17, 52, 32, 8, 7, 36, 9, 37, 11, 19]
print(len(x0))
print(solver.solve_tsp_simulated_annealing(matrix, x0=x0))
