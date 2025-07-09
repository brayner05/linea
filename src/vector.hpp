#ifndef LINEA_VECTOR_HPP
#define LINEA_VECTOR_HPP

#include <cmath>
#include "matrix.hpp"


namespace linea {
    /// @brief Class representing a 3D vector. A sub-class of Matrix<3,1>,
    /// allowing for any matrix methods to be called on a Vector3.
    class Vector3 : public Matrix<3, 1> {
    public:
        inline Vector3(double xx, double yy, double zz) 
            : Matrix<3, 1>{{xx}, {yy}, {zz}} {}

        inline Vector3() : Vector3(0, 0, 0) {}

        inline double& x() { return this->operator[]({0, 0}); }
        inline double& y() { return this->operator[]({1, 0}); }
        inline double& z() { return this->operator[]({2, 0}); }

        inline double get_x() const { return this->at({0, 0}); }
        inline double get_y() const { return this->at({1, 0}); }
        inline double get_z() const { return this->at({2, 0}); }

        inline double magnitude() const { 
            auto x = this->get_x();
            auto y = this->get_y();
            auto z = this->get_y();
            return std::sqrt(x * x + y * y + z * z);
        }


        inline Vector3 normalize() const {
            auto length = this->magnitude();
            return Vector3 { 
                this->get_x() / length, 
                this->get_y() / length, 
                this->get_z() / length 
            };
        };


        inline double dot(const Vector3& other) const {
            return (
                this->at({0, 0}) * other.at({0, 0}) + 
                this->at({1, 0}) * other.at({1, 0}) + 
                this->at({2, 0}) * other.at({2, 0})
            );
        }

        inline Vector3& operator+=(const Vector3& v) {
            this->x() += v.at({0, 0});
            this->y() += v.at({1, 0});
            this->z() += v.at({2, 0});
            return *this;
        }

        Vector3& operator-=(const Vector3& v) {
            this->x() -= v.at({0, 0});
            this->y() -= v.at({1, 0});
            this->z() -= v.at({2, 0});
            return *this;
        }

        Vector3& operator*=(double scalar) {
            this->x() *= scalar;
            this->y() *= scalar;
            this->z() *= scalar;
            return *this;
        }

        Vector3& operator/=(double scalar) {
            if (scalar == 0) {
                throw std::runtime_error("Cannot divide by 0.");
            }

            this->x() /= scalar;
            this->y() /= scalar;
            this->z() /= scalar;

            return *this;
        }
    };


    Vector3 operator+(Vector3 v, const Vector3& u) {
        v += u;
        return v;
    }


    Vector3 operator-(Vector3 v, const Vector3& u) {
        v -= u;
        return v;
    }


    Vector3 operator*(Vector3 v, double scalar) {
        return v *= scalar;
    }


    Vector3 operator*(double scalar, Vector3 v) {
        return v * scalar;
    }


    Vector3 operator/(Vector3 v, double scalar) {
        return v /= scalar;
    }


    template <u32 R>
    class Vector : public Matrix<R, 1> {

    };
}


#endif