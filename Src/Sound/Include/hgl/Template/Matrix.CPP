#ifndef HGL_MATRIX_CPP
#define HGL_MATRIX_CPP

#include<hgl/Matrix.H>
#include<string.h>

namespace hgl
{
	template<typename T> void __inline LoadIdentity(T *m)
	{
		/**
		 * Identity matrix.
		 */
		const T Identity[16] = {
		   1.0, 0.0, 0.0, 0.0,
		   0.0, 1.0, 0.0, 0.0,
		   0.0, 0.0, 1.0, 0.0,
		   0.0, 0.0, 0.0, 1.0
		};

		hgl_memcpy(m,Identity,16*sizeof(T));
	}

	/**********************************************************************/
	/** \name Matrix multiplication */
	/*@{*/

	#define A(row,col)  a[(col<<2)+row]
	#define B(row,col)  b[(col<<2)+row]
	#define P(row,col)  product[(col<<2)+row]

	/**
	 * Perform a full 4x4 matrix multiplication.
	 *
	 * \param a matrix.
	 * \param b matrix.
	 * \param product will receive the product of \p a and \p b.
	 *
	 * \warning Is assumed that \p product != \p b. \p product == \p a is allowed.
	 *
	 * \note KW: 4*16 = 64 multiplications
	 *
	 * \author This \c matmul was contributed by Thomas Malik
	 */
	template<typename T> void __inline matmul4( T *product, const T *a, const T *b )
	{
	   int i;
	   for (i = 0; i < 4; i++) {
		  const T ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		  P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		  P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		  P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		  P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	   }
	}

	#undef A
	#undef B
	#undef P

	template<typename T>
	Matrix<T>::Matrix()
	{
		LoadIdentity();
	}

	template<typename T>
	Matrix<T>::Matrix(	float m0,float m1,float m2,float m3,
						float m4,float m5,float m6,float m7,
						float m8,float m9,float ma,float mb,
						float mc,float md,float me,float mf)
	{
		m[ 0]=m0;m[ 1]=m1;m[ 2]=m2;m[ 3]=m3;
		m[ 4]=m4;m[ 5]=m5;m[ 6]=m6;m[ 7]=m7;
		m[ 8]=m8;m[ 9]=m9;m[10]=ma;m[11]=mb;
		m[12]=mc;m[13]=md;m[14]=me;m[15]=mf;
	}

	/**
	* 加载缺省矩阵
	*/
	template<typename T>
	void Matrix<T>::LoadIdentity()
	{
		hgl::LoadIdentity<T>(m);
	}

	/**
	* 缩放
	*/
	template<typename T>
	void Matrix<T>::Scale(T x,T y,T z)
	{
	   m[0] *= x;   m[4] *= y;   m[8]  *= z;
	   m[1] *= x;   m[5] *= y;   m[9]  *= z;
	   m[2] *= x;   m[6] *= y;   m[10] *= z;
	   m[3] *= x;   m[7] *= y;   m[11] *= z;
	}

