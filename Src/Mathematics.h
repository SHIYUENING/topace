#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

#include <math.h>
#include <tvmet/Matrix.h>
#include <tvmet/Vector.h>

using namespace std;
using namespace tvmet;

typedef Vector<double, 2>	Vector2d;
typedef Matrix<double, 2, 2>	Matrix22d;
typedef Vector<double, 3>	Vector3d;
typedef Matrix<double, 3, 3>	Matrix33d;
typedef Vector<double, 4>	Vector4d;
typedef Matrix<double, 4, 4>	Matrix44d;

const double PI = 3.14159265358979323846;
const double pi = PI;
const double E = 2.7182818284590452354;

template <typename T>
T det(const Matrix<T, 0, 0>& m){
    return 0;
}

template <typename T>
T det(const Matrix<T, 1, 1>& m){
    return m(0, 0);
}

template <typename T>
T det(const Matrix<T, 2, 2>& m){
    return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}

template <typename T>
T det(const Matrix<T, 3, 3>& m){
    return m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0) + m(0, 2) * m(1, 0) * m(2, 1)
           - m(0, 0) * m(1, 2) * m(2, 1) - m(0, 1) * m(1, 0) * m(2, 2) - m(0, 2) * m(1, 1) * m(2, 0);
}

template <typename T>
T sgn(const T& m){
    if (m > 0) { return 1; }
    if (m < 0) { return -1; }
    return 0;
}

template <typename T>
void exchange(T& a, T& b){
    T t = a;
    a = b;
    b = t;
}

template <typename T, size_t Sz>
T det(const Matrix<T, Sz, Sz>& rhs){
    T m[Sz * Sz];

#define m(i, j) m[(i) + (j) * Sz]

    for (size_t j = 0; j < Sz; j++){
        for (size_t i = 0; i < Sz; i++){
            m(i, j) = rhs(i, j);
        }
    }

    T Value = 1;
    for (size_t j = 0; j < Sz; j++){
        bool Sign = false;
        for (size_t i = j; i < Sz; i++){
            if (m(i, j) != 0){
                if (i != j){
                    for (size_t n = 0; n < Sz; n++){
                        exchange(m(i, n), m(j, n));
                    }
                }
                Value *= sgn(m(j, j));
                for (size_t k = j + 1; k < Sz; k++){
                    T Temp = -m(k, j) / m(j, j);
                    for (int n = 0; n < Sz; n++){
                        m(k, n) += Temp * m(j, n);
                    }
                }
                Sign = true;
                break;
            }
        }
        if (!Sign){ return 0; }
    }
    for (size_t j = 0; j < Sz; j++){
        Value *= m(j, j);
    }
    return Value;

#undef m
}

Vector2d cross(const Vector2d& rhs);

Vector3d cross(const Vector3d& rhs);

double CRad(double degress);

double CDeg(double radius);

double Sign(double d);

double acos_s(double d);

#include "Transform.h"
#endif
