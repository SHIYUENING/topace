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


///<summary>变换的旋转矩阵</summary>
const Matrix33d& Transform::Matrix() const{
    return m;
}

///<summary>变换的参考点</summary>
const Vector3d& Transform::RefPos() const{
    return p;
}

///<summary>变换矩阵(4维)</summary>
const double* Transform::Matrix4() const{
    return m4.data();
}

///<summary>按外部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
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

    m = Mu * Rho * trans(Mu) * Matrix33d(m); //注意：不应在等式左右同时直接出现一个矩阵或向量，必须先拷贝为临时变量，否则会计算出错。

    RefreshM4();
}



///<summary>按内部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
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

    m = Matrix33d(m) * Mu * Rho * trans(Mu); //注意：不应在等式左右同时直接出现一个矩阵或向量，必须先拷贝为临时变量，否则会计算出错。

    RefreshM4();
}

///<summary>将内部坐标系的一个方向，转向外部坐标系的一个点，且按最小弧来进行转动</summary>
void Transform::TurnTo(const Vector3d& internalSourceDirection, const Vector3d& externalTargetPosition){
    Vector3d current;
    current = m * internalSourceDirection;
    if (all_elements(current == 0)){ return; }
    current = normalize(current);

    Vector3d target;
    target = externalTargetPosition - p;
    if (all_elements(target == 0)){ return; }
    target = normalize(target);

    double k = dot(current, target);

    Vector3d rotateAxis;
    rotateAxis = cross(current, target);
    if (all_elements(rotateAxis == 0)){ return; }
    rotateAxis = normalize(rotateAxis);

    double rotateAngle = acos_s(dot(current, target));
    Rotate(rotateAxis * rotateAngle);
}

///<summary>按外部向量平移</summary>
void Transform::Translate(const Vector3d& externalReplacement){
    p += externalReplacement;
    RefreshM4();
}



///<summary>按内部向量平移</summary>
void Transform::TranslateInternal(const Vector3d& internalReplacement){
    p += m * internalReplacement;
    RefreshM4();
}


Transform Transform::Invert() const{
    return Transform(trans(m), -(trans(m) * p));
}


void Transform::RefreshM4(){
    //注意到tvmet与OpenGL的数据存储优先格式相反
    m4 = m(0, 0), m(1, 0), m(2, 0), 0,
         m(0, 1), m(1, 1), m(2, 1), 0,
         m(0, 2), m(1, 2), m(2, 2), 0,
            p(0),    p(1),    p(2), 1;
}

Transform operator*(const Transform& lhs, const Transform& rhs){
    return Transform(lhs.Matrix() * rhs.Matrix(), lhs.RefPos() + rhs.RefPos());
}
