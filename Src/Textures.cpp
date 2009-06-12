#include "HUDUI.h"
#include "DDS.h"
GLuint textureRedar,ShowHPTexID,CompassTexID,UItexture4,PlayerSign,LockTexID,Maptexture,SeaTexID;

unsigned int EmptyTexture(int wh,bool isGL_LINEAR)							// ����һ���յ�����
{
	GLuint txtnumber;							// ����ID
	unsigned int* data;						// �洢����

	// Ϊ�������ݣ�128*128*4�������洢��
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// ����洢��

	glGenTextures(1, &txtnumber);				// ����һ������
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// ��������

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, wh, wh, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if(isGL_LINEAR)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}

	delete [] data;						// �ͷ�����

	return txtnumber;						// ��������ID
}

void LoadGLTextures()
{

	CDDS loadDDS;
	textureRedar=loadDDS.loadCompressedTexture("Data/redar.dds");
	ShowHPTexID=loadDDS.loadCompressedTexture("Data/showHP.dds");
	CompassTexID=loadDDS.loadCompressedTexture("Data/Compass.dds");
	UItexture4=loadDDS.loadCompressedTexture("Data/UI1.dds");
	PlayerSign=loadDDS.loadCompressedTexture("Data/PlayerSign.dds");
	LockTexID=loadDDS.loadCompressedTexture("Data/lock.dds");
	Maptexture=loadDDS.loadCompressedTexture("Data/map.dds");
	SeaTexID=loadDDS.loadCompressedTexture("Data/sea.dds");
}