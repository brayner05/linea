#ifndef LINEA_MATRIX_HPP
#define LINEA_MATRIX_HPP
#include <cstdint>
#include <utility>
#include <stdexcept>
#include <sstream>

namespace linea {
    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    template <u32 R, u32 C>
    class Matrix {
    private:
        double data[R][C] {};

    public:
        Matrix() = default;
        Matrix(std::initializer_list<std::initializer_list<double>> values);

        double& operator[](const std::pair<u32, u32>& indices);
        double at(const std::pair<u32, u32>& indices) const;

        template <u32 CC>
        Matrix<R, CC> operator*(const Matrix<C, CC>& mat) const;

        Matrix<R, C> operator+=(const Matrix<R, C>& mat);
        Matrix<R, C> operator-=(const Matrix<R, C>& mat);
    };


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
    Matrix<R, C> Matrix<R, C>::operator+=(const Matrix<R, C>& mat) {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] += mat.data[i][j];
            }
        }
    }


    template <u32 R, u32 C>
    Matrix<R, C> Matrix<R, C>::operator-=(const Matrix<R, C>& mat) {
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < C; ++j) {
                this->data[i][j] -= mat.data[i][j];
            }
        }
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
    template <u32 CC>
    Matrix<R, CC> Matrix<R, C>::operator*(const Matrix<C, CC>& mat) const {
        Matrix<R, CC> output {};
        for (u32 i = 0; i < R; ++i) {
            for (u32 j = 0; j < CC; ++j) {
                double sum = 0;
                for (u32 k = 0; k < C; ++k) {
                    sum += this->data[i][k] * mat.data[k][j];
                }
                output[{i, j}] = sum;
            }
        }
        return output;
    }
}

#endif