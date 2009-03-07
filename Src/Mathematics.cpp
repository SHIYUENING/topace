#include "Mathematics.h"

Vector2d cross(const Vector2d& rhs){
    return Vector2d(-rhs(1), rhs(0));
}

Vector3d cross(const Vector3d& rhs){
    Vector2d r = cross(Vector2d(rhs(0), rhs(1)));
    return Vector3d(r(0), r(1), 0);
}

double CRad(double degress){
    return degress / 180. * pi;
}

double CDeg(double radius){
    return radius / pi * 180.;
}

double Sign(double d){
    if (d > 0){ return 1; }
    if (d < 0){ return -1; }
    return 0;
}

double acos_s(double d){
    if (d >= 1.){ return 0.; }
    else if (d <= -1.){ return pi; }
    return acos(d);
}