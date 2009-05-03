#ifndef HGL_AUDIOSOURCE_INCLUDE
#define HGL_AUDIOSOURCE_INCLUDE

#include<hgl/Vertex3.H>
#include<hgl/ConeAngle.H>
#include<hgl/ReferenceValue.H>
#include<hgl/AudioBuffer.H>

namespace hgl
{
	/**
	* 音频源，指的是一个发声源，要发声必须创建至少一个发声源。而这个类就是管理发声源所用的。
	*/
	class AudioSource                                                                       ///音频源类
	{
		#include<hgl/AudioSource.Attrib.H>

	public: //属性

		Property<uint>		Index;

		Property<double>	CurTime;														///<当前播放到的时间

		Property<int>		State;                                                          ///<音源状态
		Property<float>		MinGain;                                                        ///<最小增益
		Property<float>		MaxGain;                                                        ///<最大增益

		Property<bool>		Loop;                                                           ///<是否循环播放虚拟变量

		Property<float>		Pitch;                                                          ///<播放频率
		Property<float>		Gain;                                                           ///<音量增益幅度
		Property<float>		ConeGain;                                                       ///<

		Property<float>		RolloffFactor;                                                  ///<

	public:	//属性方法

		const Vertex3f &GetPosition(){return position;}
		const Vertex3f &GetVelocity(){return velocity;}
		const Vertex3f &GetDirection(){return direction;}

		const ReferenceValue &GetDistance(){return distance;}
		const ConeAngle &GetAngle(){return angle;}

		void SetPosition(const Vertex3f &);
		void SetVelocity(const Vertex3f &);
		void SetDirection(const Vertex3f &);
		void SetDistance(const ReferenceValue &);
		void SetAngle(const ConeAngle &);

	public: //方法

		AudioSource(bool=false);                                                                    ///<本类构造函数
		AudioSource(AudioBuffer *);																	///<本类构造函数
		virtual ~AudioSource();                                                                     ///<本类析构函数

		virtual bool Play(bool=false);                                                              ///<播放当前音源
		virtual void Pause();                                                                       ///<暂停/继续播放
		virtual void Stop();                                                                        ///<停止播放
		virtual void Rewind();                                                                      ///<重绕播放

		virtual bool Create();                                                                      ///<创建音源
		virtual void Close();                                                                       ///<关闭音源

		bool Link(AudioBuffer *);                                                                   ///<绑定一个音频缓冲区
		void Unlink();                                                                              ///<解除绑定
	};
}

#endif//HGL_AUDIOSOURCE_INCLUDE