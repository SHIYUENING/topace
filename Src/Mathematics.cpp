#include "Mathematics.h"

Matrix44d inverse(const Matrix44d& m)
{   
    double   a1,a2,a3,a4;   
    double   b1,b2,b3,b4;   
    double   c1,c2,c3,c4;   
    double   d1,d2,d3,d4;   

    a1=m(0, 0);
    a2=m(0, 1);
    a3=m(0, 2);
    a4=m(0, 3);

    b1=m(1, 0);
    b2=m(1, 1);
    b3=m(1, 2);
    b4=m(1, 3);

    c1=m(2, 0);
    c2=m(2, 1);
    c3=m(2, 2);
    c4=m(2, 3);

    d1=m(3, 0);
    d2=m(3, 1);
    d3=m(3, 2);
    d4=m(3, 3);

    double   KK;   
    KK=(-a1*b2*d3*c4+a1*b2*d4*c3-a1*d4*c2*b3-a1*d2*b4*c3     
        +a1*d3*c2*b4+a1*d2*b3*c4+b2*d1*a3*c4-b2*d4*c1*a3   
        -b2*d1*a4*c3+b2*d3*c1*a4-d1*a2*b3*c4+d1*a4*c2*b3   
        +d2*b4*c1*a3+d2*b1*a4*c3+d3*c4*b1*a2-d3*c2*b1*a4   
        -d3*c1*a2*b4-d1*a3*c2*b4-d2*b3*c1*a4-d2*b1*a3*c4   
        -d4*c3*b1*a2+d4*c2*b1*a3+d4*c1*a2*b3+d1*a2*b4*c3);     

    double   KK_1;   
    KK_1=1.0/KK;   

    Matrix44d C;

    C(0,0)=   (-b2*d3*c4+b2*d4*c3-d4*c2*b3-d2*b4*c3+d3*c2*b4+d2*b3*c4)*KK_1;   
    C(0,1)=-(-d2*a4*c3-d3*c4*a2+d3*c2*a4-d4*c2*a3+d2*a3*c4+d4*c3*a2)*KK_1;   
    C(0,2)=   (   d4*a2*b3-d3*a2*b4-d2*b3*a4-d4*b2*a3+d2*b4*a3+d3*b2*a4)*KK_1;   
    C(0,3)=-(-a4*c2*b3-a2*b4*c3-b2*a3*c4+a3*c2*b4+b2*a4*c3+a2*b3*c4)*KK_1;     

    C(1,0)=-(-d3*c4*b1+d4*c3*b1+d1*b3*c4-d4*c1*b3-d1*b4*c3+d3*c1*b4)*KK_1;   
    C(1,1)=   (-a1*d3*c4+a1*d4*c3+d1*a3*c4-d4*c1*a3-d1*a4*c3+d3*c1*a4)*KK_1;     
    C(1,2)=-(-a1*d3*b4+a1*d4*b3+d1*a3*b4-d1*a4*b3+d3*b1*a4-d4*b1*a3)*KK_1;     
    C(1,3)=   (   a1*b3*c4-a1*b4*c3+b4*c1*a3-b3*c1*a4-b1*a3*c4+b1*a4*c3)*KK_1;     

    C(2,0)=     (b2*d1*c4-b2*d4*c1+d2*b4*c1-d1*c2*b4-d2*b1*c4+d4*c2*b1)*KK_1;     
    C(2,1)=   -(a1*d4*c2-a1*d2*c4-d4*c1*a2-d1*a4*c2+d2*c1*a4+d1*a2*c4)*KK_1;     
    C(2,2)=   (a1*b2*d4-a1*d2*b4-b2*d1*a4+d2*b1*a4-d4*b1*a2+d1*a2*b4)*KK_1;     
    C(2,3)=-(c4*a1*b2-c4*b1*a2-c1*a4*b2-c2*a1*b4+c2*b1*a4+c1*a2*b4)*KK_1;   

    C(3,0)=-(   b2*d1*c3-b2*d3*c1-d1*c2*b3+d3*c2*b1+d2*b3*c1-d2*b1*c3)*KK_1;     
    C(3,1)=   (-a1*d2*c3+a1*d3*c2+d2*c1*a3-d3*c1*a2-d1*a3*c2+d1*a2*c3)*KK_1;       
    C(3,2)=-(   d3*a1*b2-d3*b1*a2-d1*a3*b2-d2*a1*b3+d2*b1*a3+d1*a2*b3)*KK_1;   
    C(3,3)=   (   c3*a1*b2-c3*b1*a2-c1*a3*b2-c2*a1*b3+c2*b1*a3+c1*a2*b3)*KK_1;   

    return C;
}

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