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
	bool UseTangentArray;

	unsigned int	TextureID;							
	unsigned int	NormalTexID;						
	unsigned int	SpecularTexID;

	unsigned int	VertexCount;					
	float*			pVertices;							
	float*			pNormals;							
	float*			pTexCoords;							
	float*			pTangent;							

	unsigned int	VBOVertices;						
	unsigned int	VBONormals;							
	unsigned int	VBOTexCoords;					
	unsigned int	VBOTangent;					
};

class CLoadVBMD	
{
public:
	CLoadVBMD();							
	virtual ~CLoadVBMD();
	int Init(char *filename,bool UseTexture=true,GLint UserTexture=0,bool UseTangent=false);					
	bool ShowVBMD(unsigned int MID,bool BindSelfTexture=true);
	void CleanUpVBMD(unsigned int MID);				
	void BuildVBO(unsigned int MID);				
	bool VBOSupported;
	bool m_IsSupportFBO;
	int TotalMid;
	int ModelId;
	float VerticesInToTBN[3][3];
	float TexCoordsInToTBN[3][2];
	float TBNout[3];

private:
	FILE	*m_FilePointer;							
public:
	void TBN(void);
	unsigned int GetTextureID(int MID);
	unsigned int GetNormalTexID(int MID);
	unsigned int GetSpecularTexID(int MID);
};
#endif