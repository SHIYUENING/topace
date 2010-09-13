#ifndef HGL_POINTSPRITE_INCLUDE
#define HGL_POINTSPRITE_INCLUDE

#include<hgl/VisualObject.H>
#include<hgl/Vertex3.H>
#include<hgl/Color4f.H>
#include<hgl/DrawArray.H>
namespace hgl
{
	/**
	* 点精灵即OpenGL中point sprite扩展的一种封装，在没有硬件支持的情况下仅画出点来<br>
	* 同时粒子系统也会通过点精灵来绘制
	*/
	class PointSprite:public VisualObject                                                           ///点精灵类
	{
		int MaxCount;
		float size;

		float GetSize(){return size;}
		void SetSize(float);

	public:

		float			Fade;                                                                       ///<开始衰退
		Property<float>	Size;                                                                       ///<点大小

		DrawArray *		Array;																			///<数据阵列

	public:

		PointSprite(int,uint=pdcVertex2f|pdcColor4f,float=1,float=64);                              ///<本类构造函数
		virtual ~PointSprite();                                                                     ///<本类析构函数

		virtual void Draw(int,int);                                                                 ///<绘制部分点精灵
				void Draw();																		///<绘制所有点精灵
	};
}//namespace hgl
#endif//HGL_POINTSPRITE_INCLUDE
