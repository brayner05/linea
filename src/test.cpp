#include <iostream>
#include <array>
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    auto u = linea::Vector3(2, 3, 4);
    auto v = linea::Vector3(2, 4, 2);
    std::cout << u.dot(v) << '\n';

    auto v1 = 2 * u + 3 * v;
    std::cout << "[" << v1.x() << ", " << v1.y() << ", " << v1.z() << "]\n";
}