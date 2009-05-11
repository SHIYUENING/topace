#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Mathematics.h"

///<summary>��ͬ�任(�����任)</summary>
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

    ///<summary>�任����ת����</summary>
    const Matrix33d& Matrix()const;

    ///<summary>�任�Ĳο���</summary>
    const Vector3d& RefPos()const;

    ///<summary>�任����(4ά)</summary>
    const double* Matrix4()const;

    ///<summary>���ⲿ����ϵ��ת��������ת(���䷽��Ϊ�ᣬ��СΪ��ת��)</summary>
    void Rotate(const Vector3d& externalTheta);

    ///<summary>���ⲿ����ϵ��ת��������ת(���䷽��Ϊ�ᣬ��СΪ��ת��)</summary>
    template<class E>
    void Rotate(const XprVector<E, 3>& externalTheta){
        Rotate(Vector3d(externalTheta));
    }

    ///<summary>���ڲ�����ϵ��ת��������ת(���䷽��Ϊ�ᣬ��СΪ��ת��)</summary>
    void RotateInternal(const Vector3d& internalTheta);

    ///<summary>���ڲ�����ϵ��ת��������ת(���䷽��Ϊ�ᣬ��СΪ��ת��)</summary>
    template<class E>
    void RotateInternal(const XprVector<E, 3>& internalTheta){
        RotateInternal(Vector3d(internalTheta));
    }

    ///<summary>���ڲ�����ϵ��һ������ת���ⲿ����ϵ��һ���㣬�Ұ���С��������ת��</summary>
    void TurnTo(const Vector3d& internalSourceDirection, const Vector3d& externalTargetPosition);

    ///<summary>���ڲ�����ϵ��һ������ת���ⲿ����ϵ��һ���㣬�Ұ���С��������ת��</summary>
    template<class E>
    void TurnTo(const XprVector<E, 3>& internalSourceDirection, const XprVector<E, 3>& externalTargetPosition){
        TurnTo(Vector3d(internalSourceDirection), Vector3d(externalTargetPosition));
    }

    ///<summary>���ⲿ����ƽ��</summary>
    void Translate(const Vector3d& externalReplacement);

    ///<summary>���ⲿ����ƽ��</summary>
    template<class E>
    void Translate(const XprVector<E, 3>& externalReplacement){
        p += externalReplacement;
        RefreshM4();
    }

    ///<summary>���ڲ�����ƽ��</summary>
    void TranslateInternal(const Vector3d& internalReplacement);

    ///<summary>���ڲ�ƽ��</summary>
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
