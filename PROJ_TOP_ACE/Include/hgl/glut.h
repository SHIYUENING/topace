#ifndef HGL_GLUT_INCLUDE
#define HGL_GLUT_INCLUDE

#include<hgl/opengl.h>
namespace hgl
{
	/**
	* 这里复制了GLUT中所提供的一些绘图函数，以方便程序开发中的移植工作。
	* 代码取自FreeGLUT、GLTools
	*/
	namespace glut                      ///glut函数名字空间
	{
		void WireCube(GLdouble);                                                                    //画线框立方体
		void WireSphere(GLdouble,GLint,GLint);                                                      //画线框球体
		void WireCone(GLdouble,GLdouble,GLint,GLint);                                               //画线框圆锥体
		void WireCylinder(GLdouble,GLdouble,GLint,GLint);                                           //画线框圆柱体
		void WireTorus(GLdouble,GLdouble,GLint,GLint);                                              //画线框圆环
		void WireDodecahedron();                                                                    //画线框正十二面体,半径是3的平方根
		void WireOctahedron();                                                                      //画线框正八面体,半径是1
		void WireTetrahedron();                                                                     //画线框正四面体,半径是3的平方根
		void WireIcosahedron();                                                                     //画线框的正二十面体，半径是1
		void WireRhombicDodecahedron();                                                             //画线框斜十二面体
		void WireSierpinskiSponge (int,GLdouble offset[3],GLdouble);                                //画线框Sierpinski海绵体
		void WireTeapot(GLdouble,int=8);                                                            //画线框茶壶

		void SolidCube(GLdouble);                                                                   //画实线立方体
		void SolidSphere(GLdouble,GLint,GLint);                                                     //画实心球体
		void SolidCone(GLdouble,GLdouble,GLint,GLint);                                              //画实心圆锥体
		void SolidCylinder(GLdouble,GLdouble,GLint,GLint);                                          //画实心圆柱体
		void SolidTorus(GLdouble,GLdouble,GLint,GLint);                                             //画实心圆环
		void SolidDodecahedron();                                                                   //画实心正十二面体,半径是3的平方根
		void SolidOctahedron();                                                                     //画实心正八面体,半径是1
		void SolidTetrahedron();                                                                    //画实心正四面体,半径是3的平方根
		void SolidIcosahedron();                                                                    //画实心的正二十面体，半径是1
		void SolidRhombicDodecahedron();                                                            //画实心斜十二面体
		void SolidSierpinskiSponge(int,GLdouble offset[3],GLdouble);                                //画实心Sierpinski海绵体
		void SolidTeapot(GLdouble,int=8);                                                           //画实心茶壶

		void DrawUnitAxes();																		//绘制坐标轴
	}//namespace glut
}//namespace hgl
#endif//HGL_GLUT_INCLUDE
