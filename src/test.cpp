#include <iostream>
#include <array>
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    auto v = linea::Vector3 { 1, 2, 3 };
    std::cout << v.normalize().to_string() << "\n";
}