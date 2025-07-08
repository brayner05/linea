#ifndef LINEA_VECTOR_HPP
#define LINEA_VECTOR_HPP
#include "matrix.hpp"


namespace linea {
    class Vector3 : public Matrix<3, 1> {
    public:
        inline Vector3(double xx, double yy, double zz) 
            : Matrix<3, 1>{{xx}, {yy}, {zz}} {}

        inline Vector3() : Vector3(0, 0, 0) {}

        inline double& x() { return this->operator[]({0, 0}); }
        inline double& y() { return this->operator[]({1, 0}); }
        inline double& z() { return this->operator[]({2, 0}); }

        inline double dot(const Vector3& other) const {
            return (
                this->at({0, 0}) * other.at({0, 0}) + 
                this->at({1, 0}) * other.at({1, 0}) + 
                this->at({2, 0}) * other.at({2, 0})
            );
        }
    };

    template <u32 R>
    class Vector : public Matrix<R, 1> {

    };
}


#endif