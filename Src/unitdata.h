
#ifndef _UNITDATA_H
#define _UNITDATA_H
//#pragma once
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#include<hgl/OpenALEE.H>
//#include "ACMD.h"
#define AImode_Counterattack 1//受攻击时反击
#define AImode_Travel 2//受攻击时继续之前的行动
#define AImode_Avoid 3//受攻击时回避
#define AIact_MoveOrStandby 1//向某点移动或者在某处附近盘旋
#define AIact_Attact 2//向某目标攻击
#define AIact_Avoid 3//闪避
#define AIact_assemble 4//向队长集中

#define MAXTrack 100
#define MAXweapon 4
#define MAXUNITSMOKE 150
//extern CLoadACMD *m_nj;//ACMD模型对象
extern CLoadVBMD *m_VBMD;//VBMD模型对象
extern tModelID ModelID[100];
extern int ModelID_MavePart_Normal;
//using namespace hgl;
class Unitdata
{
public:
	//Missledata UNITMissles[MAXUNITMISSLES];
	//int UNITMissles_Index;
	Transform UDMplane;//飞机矩阵
	RigidBody UDPstate;//飞机运动学状态
	bool UDlockselect;//是否被选择
	bool UDlockde;//是否被锁定
	bool waringde;//是否被警告
	//bool isLeader;//是否是队长
	//int leadrNum;//队长编号
	int UDlife;//生命值，-1表示不存在，0表示已经被灭
	float UDwinl;//相对玩家的距离，UDwinz（屏幕坐标深度）为负数的时候此值无效
	float UDwinx;//屏幕坐标x
	float UDwiny;//屏幕坐标y
	float UDwinz;//屏幕坐标深度
	char  UDname[32];//单位名字
	int UDfighterType;//机种
	int UDflag;//0为一般目标，1为重要目标，2为友军，3为第三方势力

	/*
	float UDposx[MAXUNITSMOKE];//尾烟粒子坐标x
	float UDposy[MAXUNITSMOKE];//尾烟粒子坐标y
	float UDposz[MAXUNITSMOKE];//尾烟粒子坐标z
	float UDposxMove[MAXUNITSMOKE];//尾烟粒子坐标x
	float UDposyMove[MAXUNITSMOKE];//尾烟粒子坐标y
	float UDposzMove[MAXUNITSMOKE];//尾烟粒子坐标z
	int smokeNum[MAXUNITSMOKE];//尾烟纹理编号
	*/

	int Track_index; 
	float Tracks[MAXTrack*12];
	float TracksColor[MAXTrack*4];
	//float TracksTexCoord[MAXTrack*2];
	float TrackAlpha;
	int weapon[MAXweapon];//武器编号<0时表示没有武器
	int smokeTime;//被消灭后烟雾残留时间
	
	int attackedMissleNum;//被攻击的导弹编号
	int attackedTGTNum;//被攻击的敌人编号
	int AImode;//行动模式1 被攻击时反击 ；2被攻击时继续之前的行为
	int AIact;//当前行为1 向指定点移动或在指定点周围盘旋 ；2攻击 ；3闪避
	int AIType;//0 一般 1 ace 2 boss
	int AIactTimer1;
	int AIactTimer2;
	int LockListNum;//锁定编号
	int attackTGTNum;//攻击目标
	int fireTimer;//攻击间隔计时器
	int RefireTime;//攻击间隔时间
	int LockTimer;//锁定计时器
	int LockOnTime;//锁定目标所需时间
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
	void MoveSpeed(void);//失速相关
	void ResetData(void);
	void m_Sound(Transform& would,float LookRenge);
	bool isPlayer;
	void addTrack(void);
	void DrawTrack(void);
	void initVBO(void);
};


#endif