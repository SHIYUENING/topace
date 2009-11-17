#include "Transform.h"


Transform::Transform(){
    m = identity<Matrix33d>();
    p = 0;
    RefreshM4();
}

Transform::Transform(const Matrix33d& Matrix, const Vector3d& RefPos){
    m = Matrix;
    p = RefPos;
    RefreshM4();
}


Transform::Transform(const Matrix33d& Matrix){
    m = Matrix;
    p = 0;
    RefreshM4();
}


Transform::Transform(const Vector3d& RefPos){
    m = identity<Matrix33d>();
    p = RefPos;
    RefreshM4();
}
void Transform::Reset(){
    m = identity<Matrix33d>();
    p = 0;
    RefreshM4();
}


const Matrix33d& Transform::Matrix() const{
    return m;
}

const Vector3d& Transform::RefPos() const{
    return p;
}

const double* Transform::Matrix4() const{
    return m4.data();
}

void Transform::Rotate(const Vector3d& externalTheta){
    double theta = norm2(externalTheta);
    if (theta == 0){ return; }
    Vector3d z;
    z = externalTheta / theta;

    Vector3d x;
    Vector3d y;
    if (all_elements(z == Vector3d(0, 0, 1))){
        x = 1, 0, 0;
        y = 0, 1, 0;
}
    else if (all_elements(z == Vector3d(0, 0, -1))){
        x = 1, 0, 0;
        y = 0, -1, 0;
}
    else{
        x = normalize(cross(z));
        y = normalize(cross(z, x));
}

    Matrix33d Mu;
    Mu = x(0), y(0), z(0),
         x(1), y(1), z(1),
         x(2), y(2), z(2);

    Matrix33d Rho;
    Rho = cos(theta), -sin(theta), 0,
         sin(theta),  cos(theta), 0,
               0,        0, 1;

    m = Mu * Rho * trans(Mu) * Matrix33d(m); 
    RefreshM4();
}



void Transform::RotateInternal(const Vector3d& internalTheta){
    double theta = norm2(internalTheta);
    if (theta == 0){ return; }
    Vector3d z;
    z = internalTheta / theta;

    Vector3d x;
    Vector3d y;
    if (all_elements(z == Vector3d(0, 0, 1))){
        x = 1, 0, 0;
        y = 0, 1, 0;
}
    else if (all_elements(z == Vector3d(0, 0, -1))){
        x = 1, 0, 0;
        y = 0, -1, 0;
}
    else{
        x = normalize(cross(z));
        y = normalize(cross(z, x));
}

    Matrix33d Mu;
    Mu = x(0), y(0), z(0),
         x(1), y(1), z(1),
         x(2), y(2), z(2);

    Matrix33d Rho;
    Rho = cos(theta), -sin(theta), 0,
          sin(theta),  cos(theta), 0,
                   0,           0, 1;

    m = Matrix33d(m) * Mu * Rho * trans(Mu); 
    RefreshM4();
}



void Transform::Translate(const Vector3d& externalReplacement){
    p += externalReplacement;
    RefreshM4();
}



void Transform::TranslateInternal(const Vector3d& internalReplacement){
    p += m * internalReplacement;
    RefreshM4();
}


Transform Transform::Invert() const{
    return Transform(trans(m), -(trans(m) * p));
}


void Transform::RefreshM4(){
    m4 = m(0, 0), m(1, 0), m(2, 0), 0,
         m(0, 1), m(1, 1), m(2, 1), 0,
         m(0, 2), m(1, 2), m(2, 2), 0,
            p(0),    p(1),    p(2), 1;
}

Transform operator*(const Transform& lhs, const Transform& rhs){
    return Transform(lhs.Matrix() * rhs.Matrix(), lhs.RefPos() + rhs.RefPos());
}
