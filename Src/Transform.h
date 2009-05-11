#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Mathematics.h"

///<summary>合同变换(正交变换)</summary>
class Transform{
private:
    Matrix33d m;
    Vector3d p;
    Matrix44d m4;
public:
    Transform();

    Transform(const Matrix33d& Matrix, const Vector3d& RefPos);

    template<class E1, class E2>
    Transform(const XprMatrix<E1, 3, 3>& Matrix, const XprVector<E2, 3>& RefPos){
        m = Matrix;
        p = RefPos;
        RefreshM4();
    }

    template<class E>
    Transform(const Matrix33d& Matrix, const XprVector<E, 3>& RefPos){
        m = Matrix;
        p = RefPos;
        RefreshM4();
    }

    template<class E>
    Transform(const XprMatrix<E, 3, 3>& Matrix, const Vector3d& RefPos){
        m = Matrix;
        p = RefPos;
        RefreshM4();
    }

    Transform(const Matrix33d& Matrix);

    template<class E>
    Transform(const XprMatrix<E, 3, 3>& Matrix){
        m = Matrix;
        p = 0;
        RefreshM4();
    }

    Transform(const Vector3d& RefPos);

    template<class E>
    Transform(const XprVector<E, 3>& RefPos){
        m = identity<Matrix33d>();
        p = RefPos;
        RefreshM4();
    }

    ///<summary>变换的旋转矩阵</summary>
    const Matrix33d& Matrix()const;

    ///<summary>变换的参考点</summary>
    const Vector3d& RefPos()const;

    ///<summary>变换矩阵(4维)</summary>
    const double* Matrix4()const;

    ///<summary>按外部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
    void Rotate(const Vector3d& externalTheta);

    ///<summary>按外部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
    template<class E>
    void Rotate(const XprVector<E, 3>& externalTheta){
        Rotate(Vector3d(externalTheta));
    }

    ///<summary>按内部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
    void RotateInternal(const Vector3d& internalTheta);

    ///<summary>按内部坐标系旋转角向量旋转(以其方向为轴，大小为旋转角)</summary>
    template<class E>
    void RotateInternal(const XprVector<E, 3>& internalTheta){
        RotateInternal(Vector3d(internalTheta));
    }

    ///<summary>将内部坐标系的一个方向，转向外部坐标系的一个点，且按最小弧来进行转动</summary>
    void TurnTo(const Vector3d& internalSourceDirection, const Vector3d& externalTargetPosition);

    ///<summary>将内部坐标系的一个方向，转向外部坐标系的一个点，且按最小弧来进行转动</summary>
    template<class E>
    void TurnTo(const XprVector<E, 3>& internalSourceDirection, const XprVector<E, 3>& externalTargetPosition){
        TurnTo(Vector3d(internalSourceDirection), Vector3d(externalTargetPosition));
    }

    ///<summary>按外部向量平移</summary>
    void Translate(const Vector3d& externalReplacement);

    ///<summary>按外部向量平移</summary>
    template<class E>
    void Translate(const XprVector<E, 3>& externalReplacement){
        p += externalReplacement;
        RefreshM4();
    }

    ///<summary>按内部向量平移</summary>
    void TranslateInternal(const Vector3d& internalReplacement);

    ///<summary>按内部平移</summary>
    template<class E>
    void TranslateInternal(const XprVector<E, 3>& internalReplacement){
        p += m * internalReplacement;
        RefreshM4();
    }

    Transform Invert()const;
	void Reset();

private:
    void RefreshM4();
};

Transform operator*(const Transform& lhs, const Transform& rhs);
#endif
