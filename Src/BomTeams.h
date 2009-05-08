//#pragma once
#ifndef _BOMTEAMS_H
#define _BOMTEAMS_H
#include "texture.h"
#define MAXBOMACTS 20
#define MAXBOMINIS 20
#define MAXBOMTEXS 40

struct BomIni
{
	unsigned int TEXNum;//������
	int Pnum;//ͼƬ���
	int SizeStart;
	int SizeEnd;
	int ShowTimeStart;//��ʼʱ��
	int ShowTimeEnd;//����ʱ��
	int ColorAlphaStart;//͸����
	int ColorAlphaEnd;//͸����	
	int AlpahType;
};
class CBomTeams
{
public:
	CBomTeams(void);
	~CBomTeams(void);
	//������
	int m_BomsNumber;
	// ��ը���
	int Num;
	// �����С
	//int RandomSize;
	int RandomSizeMAX;
	int RandomSizeMIN;
	// ����ƶ���
	//int RandomMove;
	int RandomMoveMAX;
	int RandomMoveMIN;
	//�Ƿ����
	bool AutoGetPos;
	bool LoadBomTeam(int BomTeamNum);
	BomIni Bomini[MAXBOMACTS];
	int AllFrame;//�ܹ�������
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
	int m_AllBomTeamsNum;//ʵ�ʶ��˶����鱬ը
	unsigned int loadBomTEXs(int BomsNum);
	bool InitBomType(int TypeNum);
	
		
	int loadBomTEXsNum;// ʵ�ʶ��˶����ű�ըͼ
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