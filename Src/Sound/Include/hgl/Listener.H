#ifndef HGL_LISTENER_INCLUDE
#define HGL_LISTENER_INCLUDE

#include<hgl/Vertex3.H>
namespace hgl
{
	/**
	* 这个类用于管理收听者的一些状态，可以通过它设定统一的音量，收听者的位置、方向等
	*/
	class AudioListener                                                                             ///收听者管理类
	{
	protected:

		float gain;
		Vertex3f position;
		Vertex3f velocity;
		Vertex3f *orientation;

	public:	//属性方法

		float GetGain(){return gain;}                                                               ///<读取音量增益幅度
		const Vertex3f &GetPosition(){return position;}                                             ///<读取音源坐标位置
		const Vertex3f &GetVelocity(){return velocity;}                                             ///<读取速率
		const Vertex3f *GetOrientation(){return orientation;}                                       ///<读取导向

		void SetGain(float);                                                                        ///<设置音量增益幅度
		void SetPosition(const Vertex3f &);                                                         ///<设置音源坐标位置
		void SetVelocity(const Vertex3f &);                                                         ///<设置速率
		void SetOrientation(const Vertex3f *);                                                      ///<设置导向

	public: //方法

		AudioListener();
		~AudioListener();
	};
}

#endif//HGL_LISTENER_INCLUDE