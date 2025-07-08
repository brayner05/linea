#include <iostream>
#include <array>
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    auto u = linea::Vector3(2, 3, 4);
    auto v = linea::Vector3(2, 4, 2);
    std::cout << u.dot(v) << '\n';
}