	/**
	* 旋转
	* @param angle 角度
	*/
	template<typename T>
	void Matrix<T>::Rotate(T angle,T x,T y,T z)
	{
		T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
		T rm[16];
		double s,c;
		bool optimized;

		fm_sincos(angle*M_PI/180.0f,&s,&c);

		hgl::LoadIdentity<T>(rm);

		optimized = false;

		#define M(row,col)  rm[(col<<2)+row]

		if (x == 0.0F) 
		{
			if (y == 0.0F) 
			{
				if (z != 0.0F) 
				{
					optimized = true;
					/* rotate only around z-axis */
					M(0,0) = c;
					M(1,1) = c;

					if (z < 0.0F) 
					{
						M(0,1) = s;
						M(1,0) = -s;
					}
					else 
					{
						M(0,1) = -s;
						M(1,0) = s;
					}
				}
			}
			else if (z == 0.0F) 
			{
				optimized = true;
				/* rotate only around y-axis */
				M(0,0) = c;
				M(2,2) = c;
				if (y < 0.0F) 
				{
					M(0,2) = -s;
					M(2,0) = s;
				}
				else 
				{
					M(0,2) = s;
					M(2,0) = -s;
				}
			}
		}
		else if (y == 0.0F) 
		{
			if (z == 0.0F) 
			{
				optimized = true;
				/* rotate only around x-axis */
				M(1,1) = c;
				M(2,2) = c;

				if (x < 0.0F) 
				{
					M(1,2) = s;
					M(2,1) = -s;
				}
				else 
				{
					M(1,2) = -s;
					M(2,1) = s;
				}
			}
		}

		if (!optimized) 
		{
			const T mag = fm_sqrt(x * x + y * y + z * z);

			if (mag <= 1.0e-4) 
			{
				/* no rotation, leave mat as-is */
				return;
			}

			x /= mag;
			y /= mag;
			z /= mag;


			/*
			*     Arbitrary axis rotation matrix.
			*
			*  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
			*  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
			*  (which is about the X-axis), and the two composite transforms
			*  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
			*  from the arbitrary axis to the X-axis then back.  They are
			*  all elementary rotations.
			*
			*  Rz' is a rotation about the Z-axis, to bring the axis vector
			*  into the x-z plane.  Then Ry' is applied, rotating about the
			*  Y-axis to bring the axis vector parallel with the X-axis.  The
			*  rotation about the X-axis is then performed.  Ry and Rz are
			*  simply the respective inverse transforms to bring the arbitrary
			*  axis back to it's original orientation.  The first transforms
			*  Rz' and Ry' are considered inverses, since the data from the
			*  arbitrary axis gives you info on how to get to it, not how
			*  to get away from it, and an inverse must be applied.
			*
			*  The basic calculation used is to recognize that the arbitrary
			*  axis vector (x, y, z), since it is of unit length, actually
			*  represents the sines and cosines of the angles to rotate the
			*  X-axis to the same orientation, with theta being the angle about
			*  Z and phi the angle about Y (in the order described above)
			*  as follows:
			*
			*  fm_cos ( theta ) = x / fm_sqrt ( 1 - z^2 )
			*  fm_sin ( theta ) = y / fm_sqrt ( 1 - z^2 )
			*
			*  fm_cos ( phi ) = fm_sqrt ( 1 - z^2 )
			*  fm_sin ( phi ) = z
			*
			*  Note that fm_cos ( phi ) can further be inserted to the above
			*  formulas:
			*
			*  fm_cos ( theta ) = x / fm_cos ( phi )
			*  fm_sin ( theta ) = y / fm_sin ( phi )
			*
			*  ...etc.  Because of those relations and the standard trigonometric
			*  relations, it is pssible to reduce the transforms down to what
			*  is used below.  It may be that any primary axis chosen will give the
			*  same results (modulo a sign convention) using thie method.
			*
			*  Particularly nice is to notice that all divisions that might
			*  have caused trouble when parallel to certain planes or
			*  axis go away with care paid to reducing the expressions.
			*  After checking, it does perform correctly under all cases, since
			*  in all the cases of division where the denominator would have
			*  been zero, the numerator would have been zero as well, giving
			*  the expected result.
			*/

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * s;
			ys = y * s;
			zs = z * s;
			one_c = 1.0F - c;

			/* We already hold the identity-matrix so we can skip some statements */
			M(0,0) = (one_c * xx) + c;
			M(0,1) = (one_c * xy) - zs;
			M(0,2) = (one_c * zx) + ys;
			/*    M(0,3) = 0.0F; */

			M(1,0) = (one_c * xy) + zs;
			M(1,1) = (one_c * yy) + c;
			M(1,2) = (one_c * yz) - xs;
			/*    M(1,3) = 0.0F; */

			M(2,0) = (one_c * zx) - ys;
			M(2,1) = (one_c * yz) + xs;
			M(2,2) = (one_c * zz) + c;
			/*    M(2,3) = 0.0F; */

			/*
			M(3,0) = 0.0F;
			M(3,1) = 0.0F;
			M(3,2) = 0.0F;
			M(3,3) = 1.0F;
			*/
		}
		#undef M

		matmul4<T>(m,m,rm);
	}

	/**
	* 移动
	*/
	template<typename T>
	void Matrix<T>::Translate(T x,T y,T z)
	{
	   m[12] = m[0] * x + m[4] * y + m[8]  * z + m[12];
	   m[13] = m[1] * x + m[5] * y + m[9]  * z + m[13];
	   m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
	   m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
	}

