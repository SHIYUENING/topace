#pragma once
#include "Unitdata.h"
#include "MissleList.h"
#include "Models.h"
#include "sound.h"
#include "Shell.h"
#include "MyFont.h"
int lockflash=0;//决定锁定框是否闪烁
unsigned int FrameSkip=0;
#define MAXRedarlocks 100
#define maxMissles 20
#define maxMisslesSmoke 20000
#define maxUnits 25
#define maxUnitsSmoke 20000
#define MAXweaponNUM 30
#define MAXsmoke 200
#define MAXBom 200
bool IsSkip=false;
bool IsHUD=false;
float tmpredarRenge=15000.0f;//临时雷达追踪范围
float tmpAREAredarRenge=100000.0f;//关卡范围
float tmpLookRenge=30000.0f;//临时视距
struct redarmodels
{
	char  name[10];//名字
	float Renge;//追踪范围

};
redarmodels redarmodel[10];
struct weapons
{
	char  name[10];//名字
	int type;//0不存在，1机枪，2导弹，3未定
	//bool life;//是否生存
	float ATK;//攻击力
	float SPEED;//飞行速度
	float flyTime;//持续时间
	float fireTime;//射击间隔
	float reloadTime;//装填时间
	int maxlock;//最大锁定数
	int fireNum;//同时最大发射数
	float lockrenge;//锁定距离
	int cannotLockType;//不能锁定的种类，0无，1陆/水，2空
	float damRenge;//爆炸范围
	float roll;//机动性/追踪时最大旋转角速度



};
weapons weapon[MAXweaponNUM];
struct Ground
{
	Transform pos;
	int ID;

};
Ground grounds[4];
struct Redar
{
	float Rx;
	float Ry;
	float Rz;
	bool Rlocked;
};
//Redar redarTGT[MAXRedarlocks];
int redarTGT_index=0;
struct locklist
{
	int TGTnum;//目标编号
	//float TGTwinL;//目标距离
	//double TGTwinLin;//目标距离屏幕中心的距离的平方(这里没必要开方,开方运算很慢,否则卡马克也不会搞magic number了)
};
locklist locklists[maxUnits];
int locklists_index=0;
struct locks
{
	float locksX;
	float locksY;
	int locksTGT;
	bool lockedX;
	bool lockedY;
	bool lockON;
};
locks lockUnits[8];//锁定框
Missledata LockSign[8];
Missledata MissleSign;
Missledata ViewPoint;

struct Bom
{
	int Frame;
	int life;
	float x;
	float y;
	float z;
	float winx;
	float winy;
	float winz;
	Vector3d pos;
};

int Bom_index=0;

Unitdata UDfighers[maxUnits];
Missledata LightSun;
float LightSunPos[3];
float LightSunPosR[3];
GLfloat moveSpeed=0.01f;//每桢玩家向前位移量
//Bom Boms[MAXBom];
bool PlayerLocked=false;
bool PlayerLocking=false;
bool isPlayerControl=false;
bool isKeyDown=false;
int StartShowTime=-1;
int hited=0;
int timer[100];
MissleList	PMissleList;
CShell Shell;
Transform MView(Vector3d(0, 0, -40));//观察矩阵
Transform MWorld;//世界矩阵
Transform MLight(Vector3d(0, 0, 40));//光源位置
Transform MFighter;//玩家
Transform MViewPoint;
Transform Msky;//天空位置
Transform MFireShellPos;
Transform MavePart_BackL;
Transform MavePart_BackR;
Transform MavePart_FL;
Transform MavePart_FR;
Transform MavePart_WL;
Transform MavePart_WR;
int MissleFireLightNum=-1;
Vector3d SunPos3d;

