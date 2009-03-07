#ifndef _ACMD_H
#define _ACMD_H
#include <GL/glew.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glaux.h>
#include <iostream>

class CVector3F					// 定义3D点的类，用于保存模型中的顶点
{
public:	
	float x, y, z;
};

class CVector3S					// 定义3D点的类，用于保存模型中的顶点
{
public:	
	short x, y, z;
};

class CVector4B					// 定义3D点的类，用于保存模型中的顶点
{
public:	
	unsigned char r, g, b, a;
};

class CVector2F					// 定义3D点的类，用于保存模型中的顶点
{
public:	
	float u, v;
};

struct tPart
{
	unsigned long	size;
	unsigned char	*pData;
};

struct tACMD
{
	unsigned long	size;
	unsigned char	*pData;
	unsigned int	texture[10];
};

struct tACMHeader
{
	unsigned long	MAGICWORD;	//ACM 0x00 4D 43 41
	unsigned long	UnknownData_UL;
	float			UnknownData_2F[2];

	unsigned long	PartInfo[2];
	unsigned long	PartIndex[2];

	unsigned long	numOfTexture;
	unsigned long	Unknown1_Index;
	unsigned long	Unknown2_Index[2];

	unsigned long	RotKeyIndex[2];
	unsigned long	UnknownKey1_Index[2];

	unsigned long	UnknownKey2_Index[2];
	unsigned long	UnknownKey3_Index[2];
};

struct tPartInfo
{
	unsigned long	MaterialID;	// 材质编号
	unsigned long	numOfSubParts;	// 子部件数量
	unsigned long	PartID;	// 部件编号
	unsigned long	TextureID; // 贴图编号

	unsigned short	UnknowData2_US[2];
	unsigned long	UnknowData3_UL;
	unsigned long	UnknowData4_UL;
	unsigned long	UnknowData5_UL;

	float			POS[4];
	float			ROT[4];
};		


class CLoadACMD		// CLoadACMD类处理所有的装入代码
{
public:
	CLoadACMD();								// 初始化数据成员
	virtual ~CLoadACMD();
	void Init(char *filename, unsigned long MID,int modeltype=0);					
	void ShowACMD(unsigned long MID, unsigned long PID, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);
	void CleanUp();										// 关闭文件，释放内存空间

private:
	int mtype;
	bool ReadParts(unsigned long *pDWORD, unsigned long MID);
	unsigned long ReadPartInfo(tACMHeader *pACMHeader, tPartInfo *pPartInfo, unsigned long MID) ;
	bool ReadACM(unsigned char *pData, unsigned long MID);	// 读取ACM块
	bool ReadGIM(unsigned char *pData, unsigned long MID, unsigned long TID); // 读取GIM块

	void DeleteACMD(unsigned long MID);	// 删除模型数据

	FILE	*m_FilePointer;								// 文件指针
	FILE	*m_DumpFilePointer;							// 
};
#endif