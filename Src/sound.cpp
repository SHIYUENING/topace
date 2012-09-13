
#include<hgl/platform/SystemInfo.H>
#include <hgl/external.h>
#include <hgl/OpenALEE.h>

#include "sound.h"
#include "MyFont.h"
extern CMyFont MyFont;
bool isinitsound=false;
float Effectvol,Voicevol;
AudioBuffer * missleWarning[MAX_missleWarning];
AudioBuffer * fox2voice[MAX_fox2voice];
AudioBuffer * hitvoice[MAX_hitvoice];
AudioBuffer * killvoice[MAX_killvoice];
AudioBuffer * missvoice[MAX_missvoice];
AudioBuffer * sounds[MAX_sounds];
AudioSource * voiceSource;
AudioSource * voiceSourceLock;
AudioSource * voiceSourceLockOn;
AudioSource * voiceSourceLocked;
AudioSource * voiceSourceGunFire;
AudioSource * voiceSourceAWACS;
AudioSource * soundSource[MAX_soundSource];
Vector3d soundSourcePos[MAX_soundSource];
AudioPlayer * BGMplayer;
tSoundSourceDate SoundSourceDate[MAX_soundSource];
namespace hgl
{
	bool InitCore(SystemInfo &si,bool create_log);			///<初始化核心
}
void initsound()
{
	float BGMvol	=(float)GetPrivateProfileIntA("Sound","BGM",50,".\\set.ini")/100.0f;
	Effectvol	=(float)GetPrivateProfileIntA("Sound","Effect",100,".\\set.ini")/100.0f;
	Voicevol	=(float)GetPrivateProfileIntA("Sound","Voice",100,".\\set.ini")/100.0f;
	hgl::SystemInfo si;
	bool InitOK=false;
	InitOK=hgl::InitCore(si,false);
	if(!InitOK)
		return ;
	InitOK=InitOpenAL((const wchar_t *)0,(const wchar_t *)0);
	//openal::InitOpenALEE();
	BGMplayer= new AudioPlayer;
	BGMplayer->Load(L"Data/bgm.ogg");
	BGMplayer->Gain=BGMvol;
	
	
	//missleWarning[0] = new AudioBuffer;missleWarning[0]->Load(L"Data/voice/missleWarning0.ogg");
	//missleWarning[1] = new AudioBuffer;missleWarning[1]->Load(L"Data/voice/missleWarning1.ogg");
	//missleWarning[2] = new AudioBuffer;missleWarning[2]->Load(L"Data/voice/missleWarning2.ogg");
	//missleWarning[3] = new AudioBuffer;missleWarning[3]->Load(L"Data/voice/missleWarning3.ogg");
	//missleWarning[4] = new AudioBuffer;missleWarning[4]->Load(L"Data/voice/missleWarning4.ogg");
	//missleWarning[5] = new AudioBuffer;missleWarning[5]->Load(L"Data/voice/missleWarning5.ogg");
	//missleWarning[6] = new AudioBuffer;missleWarning[6]->Load(L"Data/voice/missleWarning6.ogg");
	//missleWarning[7] = new AudioBuffer;missleWarning[7]->Load(L"Data/voice/missleWarning7.ogg");
	//missleWarning[8] = new AudioBuffer;missleWarning[8]->Load(L"Data/voice/missleWarning8.ogg");
	//missleWarning[9] = new AudioBuffer;missleWarning[9]->Load(L"Data/voice/missleWarning9.ogg");
	//fox2voice[0] = new AudioBuffer;fox2voice[0]->Load(L"Data/voice/fox20.ogg");
	//fox2voice[1] = new AudioBuffer;fox2voice[1]->Load(L"Data/voice/fox21.ogg");
	//fox2voice[2] = new AudioBuffer;fox2voice[2]->Load(L"Data/voice/fox22.ogg");
	//hitvoice[0] = new AudioBuffer;hitvoice[0]->Load(L"Data/voice/hit0.ogg");
	//hitvoice[1] = new AudioBuffer;hitvoice[1]->Load(L"Data/voice/hit1.ogg");
	//hitvoice[2] = new AudioBuffer;hitvoice[2]->Load(L"Data/voice/hit2.ogg");
	//hitvoice[3] = new AudioBuffer;hitvoice[3]->Load(L"Data/voice/hit3.ogg");
	//killvoice[0] = new AudioBuffer;killvoice[0]->Load(L"Data/voice/kill0.ogg");
	//killvoice[1] = new AudioBuffer;killvoice[1]->Load(L"Data/voice/kill1.ogg");
	//killvoice[2] = new AudioBuffer;killvoice[2]->Load(L"Data/voice/kill2.ogg");
	//killvoice[3] = new AudioBuffer;killvoice[3]->Load(L"Data/voice/kill3.ogg");
	//killvoice[4] = new AudioBuffer;killvoice[4]->Load(L"Data/voice/kill4.ogg");
	//killvoice[5] = new AudioBuffer;killvoice[5]->Load(L"Data/voice/kill5.ogg");
	//killvoice[6] = new AudioBuffer;killvoice[6]->Load(L"Data/voice/kill6.ogg");
	//killvoice[7] = new AudioBuffer;killvoice[7]->Load(L"Data/voice/kill7.ogg");
	//killvoice[8] = new AudioBuffer;killvoice[8]->Load(L"Data/voice/kill8.ogg");
	//killvoice[9] = new AudioBuffer;killvoice[9]->Load(L"Data/voice/kill9.ogg");
	//missvoice[0] = new AudioBuffer;missvoice[0]->Load(L"Data/voice/miss0.ogg");
	//missvoice[1] = new AudioBuffer;missvoice[1]->Load(L"Data/voice/miss1.ogg");
	//missvoice[2] = new AudioBuffer;missvoice[2]->Load(L"Data/voice/miss2.ogg");
	//missvoice[3] = new AudioBuffer;missvoice[3]->Load(L"Data/voice/miss3.ogg");
	sounds[0] = new AudioBuffer;sounds[0]->Load(L"Data/sound/Boom0.ogg");
	sounds[1] = new AudioBuffer;sounds[1]->Load(L"Data/sound/FireMissle.ogg");
	sounds[2] = new AudioBuffer;sounds[2]->Load(L"Data/sound/GunFire.ogg");
	sounds[3] = new AudioBuffer;sounds[3]->Load(L"Data/sound/GunHited.ogg");
	sounds[4] = new AudioBuffer;sounds[4]->Load(L"Data/sound/lock.ogg");
	sounds[5] = new AudioBuffer;sounds[5]->Load(L"Data/sound/locked.ogg");
	sounds[6] = new AudioBuffer;sounds[6]->Load(L"Data/sound/Lockon.ogg");
	voiceSource=new AudioSource;voiceSource->Gain=Voicevol;
	voiceSourceLock=new AudioSource;voiceSourceLock->Link(sounds[4]);voiceSourceLock->Gain=Effectvol;
	voiceSourceLockOn=new AudioSource;voiceSourceLockOn->Link(sounds[6]);voiceSourceLockOn->Gain=Effectvol;
	voiceSourceLocked=new AudioSource;voiceSourceLocked->Link(sounds[5]);voiceSourceLocked->Gain=Effectvol;
	voiceSourceGunFire=new AudioSource;voiceSourceGunFire->Link(sounds[2]);voiceSourceGunFire->Gain=Effectvol;
	voiceSourceAWACS=new AudioSource;voiceSourceAWACS->Gain=Voicevol;
	for(int i=0;i<MAX_soundSource;i++)
	{
		soundSource[i]=new AudioSource;
		soundSource[i]->Gain=Effectvol;
	}

	isinitsound=true;

}
bool AddSound(int Num,const Vector3d& pos)
{
	if((Num<0)||(Num>=MAX_soundSource))
		return false;
	int i=0;
	while(soundSource[i]->State==AL_PLAYING)
	{
		i=i+1;
		if(i>=MAX_soundSource)
			return false;
	}
	soundSourcePos[i]=pos;
	soundSource[i]->Unlink();
	soundSource[i]->Link(sounds[Num]);
	soundSource[i]->Gain=Effectvol;
	soundSource[i]->Play();
	return true;


}
void MoveSound(Transform& would,float LookRenge)
{
	if(!isinitsound)
		return;
	for(int i=0;i<MAX_soundSource;i++)
	{
		if(soundSource[i]->State==AL_PLAYING)
		{
			Vertex3f FirstSoundPoint,lastSoundPoint,SoundVelocity;
			Vector3d Pos3d;
			Pos3d=would.Matrix() * soundSourcePos[i] + would.RefPos();
			FirstSoundPoint=Vertex3f((float)Pos3d(0)/LookRenge,(float)Pos3d(1)/LookRenge,(float)Pos3d(2)/LookRenge);
			lastSoundPoint=soundSource[i]->GetPosition();
			soundSource[i]->SetVelocity(FirstSoundPoint-lastSoundPoint);
			
			soundSource[i]->SetPosition(FirstSoundPoint);
		}
	}

}
void PlaymissleWarning(int Num)
{
	return;
	if((Num<0)||(Num>=MAX_missleWarning))
		return;
	if(missleWarning[Num]->Time<0.001)
		return;
	if(voiceSource->State==AL_PLAYING)
		return;
	voiceSource->Unlink();
	voiceSource->Link(missleWarning[Num]);
	voiceSource->Gain=Voicevol;
	voiceSource->Play();



}
void Playfox2voice(int Num)
{
	return;
	if((Num<0)||(Num>=MAX_fox2voice))
		return;
	if(fox2voice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(fox2voice[Num]);
	voiceSourceAWACS->Gain=Voicevol;
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《ＦＯＸ２！》");
	if(Num==1)
		MyFont.inputTxt("《ＦＯＸ２！ＦＯＸ２！》");
	if(Num==2)
		MyFont.inputTxt("《ＦＯＸ２》");


}
void Playhitvoice(int Num)
{
	return;
	if((Num<0)||(Num>=MAX_hitvoice))
		return;
	if(hitvoice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(hitvoice[Num]);
	voiceSourceAWACS->Gain=Voicevol;
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《导弹命中！》");
	if(Num==1)
		MyFont.inputTxt("《击中目标！》");
	if(Num==2)
		MyFont.inputTxt("《导弹命中！》");
	if(Num==3)
		MyFont.inputTxt("《目标命中！》");

}
void Playkillvoice(int Num)
{
	return;
	if((Num<0)||(Num>=MAX_killvoice))
		return;
	if(killvoice[Num]->Time<0.001)
		return;
	if(voiceSource->State==AL_PLAYING)
		return;
	voiceSource->Unlink();
	voiceSource->Link(killvoice[Num]);
	voiceSource->Gain=Voicevol;
	voiceSource->Play();


}
void Playmissvoice(int Num)
{
	return;
	if((Num<0)||(Num>=MAX_missvoice))
		return;
	if(missvoice[Num]->Time<0.001)
		return;
	if(voiceSourceAWACS->State==AL_PLAYING)
		return;
	voiceSourceAWACS->Unlink();
	voiceSourceAWACS->Link(missvoice[Num]);
	voiceSourceAWACS->Gain=Voicevol;
	voiceSourceAWACS->Play();
	if(Num==0)
		MyFont.inputTxt("《没有命中，被躲开了》");
	if(Num==1)
		MyFont.inputTxt("《ＭＩＳＳ！》");
	if(Num==2)
		MyFont.inputTxt("《导弹丢失目标！》");
	if(Num==3)
		MyFont.inputTxt("《ＭＩＳＳ》");

}
void SoundPause()
{
	if(BGMplayer->Time<0.001)
		return;
	if(BGMplayer->State==AL_PLAYING)
	{
		BGMplayer->Pause();
		return;
	}
	if(BGMplayer->State==AL_PAUSED)
	{
		BGMplayer->Resume();
		return;
	}
}