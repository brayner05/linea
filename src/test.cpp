#include <iostream>
#include <array>
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    auto m = linea::Matrix<4, 4>::identity();
    std::cout << m.to_string() << '\n';
}