//#pragma once
#ifndef _BOMTEAMS_H
#define _BOMTEAMS_H
#include "texture.h"
#define MAXBOMACTS 20
#define MAXBOMINIS 20
#define MAXBOMTEXS 40

struct BomIni
{
	unsigned int TEXNum;//纹理编号
	int Pnum;//图片编号
	int SizeStart;
	int SizeEnd;
	int ShowTimeStart;//开始时间
	int ShowTimeEnd;//结束时间
	int ColorAlphaStart;//透明度
	int ColorAlphaEnd;//透明度	
	int AlpahType;
};
class CBomTeams
{
public:
	CBomTeams(void);
	~CBomTeams(void);
	//动作数
	int m_BomsNumber;
	// 爆炸编号
	int Num;
	// 随机大小
	//int RandomSize;
	int RandomSizeMAX;
	int RandomSizeMIN;
	// 随机移动量
	//int RandomMove;
	int RandomMoveMAX;
	int RandomMoveMIN;
	//是否跟随
	bool AutoGetPos;
	bool LoadBomTeam(int BomTeamNum);
	BomIni Bomini[MAXBOMACTS];
	int AllFrame;//总共多少桢
	bool m_IsSkip;

	int DrawBomTeam(float posX, float posY, float posZ, int frame, unsigned int GLlistNum,float TeamSize);
};
class CBomType
{
public:
	CBomType(void);
	~CBomType(void);
	CBomTeams BomTeams[MAXBOMINIS];
	bool LoadTypeIni(int TypeNum);
	//Texture BomTextures[MAXBOMTEXS];
	int m_AllBomTeamsNum;//实际读了多少组爆炸
	unsigned int loadBomTEXs(int BomsNum);
	bool InitBomType(int TypeNum);
	
		
	int loadBomTEXsNum;// 实际读了多少张爆炸图
	bool m_IsSupportFBO;

public:
	bool InitBomTeams(void);
public:
	int BomType;
};
class CBom
{
public:
	CBom(void);
	~CBom(void);
	int Frame;
	int life;
	int m_Timer;
	float x;
	float y;
	float z;
	int Movex;
	int Movey;
	int Movez;
	int BomType;
	int BomTeam;
	int NewBom(float posx, float posy, float posz, CBomType * m_pBom);
	int RandomSize;
	int DrawBom(float posx, float posy, float posz, CBomType * m_pBom);
	bool AutoGetPos;
};
#endif