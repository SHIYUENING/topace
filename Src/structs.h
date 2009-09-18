#pragma once
#include "chars.h"
#include "DefinesFile.h"
#include "Unitdata.h"
#include "MissleList.h"
#include "Models.h"
#include "sound.h"
#include "Shell.h"
#include "MyFont.h"
#include "HUDUI.h"
int lockflash=0;//决定锁定框是否闪烁
unsigned int FrameSkip=0;

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
bool KeySPACE=false;
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
/*
Transform MavePart_BackL;
Transform MavePart_BackR;
Transform MavePart_FL;
Transform MavePart_FR;
Transform MavePart_WL;
Transform MavePart_WR;
*/
GLfloat Part_Main_ShadowMapMVPmatrix[16];
GLfloat Part_BackL_ShadowMapMVPmatrix[16];
GLfloat Part_BackR_ShadowMapMVPmatrix[16];
GLfloat Part_FL_ShadowMapMVPmatrix[16];
GLfloat Part_FR_ShadowMapMVPmatrix[16];
GLfloat Part_WL_ShadowMapMVPmatrix[16];
GLfloat Part_WR_ShadowMapMVPmatrix[16];
int MissleFireLightNum=-1;
int SmallWindowTGT=-1;
Vector3d SunPos3d;
CMyFont MyFont;
int winwidth,winheight;//全局变量，用于记录窗口实时大小，gui部分大多会使用到

bool		g_fVBOSupported = false;							// ARB_vertex_buffer_object supported?
								// Rotation
int			g_nFPS = 0, g_nFrames = 0;							// FPS and FPS Counter
DWORD		g_dwLastFPS = 0;									// Last FPS Check Time	
//~TUTORIAL
double oneframetime=0.0;//每桢运行时间，超过0.016游戏就不能保持全速了
double oneframetimeT=0.0;
int needloadfile=0;
bool loadover=false;
bool isDraw=false;
bool lockedsound=false;
bool GunFiresound=false;
float turnX,turnY,turnZ,moveX,moveY,moveZ,turnSpeed;//玩家旋转和移动变量
float shellturn;
//GLdouble wx,wy,wz;//某单位在窗口上的坐标，Z<0说明在前方，Z>0说明在后方，Z值应该是深度
//下面三个是惯性计算相关变量
float InertiaX=0.0f;
float InertiaY=0.0f;
float InertiaZ=0.0f;
float InertiaSpeed=0.0f;
float InertiaX_Last=0.0f;
float InertiaY_Last=0.0f;
float InertiaZ_Last=0.0f;
float InertiaSpeed_Last=0.0f;

float ViewTurnX=0.0f;
float ViewTurnY=0.0f;
bool pushkeyHUD=false;
bool GamePause=false;
bool KeyStart=false;
bool KeySelect=false;
bool KeyOther=false;

char szVERSION[512]={0};//opengl版本

char szResolution[128]={0};//屏幕高宽
char szTitle[256]={0};	//标题

GLdouble lockX,lockY;//锁定框位置
float MAXSpeed=0.05f;
float MINSpeed=0.0001f;
float Acceleration=0.0001f;
float SpeedShowPercentage=30000;
float TurnRateX=0.005f;
float TurnRateY=0.05f;
float TurnRateZ=0.005f;

float glClearColorR=0.72f;
float glClearColorG=0.73f;
float glClearColorB=0.82f;
float glClearColorA=1.0f;
float fogColorR=0.72f;
float fogColorG=0.73f;
float fogColorB=0.82f;
float fogColorA=1.0f;
float fogDENSITY=0.35f;
float Fog_Far=1000.0f;
float Fog_Near=800.0f;
float LightAmbientR=0.7f;
float LightAmbientG=0.7f;
float LightAmbientB=0.7f;
float LightAmbientA=1.0f;
float LightDiffuseR=1.0f;
float LightDiffuseG=1.0f;
float LightDiffuseB=1.0f;
float LightDiffuseA=1.0f;
//bool Bgens=false;//环境贴图相关
//bool Bgent=false;//环境贴图相关

bool lockedX=false;//X轴是否锁定到目标
bool lockedY=false;//Y轴是否锁定到目标
bool lockselect=false;//是否要锁定目标
bool KeyQ=false;//按键“Q”是否按下
bool KeyF=false;//按键“F”是否按下
bool KeyR=false;//按键“R”是否按下
bool KeyT=false;
double oneframetimelimit=1.0/60.0;//每桢最大时间
int wingFrame=0;
int wingFrame_Last=0;
int MissleBoxFrame=0;
int MissleBoxFrame_Last=0;
int SmallWindowType=0;
float moveSpeedT=0.0f;
float changeInertia=0.0f;
float EnginePower=0.5f;
float EnginePower_Last=0.5f;
extern bool isinitsound;
extern AudioBuffer * missleWarning[MAX_missleWarning];
extern AudioBuffer * fox2voice[MAX_fox2voice];
extern AudioBuffer * hitvoice[MAX_hitvoice];
extern AudioBuffer * killvoice[MAX_killvoice];
extern AudioBuffer * missvoice[MAX_missvoice];
extern AudioBuffer * sounds[MAX_sounds];
extern AudioSource * voiceSource;
extern AudioSource * voiceSourceLock;
extern AudioSource * voiceSourceLockOn;
extern AudioSource * voiceSourceLocked;
extern AudioSource * voiceSourceGunFire;
extern AudioSource * voiceSourceAWACS;
extern AudioSource * soundSource[MAX_soundSource];
extern Vector3d soundSourcePos[MAX_soundSource];
extern AudioPlayer * BGMplayer;
extern tSoundSourceDate SoundSourceDate[MAX_soundSource];
extern GLuint SeaTexID,UItexture1,UItexture2,UItexture3;;

GLuint SmallWinTexID=0;
GLint SmallWinSize=128;
bool IsSupportFBO=false;
GLuint RedarTexture;
float tmplockRenge=10000.0f;
extern bool VBOSupported;
extern GLuint AmbientReflectiveTexture;
extern bool ShaderLight;//是否使用shader
extern bool ShaderWater;//是否使用shader
extern bool ShaderBloom;//是否使用Bloom
extern bool UseHighShadow;
extern bool UseShadow;
extern unsigned int ShadowLevel;
extern float BackFireEyeDir[4];
extern float globalAmbient[4];
extern float paraLightColor[4];
extern float paraLightDirection[3];
extern float MissleLightDirection[4];
extern float MissleLightColor[3];
extern float lightColor[4];
extern float eyePosition[3];
extern float eyePositionSea[3];
extern float lightPosition[];
extern float lightPositionSea[];

extern float Ppos1;
extern float Ppos2;
extern float pixelfogColor[3];
extern GLfloat ShadowMapMVPmatrix[16];
extern GLfloat Worldmatrix[16];
extern GLdouble DrawPlayermatrix[16]={0};