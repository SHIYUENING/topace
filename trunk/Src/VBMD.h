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
	// ��������
	unsigned int	TextureID;								// ��ͼ���
	unsigned int	VertexCount;							// �������鶥����
	float*			pVertices;								// �������鶥������
	float*			pNormals;								// �������鷨������
	float*			pTexCoords;								// ��������������������

	// ���㻺�����ID
	unsigned int	VBOVertices;							// ���� ���㻺��ID
	unsigned int	VBONormals;								// ���� ���㻺��ID
	unsigned int	VBOTexCoords;							// �������� ���㻺��ID
};

class CLoadVBMD		// CLoadVBMD�ദ�����е�װ�����
{
public:
	CLoadVBMD();								// ��ʼ�����ݳ�Ա
	virtual ~CLoadVBMD();
	int Init(char *filename,bool UseTexture=true,GLint UserTexture=0);					
	bool ShowVBMD(unsigned int MID,bool BindSelfTexture=true);
	void CleanUpVBMD(unsigned int MID);					// ɾ��ģ������
	void BuildVBO(unsigned int MID);					// �������㻺�����
	bool VBOSupported;
	bool m_IsSupportFBO;
	int TotalMid;
	int ModelId;
	float VerticesInToTBN[3][3];
	float TexCoordsInToTBN[3][2];
	float TBNout[3];

private:
	FILE	*m_FilePointer;								// �ļ�ָ��
public:
	void TBN(void);
};
#endif