#include <iostream>
#include <array>
#include "matrix.hpp"

int main() {
    auto matrix = linea::Matrix<3, 3> {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    auto multiply = linea::Matrix<3, 3> {
        {2, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    auto M = multiply * matrix;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << M[{i, j}] << '\n';
        }
    }
}