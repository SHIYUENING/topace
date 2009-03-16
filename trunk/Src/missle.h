//#pragma once
#ifndef _MISSLE_H
#define _MISSLE_H
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#define MAXMISSLESMOKE 150
extern CLoadVBMD *m_VBMD;//VBMD模型对象
extern tModelID ModelID[100];
class Missledata
{
public:
	Transform UDMplane;//导弹矩阵
	RigidBody UDPstate;//导弹运动学状态
	int UDlife;//生命值，-1表示不存在，0表示已经被灭
	int UDMissleType;//导弹种类
	int TGTnum;//目标单位编号
	/*
	float UDposx[MAXMISSLESMOKE];//尾烟粒子坐标x
	float UDposy[MAXMISSLESMOKE];//尾烟粒子坐标y
	float UDposz[MAXMISSLESMOKE];//尾烟粒子坐标z
	float UDposxMove[MAXMISSLESMOKE];//尾烟粒子坐标x
	float UDposyMove[MAXMISSLESMOKE];//尾烟粒子坐标y
	float UDposzMove[MAXMISSLESMOKE];//尾烟粒子坐标z
	float UDposzSIZE[MAXMISSLESMOKE];//尾烟粒子大小
	float UDposxF[MAXMISSLESMOKE];//尾烟粒子坐标x
	float UDposyF[MAXMISSLESMOKE];//尾烟粒子坐标y
	float UDposzF[MAXMISSLESMOKE];//尾烟粒子坐标z
	*/
	float UDwinl;//相对玩家的距离，UDwinz（屏幕坐标深度）为负数的时候此值无效
	float UDwinx;//屏幕坐标x
	float UDwiny;//屏幕坐标y
	float UDwinz;//屏幕坐标深度
	//int smokeNum[MAXMISSLESMOKE];//尾烟纹理编号
	int UDposflag;//标示目前被变更的坐标
	int UDposflagF;//标示目前被变更的坐标
	int smokeTime;//被消灭后烟雾残留时间
	int timer;

public:
	Missledata(void);
	~Missledata(void);
    void Missledata::TurnTo(const Vector3d& Position);
	//void setpos(int smokeN=0);
	//void setposF(void);
	void m_Draw(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge);
	/*
	void m_DrawSmoke(
		int m_winwidth,
		int m_winheight,
		int i,
		float& SmokePosX,
		float& SmokePosY,
		float& SmokePosZ,
		float& SmokeAlpha,
		float& SmokeMAlpha);

*/
	

};
#endif