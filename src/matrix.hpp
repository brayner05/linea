#ifndef LINEA_MATRIX_HPP
#define LINEA_MATRIX_HPP

#include <cstdint>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <string>

namespace linea {
    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    /// @brief An R x C Matrix of doubles.
    /// @tparam R The number of rows.
    /// @tparam C The number of columns.
    template <u32 R, u32 C>
    class Matrix {
    private:
        double data[R][C] {};

    public:
        /// @brief Generates an R x C matrix full of 0's.
        Matrix();

        /// @brief Creates an R x C matrix and allows the values to be defined explicitly.
        /// @param values An R x C list of double values to assign the the matrix.
        Matrix(std::initializer_list<std::initializer_list<double>> values);

        /// @brief Gets the value at a given entry of the matrix.
        /// @param indices An ordered pair of indices (a, b) such that \f$ 0 <= a < R \f$ and \f$ 0 <= B < C \f$.
        /// @return The entry at M_{a,b}.
        double& operator[](const std::pair<u32, u32>& indices);

        /// @brief Gets a copy of the value at a given entry of the matrix.
        /// @param indices An ordered pair of indices (a, b) such that \f$ 0 <= a < R \f$ and \f$ 0 <= B < C \f$.
        /// @return The entry at \f$ M_{a,b} \f$.
        double at(const std::pair<u32, u32>& indices) const;

        /// @brief Gets the transpose of the matrix. That is, for this matrix M,
        /// M.transpose() is the matrix N such that for every \f$ i,j \f$, \f$ N_{i,j} = M_{j, i} \f$
        /// @return The transpose of the matrix.
        Matrix<C, R> transpose() const;

        template <u32 CC>
        Matrix<R, CC> operator*(const Matrix<C, CC>& mat) const;

        Matrix<R, C>& operator+=(const Matrix<R, C>& mat);
        Matrix<R, C>& operator-=(const Matrix<R, C>& mat);
        Matrix<R, C>& operator*=(double scalar);
        Matrix<R, C>& operator/=(double scalar);

        std::string to_string() const;
    };


    template <u32 R, u32 C>
    Matrix<R, C>::Matrix() {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] = 0;
            }
        }
    }


    template <u32 R, u32 C>
    Matrix<R, C>::Matrix(std::initializer_list<std::initializer_list<double>> values) {
        auto input_rows = values.size();
        auto input_cols = values.begin()->size();

        if (input_rows != R || input_cols != C) {
            std::ostringstream os;
            os << "Cannot initialize a " << R << "x" << C << " matrix ";
            os << "with initializer_list of size " << input_rows << "x" << input_cols << ".";
            throw std::runtime_error(os.str());
        }

        u32 row_idx = 0;
        for (auto row = values.begin(); row != values.end(); ++row, ++row_idx) {
            u32 col_idx = 0;
            for (auto col = row->begin(); col != row->end(); ++col, ++col_idx) {
                this->data[row_idx][col_idx] = *col;
            }
        }
    }


    template <u32 R, u32 C>
    double& Matrix<R, C>::operator[](const std::pair<u32, u32>& indices) {
        const auto row = indices.first;
        const auto col = indices.second;

        if (row >= R || col >= C) {
            throw std::runtime_error("Matrix indices out of bounds.");
        }

        return this->data[row][col];
    }


    template <u32 R, u32 C>
    double Matrix<R, C>::at(const std::pair<u32, u32>& indices) const {
        const auto row = indices.first;
        const auto col = indices.second;

        if (row >= R || col >= C) {
            throw std::runtime_error("Matrix indices out of bounds.");
        }

        return this->data[row][col];
    }


    template <u32 R, u32 C>
    Matrix<C, R> Matrix<R, C>::transpose() const {
        Matrix<C, R> transposed {};
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                transposed[{j, i}] = this->at({i, j});
            }
        }
        return transposed;
    }


    template <u32 R, u32 C>
    Matrix<R, C>& Matrix<R, C>::operator+=(const Matrix<R, C>& mat) {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] += mat.data[i][j];
            }
        }
        return *this;
    }


    template <u32 R, u32 C>
    Matrix<R, C>& Matrix<R, C>::operator-=(const Matrix<R, C>& mat) {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] -= mat.data[i][j];
            }
        }
        return *this;
    }


    template <u32 R, u32 C>
    Matrix<R, C>& Matrix<R, C>::operator*=(double scalar) {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] *= scalar;
            }
        }
        return *this;
    }


    template <u32 R, u32 C>
    Matrix<R, C>& Matrix<R, C>::operator/=(double scalar) {
        if (scalar == 0) {
            throw std::runtime_error("Cannot divide by 0.");
        }

        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] /= scalar;
            }
        }

        return *this;
    }


    template <u32 R, u32 C>
    Matrix<R, C> operator+(Matrix<R, C> M1, const Matrix<R, C>& M2) {
        M1 += M2;
        return M1;
    }


    template <u32 R, u32 C>
    Matrix<R, C> operator-(Matrix<R, C> M1, const Matrix<R, C>& M2) {
        M1 -= M2;
        return M1;
    }


    template <u32 R, u32 C>
    Matrix<R, C> operator*(Matrix<R, C> M, double scalar) {
        M *= scalar;
        return M;
    }


    template <u32 R, u32 C>
    Matrix<R, C> operator*(double scalar, Matrix<R, C> M) {
        return M * scalar;
    }


    template <u32 R, u32 C>
    Matrix<R, C> operator/(Matrix<R, C> M1, const Matrix<R, C>& M2) {
        M1 -= M2;
        return M1;
    }


    template <u32 R, u32 C>
    template <u32 CC>
    Matrix<R, CC> Matrix<R, C>::operator*(const Matrix<C, CC>& mat) const {
        Matrix<R, CC> output {};
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < CC; ++j) {
                double sum = 0;
                for (u32 k = 0; k < C; ++k) {
                    sum += this->data[i][k] * mat.at({k, j});
                }
                output[{i, j}] = sum;
            }
        }
        return output;
    }


    template <u32 R, u32 C>
    std::string Matrix<R, C>::to_string() const {
        std::ostringstream os;
        for (u32 row = 0; row < R; ++row) {
            os << "[ ";
            for (u32 col = 0; col < C; ++col) {
                os << this->at({row, col}) << " ";
            }
            os << "]" << (row == R - 1 ? "" : "\n");
        }
        return os.str();
    }
}

#endif