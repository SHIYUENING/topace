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
int lockflash=0;//�����������Ƿ���˸
unsigned int FrameSkip=0;

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
bool KeySPACE=false;
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
int winwidth,winheight;//ȫ�ֱ��������ڼ�¼����ʵʱ��С��gui���ִ���ʹ�õ�

bool		g_fVBOSupported = false;							// ARB_vertex_buffer_object supported?
								// Rotation
int			g_nFPS = 0, g_nFrames = 0;							// FPS and FPS Counter
DWORD		g_dwLastFPS = 0;									// Last FPS Check Time	
//~TUTORIAL
double oneframetime=0.0;//ÿ������ʱ�䣬����0.016��Ϸ�Ͳ��ܱ���ȫ����
double oneframetimeT=0.0;
int needloadfile=0;
bool loadover=false;
bool isDraw=false;
bool lockedsound=false;
bool GunFiresound=false;
float turnX,turnY,turnZ,moveX,moveY,moveZ,turnSpeed;//�����ת���ƶ�����
float shellturn;
//GLdouble wx,wy,wz;//ĳ��λ�ڴ����ϵ����꣬Z<0˵����ǰ����Z>0˵���ں󷽣�ZֵӦ�������
//���������ǹ��Լ�����ر���
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

char szVERSION[512]={0};//opengl�汾

char szResolution[128]={0};//��Ļ�߿�
char szTitle[256]={0};	//����

GLdouble lockX,lockY;//������λ��
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
//bool Bgens=false;//������ͼ���
//bool Bgent=false;//������ͼ���

bool lockedX=false;//X���Ƿ�������Ŀ��
bool lockedY=false;//Y���Ƿ�������Ŀ��
bool lockselect=false;//�Ƿ�Ҫ����Ŀ��
bool KeyQ=false;//������Q���Ƿ���
bool KeyF=false;//������F���Ƿ���
bool KeyR=false;//������R���Ƿ���
bool KeyT=false;
double oneframetimelimit=1.0/60.0;//ÿ�����ʱ��
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
extern bool ShaderLight;//�Ƿ�ʹ��shader
extern bool ShaderWater;//�Ƿ�ʹ��shader
extern bool ShaderBloom;//�Ƿ�ʹ��Bloom
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