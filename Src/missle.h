//#pragma once
#ifndef _MISSLE_H
#define _MISSLE_H
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#define MAXMISSLESMOKE 150
extern CLoadVBMD *m_VBMD;//VBMDģ�Ͷ���
extern tModelID ModelID[100];
class Missledata
{
public:
	Transform UDMplane;//��������
	RigidBody UDPstate;//�����˶�ѧ״̬
	int UDlife;//����ֵ��-1��ʾ�����ڣ�0��ʾ�Ѿ�����
	int UDMissleType;//��������
	int TGTnum;//Ŀ�굥λ���
	/*
	float UDposx[MAXMISSLESMOKE];//β����������x
	float UDposy[MAXMISSLESMOKE];//β����������y
	float UDposz[MAXMISSLESMOKE];//β����������z
	float UDposxMove[MAXMISSLESMOKE];//β����������x
	float UDposyMove[MAXMISSLESMOKE];//β����������y
	float UDposzMove[MAXMISSLESMOKE];//β����������z
	float UDposzSIZE[MAXMISSLESMOKE];//β�����Ӵ�С
	float UDposxF[MAXMISSLESMOKE];//β����������x
	float UDposyF[MAXMISSLESMOKE];//β����������y
	float UDposzF[MAXMISSLESMOKE];//β����������z
	*/
	float UDwinl;//�����ҵľ��룬UDwinz����Ļ������ȣ�Ϊ������ʱ���ֵ��Ч
	float UDwinx;//��Ļ����x
	float UDwiny;//��Ļ����y
	float UDwinz;//��Ļ�������
	//int smokeNum[MAXMISSLESMOKE];//β��������
	int UDposflag;//��ʾĿǰ�����������
	int UDposflagF;//��ʾĿǰ�����������
	int smokeTime;//��������������ʱ��
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