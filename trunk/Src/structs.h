#pragma once
#include "Unitdata.h"
#include "MissleList.h"
#include "Models.h"
#include "sound.h"
#include "Shell.h"
#include "MyFont.h"
int lockflash=0;//�����������Ƿ���˸
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
float tmpredarRenge=15000.0f;//��ʱ�״�׷�ٷ�Χ
float tmpAREAredarRenge=100000.0f;//�ؿ���Χ
float tmpLookRenge=30000.0f;//��ʱ�Ӿ�
struct redarmodels
{
	char  name[10];//����
	float Renge;//׷�ٷ�Χ

};
redarmodels redarmodel[10];
struct weapons
{
	char  name[10];//����
	int type;//0�����ڣ�1��ǹ��2������3δ��
	//bool life;//�Ƿ�����
	float ATK;//������
	float SPEED;//�����ٶ�
	float flyTime;//����ʱ��
	float fireTime;//������
	float reloadTime;//װ��ʱ��
	int maxlock;//���������
	int fireNum;//ͬʱ�������
	float lockrenge;//��������
	int cannotLockType;//�������������࣬0�ޣ�1½/ˮ��2��
	float damRenge;//��ը��Χ
	float roll;//������/׷��ʱ�����ת���ٶ�



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
	int TGTnum;//Ŀ����
	//float TGTwinL;//Ŀ�����
	//double TGTwinLin;//Ŀ�������Ļ���ĵľ����ƽ��(����û��Ҫ����,�����������,�������Ҳ�����magic number��)
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
locks lockUnits[8];//������
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
GLfloat moveSpeed=0.01f;//ÿ�������ǰλ����
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
Transform MView(Vector3d(0, 0, -40));//�۲����
Transform MWorld;//�������
Transform MLight(Vector3d(0, 0, 40));//��Դλ��
Transform MFighter;//���
Transform MViewPoint;
Transform Msky;//���λ��
Transform MFireShellPos;
Transform MavePart_BackL;
Transform MavePart_BackR;
Transform MavePart_FL;
Transform MavePart_FR;
Transform MavePart_WL;
Transform MavePart_WR;
int MissleFireLightNum=-1;
Vector3d SunPos3d;

