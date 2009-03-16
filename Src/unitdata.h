
#ifndef _UNITDATA_H
#define _UNITDATA_H
//#pragma once
#include "Mathematics.h"
#include "Physics.h"
#include "VBMD.h"
//#include "ACMD.h"

#define MAXweapon 4
#define MAXUNITSMOKE 150
//extern CLoadACMD *m_nj;//ACMD模型对象
extern CLoadVBMD *m_VBMD;//VBMD模型对象
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
	int UDlife;//生命值，-1表示不存在，0表示已经被灭
	float UDwinl;//相对玩家的距离，UDwinz（屏幕坐标深度）为负数的时候此值无效
	float UDwinx;//屏幕坐标x
	float UDwiny;//屏幕坐标y
	float UDwinz;//屏幕坐标深度
	char  UDname[10];//单位名字
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
	int UDposflag;//标示目前被变更的坐标
	int weapon[MAXweapon];//武器编号<0时表示没有武器
	int smokeTime;//被消灭后烟雾残留时间
	int TGTnum; //攻击目标编号
	int attackedMissleNum;//被攻击的导弹编号
	int attackedTGTNum;//被攻击的敌人编号
	int AImode;//行动模式1 被攻击时反击 ；2被攻击时继续之前的行为
	int AIact;//当前行为1 向指定点移动或在指定点周围盘旋 ；2攻击 ；3闪避
	int LockListNum;//锁定编号


	
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