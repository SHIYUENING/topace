#include "HUDUI.h"
#include "DDS.h"
GLuint textureRedar,ShowHPTexID,CompassTexID,UItexture4,PlayerSign,LockTexID,Maptexture,SeaTexID;

unsigned int EmptyTexture(int wh,bool isGL_LINEAR)							// 创建一个空的纹理
{
	GLuint txtnumber;							// 纹理ID
	unsigned int* data;						// 存储数据

	// 为纹理数据（128*128*4）建立存储区
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &txtnumber);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// 构造纹理

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

	delete [] data;						// 释放数据

	return txtnumber;						// 返回纹理ID
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