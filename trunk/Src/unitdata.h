
#ifndef _UNITDATA_H
#define _UNITDATA_H
//#pragma once
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#include<hgl/OpenALEE.H>
//#include "ACMD.h"
#define AImode_Counterattack 1//�ܹ���ʱ����
#define AImode_Travel 2//�ܹ���ʱ����֮ǰ���ж�
#define AImode_Avoid 3//�ܹ���ʱ�ر�
#define AIact_MoveOrStandby 1//��ĳ���ƶ�������ĳ����������
#define AIact_Attact 2//��ĳĿ�깥��
#define AIact_Avoid 3//����
#define AIact_assemble 4//��ӳ�����

#define MAXTrack 100
#define MAXweapon 4
#define MAXUNITSMOKE 150
//extern CLoadACMD *m_nj;//ACMDģ�Ͷ���
extern CLoadVBMD *m_VBMD;//VBMDģ�Ͷ���
extern tModelID ModelID[100];
extern int ModelID_MavePart_Normal;
//using namespace hgl;
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
	//bool isLeader;//�Ƿ��Ƕӳ�
	//int leadrNum;//�ӳ����
	int UDlife;//����ֵ��-1��ʾ�����ڣ�0��ʾ�Ѿ�����
	float UDwinl;//�����ҵľ��룬UDwinz����Ļ������ȣ�Ϊ������ʱ���ֵ��Ч
	float UDwinx;//��Ļ����x
	float UDwiny;//��Ļ����y
	float UDwinz;//��Ļ�������
	char  UDname[32];//��λ����
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

	int Track_index; 
	float Tracks[MAXTrack*12];
	float TracksColor[MAXTrack*4];
	//float TracksTexCoord[MAXTrack*2];
	float TrackAlpha;
	int weapon[MAXweapon];//�������<0ʱ��ʾû������
	int smokeTime;//��������������ʱ��
	
	int attackedMissleNum;//�������ĵ������
	int attackedTGTNum;//�������ĵ��˱��
	int AImode;//�ж�ģʽ1 ������ʱ���� ��2������ʱ����֮ǰ����Ϊ
	int AIact;//��ǰ��Ϊ1 ��ָ�����ƶ�����ָ������Χ���� ��2���� ��3����
	int AIType;//0 һ�� 1 ace 2 boss
	int AIactTimer1;
	int AIactTimer2;
	int LockListNum;//�������
	int attackTGTNum;//����Ŀ��
	int fireTimer;//���������ʱ��
	int RefireTime;//�������ʱ��
	int LockTimer;//������ʱ��
	int LockOnTime;//����Ŀ������ʱ��
	float attackRange;
	float mSpeed;
	bool isRSpeed;
	bool inGunRange;
	bool inGunSoundRange;
	Vector3d MoveToPos;
	int SelfNormalModelID;
	int SelfLowModelID;

	float WingWidth;
	float TrackWidth;
	int AddTrack_index;
	unsigned int VBOVertices[8];
	unsigned int VBOColor[2];	
	//unsigned int VBOTexCoord[2];

	//AudioSource * SoundSourceGun;
	bool isAttacking;
	bool isAttackReady;



	
public:
    Unitdata(void);
	~Unitdata(void);
	//void setLinePos(void);//Transform& MView
//	void PrintLinePos(Transform& MView);
	//void setpos(int smokeN=0);
    void TurnTo(const Vector3d& Position);
	void TurnTom(const Vector3d& Position);
	double WaringTo(const Vector3d& Position);
	//void m_DrawMissle(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge);
	bool m_DrawSelf(const Vector3d& ViewPos,int m_winwidth,int m_winheight,float m_tmpLookRenge);
	void m_LaunchMissle(int m_TGT_Num);
	void AttackTo(const Vector3d& Position);
	void MoveSpeed(void);//ʧ�����
	void ResetData(void);
	void m_Sound(Transform& would,float LookRenge);
	bool isPlayer;
	void addTrack(void);
	void DrawTrack(void);
	void initVBO(void);
};


#endif