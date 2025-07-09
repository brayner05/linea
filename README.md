# Linea
Linea is a Linear Algebra library for C++.

## Examples
```cpp
    // Create a 2 x 3 matrix M.
    auto M = linea::Matrix<2, 3> {
        {1, 2, 3},
        {4, 5, 6},
    };

    // Create a 3 x 4 matrix N.
    auto N = linea::Matrix<3, 4> {
        {0, 1, 0, 1},
        {1, 2, 4, 5},
        {1, 1, 1, 1}
    };

    // Multiply M and N.
    auto A = M * N;

    // Compute the transpose of M.
    auto B = M.transpose();

    std::cout << A.to_string() << "\n";
```