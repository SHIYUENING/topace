#include "DDS.h"
#include "texture.h"
#include "HUDUI.h"


GLuint textureRedar,CompassTexID,UItexture4,PlayerSign,LockTexID,Maptexture,SeaTexID;
bool LoadTGA(Texture *, char *);
unsigned int LoadTGAFile(char *filename)
{
	Texture LoadTexture;

	if(LoadTGA(&LoadTexture,filename))
	{
		glGenTextures(1, &LoadTexture.texID);
		glBindTexture(GL_TEXTURE_2D, LoadTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, LoadTexture.bpp / 8, LoadTexture.width, LoadTexture.height, 0, LoadTexture.type, GL_UNSIGNED_BYTE, LoadTexture.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		if (LoadTexture.imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(LoadTexture.imageData);					// Free The Texture Image Memory ( CHANGE )
		}
		return LoadTexture.texID;
	}

	else
		return 0;
}

unsigned int EmptyTexture(int wh,bool isGL_LINEAR)							// ����һ���յ�����
{
	GLuint txtnumber;							// ����ID
	unsigned int* data;						// �洢����

	// Ϊ�������ݣ�128*128*4�������洢��
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// ����洢��

	glGenTextures(1, &txtnumber);				// ����һ������
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// ��������

	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, wh, wh,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

void LoadGLTextures(bool UseDDS)
{

	if(UseDDS)
	{
		CDDS loadDDS;
		textureRedar=loadDDS.loadCompressedTexture("Data/redar.dds");
		CompassTexID=loadDDS.loadCompressedTexture("Data/Compass.dds");
		UItexture4=loadDDS.loadCompressedTexture("Data/UI1.dds");
		PlayerSign=loadDDS.loadCompressedTexture("Data/PlayerSign.dds");
		LockTexID=loadDDS.loadCompressedTexture("Data/lock.dds");
		Maptexture=loadDDS.loadCompressedTexture("Data/map.dds");
		SeaTexID=loadDDS.loadCompressedTexture("Data/sea.dds",GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		textureRedar=LoadTGAFile("Data/redar.tga");
		CompassTexID=LoadTGAFile("Data/Compass.tga");
		UItexture4=LoadTGAFile("Data/UI1.tga");
		PlayerSign=LoadTGAFile("Data/PlayerSign.tga");
		LockTexID=LoadTGAFile("Data/lock.tga");
		Maptexture=LoadTGAFile("Data/map.tga");
		SeaTexID=LoadTGAFile("Data/sea.tga");
		
	}
}