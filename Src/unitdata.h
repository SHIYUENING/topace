
#ifndef _UNITDATA_H
#define _UNITDATA_H
//#pragma once
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#include "ACMD.h"

#define MAXweapon 4
#define MAXUNITSMOKE 150
//extern CLoadACMD *m_nj;//ACMDģ�Ͷ���
extern CLoadVBMD *m_VBMD;//VBMDģ�Ͷ���
class Unitdata
{
public:
	//Missledata UNITMissles[MAXUNITMISSLES];
	//int UNITMissles_Index;
	Transform UDMplane;//�ɻ�����
	RigidBody UDPstate;//�ɻ��˶�ѧ״̬
	bool UDlockselect;//�Ƿ�ѡ��
	bool UDlockde;//�Ƿ�����
	bool waringde;//�Ƿ񱻾���
	int UDlife;//����ֵ��-1��ʾ�����ڣ�0��ʾ�Ѿ�����
	float UDwinl;//�����ҵľ��룬UDwinz����Ļ������ȣ�Ϊ������ʱ���ֵ��Ч
	float UDwinx;//��Ļ����x
	float UDwiny;//��Ļ����y
	float UDwinz;//��Ļ�������
	char  UDname[10];//��λ����
	int UDfighterType;//����
	int UDflag;//0Ϊһ��Ŀ�꣬1Ϊ��ҪĿ�꣬2Ϊ�Ѿ���3Ϊ����������

	/*
	float UDposx[MAXUNITSMOKE];//β����������x
	float UDposy[MAXUNITSMOKE];//β����������y
	float UDposz[MAXUNITSMOKE];//β����������z
	float UDposxMove[MAXUNITSMOKE];//β����������x
	float UDposyMove[MAXUNITSMOKE];//β����������y
	float UDposzMove[MAXUNITSMOKE];//β����������z
	int smokeNum[MAXUNITSMOKE];//β��������
	*/
	int UDposflag;//��ʾĿǰ�����������
	int weapon[MAXweapon];//�������<0ʱ��ʾû������
	int smokeTime;//��������������ʱ��
	int TGTnum; //����Ŀ����
	int attackedMissleNum;//�������ĵ������
	int attackedTGTNum;//�������ĵ��˱��
	int AImode;//�ж�ģʽ1 ������ʱ���� ��2������ʱ����֮ǰ����Ϊ
	int AIact;//��ǰ��Ϊ1 ��ָ�����ƶ�����ָ������Χ���� ��2���� ��3����
	int LockListNum;//�������


	
public:
    Unitdata(void);
	~Unitdata(void);
	//void setLinePos(void);//Transform& MView
//	void PrintLinePos(Transform& MView);
	//void setpos(int smokeN=0);
    void TurnTo(const Vector3d& Position);
	double WaringTo(const Vector3d& Position);
	//void m_DrawMissle(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge);
	bool m_DrawSelf(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge);
	void m_LaunchMissle(int m_TGT_Num);
};


#endif