#ifndef _VBMD_H
#define _VBMD_H
#include <GL/glew.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glaux.h>
#include <iostream>
#include "DDS.h"
struct tVBMDHeader
{
	unsigned char	MAGIC[4];
	unsigned int	Size;
	unsigned int	Offset;
	unsigned int	VertexCount;
};
struct tModelID
{
	int Main;
	int MainDD1;
	int MainDD2;
	int Normal;
	int Low;
};
struct tVBMD
{
	bool Islife;
	// 网格数据
	unsigned int	TextureID;								// 贴图编号
	unsigned int	VertexCount;							// 顶点数组顶点数
	float*			pVertices;								// 顶点数组顶点数据
	float*			pNormals;								// 顶点数组法线数据
	float*			pTexCoords;								// 顶点数组纹理坐标数据

	// 顶点缓存对象ID
	unsigned int	VBOVertices;							// 顶点 顶点缓存ID
	unsigned int	VBONormals;								// 法线 顶点缓存ID
	unsigned int	VBOTexCoords;							// 纹理坐标 顶点缓存ID
};

class CLoadVBMD		// CLoadVBMD类处理所有的装入代码
{
public:
	CLoadVBMD();								// 初始化数据成员
	virtual ~CLoadVBMD();
	int Init(char *filename,bool UseTexture=true,GLint UserTexture=0);					
	bool ShowVBMD(unsigned int MID,bool BindSelfTexture=true);
	void CleanUpVBMD(unsigned int MID);					// 删除模型数据
	void BuildVBO(unsigned int MID);					// 创建顶点缓存对象
	bool VBOSupported;
	bool m_IsSupportFBO;
	int TotalMid;
	int ModelId;
	float VerticesInToTBN[3][3];
	float TexCoordsInToTBN[3][2];
	float TBNout[3];

private:
	FILE	*m_FilePointer;								// 文件指针
public:
	void TBN(void);
};
#endif