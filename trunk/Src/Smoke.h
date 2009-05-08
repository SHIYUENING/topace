//#pragma once
#ifndef _SMOKE_H
#define _SMOKE_H
#include "Mathematics.h"		
#include "DDS.h"
#include "texture.h"

#define MAXSMOKESLIST 40000
#define MAXSMOKETEXS 30
bool LoadTGA(Texture *, char *);
struct SmokeListNode
{
	unsigned int TexId;
	int type;
	float pos[3];
	float posMove[3];
	float size;
	float sizeMove;
	float life;
	float lifeMAX;
	//SmokeListNode * prev;
	//SmokeListNode * next;
};

class CSmoke
{
public:
	CSmoke(void);
	~CSmoke(void);
	//SmokeListNode *SmokeFirstNode;
	//SmokeListNode *SmokeNode;
	unsigned int SmokeNodeNumber;//下一个被添加的烟雾的编号
	unsigned int SmokeGLlist;//烟雾显示列表编号

	GLuint base;
	GLuint CloudTexID;
	int SmokeTexsNum;//烟雾纹理总数
	int GraphicLevel;//画面质量等级
	float SmokeAlpha;
	float SmoleL;
	float tmpX;
	float tmpY;
	float tmpZ;
	float CloudSize;

	bool m_IsSkip;
	
	void AddSmoke(float posx, float posy, float posz, float size=1.0f, float sizeMove=0.0f, float life=150.0f,int type=0,int CloudListNum=0);
	
	void BuildSmoke(unsigned int settexID);
	void DrawSmoke(const Vector3d& ViewPos,Transform& would,int winwidth,int winheight,float LookRenge);
	void Init(int setGraphicLevel=1,int useCloud=1);
	bool LoadSmoke(int SmokeNum);
	//void DelSmoke(SmokeListNode * DelNode);
	Vector3d Pos3d;

	GLdouble WinPos[3];
	GLdouble mvmatrix[16];
	GLdouble projmatrix[16];
	GLint viewport[4];



	SmokeListNode SmokesList[MAXSMOKESLIST];
	Texture textureSmoke[MAXSMOKETEXS];
	
	bool BuildCloud(void);
	void DeleteCloud(void);
	void DeleteSmoke(void);
	void AddCloud(float posx, float posy, float posz);
	float LastPos[2];
};
#endif