	template<typename T>
	void Matrix<T>::Transpose(const Matrix<T> &src)
	{
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				m[(j*4)+i] = src[(i*4)+j];
	}

	template<typename T>
	void Matrix<T>::Transpose()
	{
		Matrix<T> tmp=*this;

		Transpose(tmp);
	}

	/**
	* 产生当前矩阵的相反矩阵
	* @return 是否反转成功
	*/
	template<typename T>
	bool Matrix<T>::CreateInvert(const Matrix<T> &inv)
	{
	#define FABSF(v)		(v>0?v:-v)
	#define MAT(m,row,col) 	(m)[(col<<2)+row]
	#define SWAP_ROWS(a, b) { T *_tmp = a; (a)=(b); (b)=_tmp; }
		const T *in = m;
		T *out = inv.m;
		T wtmp[4][8];
		T m0, m1, m2, m3, s;
		T *r0, *r1, *r2, *r3;

		r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

		r0[0] = MAT(in,0,0), r0[1] = MAT(in,0,1),
		r0[2] = MAT(in,0,2), r0[3] = MAT(in,0,3),
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

		r1[0] = MAT(in,1,0), r1[1] = MAT(in,1,1),
		r1[2] = MAT(in,1,2), r1[3] = MAT(in,1,3),
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

		r2[0] = MAT(in,2,0), r2[1] = MAT(in,2,1),
		r2[2] = MAT(in,2,2), r2[3] = MAT(in,2,3),
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

		r3[0] = MAT(in,3,0), r3[1] = MAT(in,3,1),
		r3[2] = MAT(in,3,2), r3[3] = MAT(in,3,3),
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

		/* choose pivot - or die */
		if (FABSF(r3[0])>FABSF(r2[0])) SWAP_ROWS(r3, r2);
		if (FABSF(r2[0])>FABSF(r1[0])) SWAP_ROWS(r2, r1);
		if (FABSF(r1[0])>FABSF(r0[0])) SWAP_ROWS(r1, r0);
		if (0.0 == r0[0])  return false;

		/* eliminate first variable     */
		m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
		s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
		s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
		s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
		s = r0[4];
		if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r0[5];
		if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r0[6];
		if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r0[7];
		if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (FABSF(r3[1])>FABSF(r2[1])) SWAP_ROWS(r3, r2);
		if (FABSF(r2[1])>FABSF(r1[1])) SWAP_ROWS(r2, r1);
		if (0.0 == r1[1])  return false;

		/* eliminate second variable */
		m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
		r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
		r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
		s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (FABSF(r3[2])>FABSF(r2[2])) SWAP_ROWS(r3, r2);
		if (0.0 == r2[2])  return false;

		/* eliminate third variable */
		m3 = r3[2]/r2[2];
		r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

		/* last check */
		if (0.0 == r3[3]) return false;

		s = 1.0F/r3[3];             /* now back substitute row 3 */
		r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

		m2 = r2[3];                 /* now back substitute row 2 */
		s  = 1.0F/r2[2];
		r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
		m1 = r1[3];
		r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
		m0 = r0[3];
		r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

		m1 = r1[2];                 /* now back substitute row 1 */
		s  = 1.0F/r1[1];
		r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
		m0 = r0[2];
		r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

		m0 = r0[1];                 /* now back substitute row 0 */
		s  = 1.0F/r0[0];
		r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

		MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
		MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
		MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
		MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
		MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
		MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
		MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
		MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

		return true;
	#undef SWAP_ROWS
	#undef MAT
	#undef FABSF
	}

	template<typename T>
	int Matrix<T>::Comp(const Matrix<T> &v)const
    {
        return memcmp(this,&v,sizeof(Matrix<T>));
    }

	template<typename T>
	Matrix<T> &Matrix<T>::operator =(const Matrix<T> &mat)
	{
		hgl_memcpy(this,&mat,sizeof(Matrix<T>));

		return *this;
	}

	template<typename T>
	Matrix<T> &Matrix<T>::operator *=(const Matrix<T> &mat)
	{
		Matrix<T> tmp=*this;

		matmul4<T>(m,tmp.m,mat.m);

		return *this;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator *(const Matrix<T> &mat) const
	{
		Matrix<T> result;

    	matmul4<T>(result.m,m,mat.m);

		return result;
	}
}//namespace hgl
#endif//HGL_MATRIX_CPP
