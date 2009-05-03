#ifndef AUDIO_PLAYERINCLUDE
#define AUDIO_PLAYERINCLUDE

#include<hgl/HAC.H>
#include<hgl/OpenAL.H>
#include<hgl/Thread.H>
#include<hgl/AudioSource.H>
using namespace openal;
namespace hgl
{
	struct AudioPlugInInterface;

    /**
    * 使用AudioPlayer创建的音频播放器类，一般用于背景音乐等独占的音频处理。
    * 这个音频播放器将使用一个单独的线程，在播放器被删除时线程也会被关闭。
    */
    class AudioPlayer:public Thread                                                                 ///音频播放器基类
    {
        #include<hgl/AudioPlayer.Attrib.H>

	public: //属性
                                         
		Property<uint>		Index;                                                          		///<音源索引
		Property<double>	Time;                                                           		///<音频总时间

		Property<int>		State;                                                          		///<音源状态
		Property<float>		MinGain;                                                        		///<最小增益
		Property<float>		MaxGain;                                                        		///<最大增益

		Property<bool>		Loop;                                                           		///<是否循环播放虚拟变量

		Property<float>		Pitch;                                                          		///<播放频率
		Property<float>		Gain;                                                           		///<音量增益幅度
		Property<float>		ConeGain;                                                       		///<

		Property<float>		RolloffFactor;                                                  		///<

	public:	//属性方法

		const Vertex3f &		GetPosition(){return audiosource.position;} const
		void            		SetPosition(const Vertex3f &pos){audiosource.SetPosition(pos);}

		const Vertex3f &		GetVelocity(){return audiosource.velocity;} const
		void            		SetVelocity(const Vertex3f &vel){audiosource.SetVelocity(vel);}

		const Vertex3f &		GetDirection(){return audiosource.direction;} const
		void            		SetDirection(const Vertex3f &dir){audiosource.SetDirection(dir);}

		const ReferenceValue & 	GetDistance(){return audiosource.distance;} const
		void            		SetDistance(const ReferenceValue &rv){audiosource.SetDistance(rv);}

		const ConeAngle &      	GetAngle(){return audiosource.angle;} const
		void            		SetAngle(const ConeAngle &ca){audiosource.SetAngle(ca);}

	public:	//方法

		AudioPlayer();
		AudioPlayer(Stream *,AFT);
		AudioPlayer(const wchar_t *,AFT=aftNone);
		AudioPlayer(HAC *,const wchar_t *,AFT=aftNone);
        virtual ~AudioPlayer();

		virtual bool Load(Stream *,AFT);                                                  			///<从流中加载一个音频文件
		virtual bool Load(const wchar_t *,AFT=aftNone);                                             ///<加载一个音频文件
		virtual bool Load(HAC *,const wchar_t *,AFT=aftNone);										///<从HAC包中加载一个音频文件

        virtual void Play(bool=true);                                                               ///<播放音频
        virtual void Stop();                                                                        ///<停止播放
        virtual void Pause();                                                                       ///<暂停播放
        virtual void Rewind();                                                                      ///<继续播放
		virtual void Clear();                                                                       ///<清除音频数据

		virtual double GetPlayTime();																///<取得已播放时间(单位秒)

		virtual void AutoGain(float,double);														///<自动音量
	};
}

#endif//AUDIO_PLAYERINCLUDE
