//Textures.h
#pragma once
#include "DDS.h"										
#include "texture.h"
#include "testNum.h"
//#include "VBMD.h"
#include "shaders.h"
#include "BomTeams.h"
//#include "BomsSet.h"
#define MAXSMOKE 30
//#define MAXBOMS 40

int gpuType=0;//0未知 1NV 2ATI
bool LoadTGA(Texture *, char *);
Texture textureAlphaFont[1],textureLock[1];	//,textureBoms[MAXBOMS]
//GLuint	texture[2];	//gui相关纹理编号
GLuint textureRedar,UItexture4,Maptexture;
GLuint fbo;					// Our handle to the FBO
GLuint depthBuffer;			// Our handle to the depth render buffer
GLuint img,fboBloomImg,dtex;					// Our handle to a texture
//GLuint blurtexture2;
GLuint PlayerSign;
GLuint ShowHPTexID;
bool IsSupportFBO=false;
//int SmokeNumber=0;//读取的尾烟图片总数
//int BomsNumber=0;//读取的爆炸相关设定总数
//int BomPsNumber=0;//读取的爆炸相关图片总数
/*
struct BomsSet
{
	GLuint Pnum;//图片编号
	int SizeStart;
	int SizeEnd;
	int ShowTimeStart;//开始时间
	int ShowTimeEnd;//结束时间
	int ColorAlphaStart;//透明度
	int ColorAlphaEnd;//透明度
	
	int RandomSizeMIN;//随机大小最小值
	int RandomSizeMAX;//随机大小最大值
	int RandomMoveMIN;//随机移动量最小值
	int RandomMoveMAX;//随机移动量最大值
	
	
};

struct BomTeamsSet
{
	int Num;//图片编号
	BomsSet BomsSets[MAXBOMS];

	int RandomSize;//随机大小
	int RandomMove;//随机移动量
	
	int RandomSizeMIN;//随机大小最小值
	int RandomSizeMAX;//随机大小最大值
	int RandomMoveMIN;//随机移动量最小值
	int RandomMoveMAX;//随机移动量最大值
	
	
};*/
//CBomsSet BomsSets[MAXBOMS];
//用于创建渲染到纹理的空纹理
GLuint EmptyTexture(int wh=256)							// 创建一个空的纹理
{
	GLuint txtnumber;							// 纹理ID
	unsigned int* data;						// 存储数据

	// 为纹理数据（128*128*4）建立存储区
	data = (unsigned int*)new GLuint[((wh * wh)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((wh * wh)* 4 * sizeof(unsigned int)));	// 清除存储区

	glGenTextures(1, &txtnumber);				// 创建一个纹理
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// 构造纹理

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, wh, wh, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if(IsSupportFBO)
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


//处理BMP
AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

//读纹理
/*
bool LoadBoms(int BomsNum)
{

	char BomsFileName[64]={0};
	sprintf(BomsFileName,"Data/Boms/Bom%d.tga",BomsNum);
	FILE	*m_Filefighter;
	if ((m_Filefighter=fopen(BomsFileName,"rb"))==NULL)
		return false;
	if (LoadTGA(&textureBoms[BomsNum], BomsFileName))
	{
		glGenTextures(1, &textureBoms[BomsNum].texID);
		glBindTexture(GL_TEXTURE_2D, textureBoms[BomsNum].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, textureBoms[BomsNum].bpp / 8, textureBoms[BomsNum].width, textureBoms[BomsNum].height, 0, textureBoms[BomsNum].type, GL_UNSIGNED_BYTE, textureBoms[BomsNum].imageData);
		
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (textureBoms[BomsNum].imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(textureBoms[BomsNum].imageData);					// Free The Texture Image Memory ( CHANGE )
		}
		return true;

	}
	return false;
}
*/
/*
bool LoadSmoke(int SmokeNum)
{
	char SmokeFileName[64]={0};
	sprintf(SmokeFileName,"Data/Smokes/smoke%d.tga",SmokeNum);
	FILE	*m_Filefighter;
	if ((m_Filefighter=fopen(SmokeFileName,"rb"))==NULL)
		return false;

	if (LoadTGA(&textureSmoke[SmokeNum], SmokeFileName))
	{											


				// Typical Texture Generation Using Data From The TGA ( CHANGE )textureAlphaFontFont[1]
		glGenTextures(1, &textureSmoke[SmokeNum].texID);				// Create The Texture ( CHANGE )
		glBindTexture(GL_TEXTURE_2D, textureSmoke[SmokeNum].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, textureSmoke[SmokeNum].bpp / 8, textureSmoke[SmokeNum].width, textureSmoke[SmokeNum].height, 0, textureSmoke[SmokeNum].type, GL_UNSIGNED_BYTE, textureSmoke[SmokeNum].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}

		if (textureSmoke[SmokeNum].imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(textureSmoke[SmokeNum].imageData);					// Free The Texture Image Memory ( CHANGE )
		}

		return true;
	}

	return false;


}
*/
void initFBO()
{
	char szGPU[128]={0};
	sprintf(szGPU,"%s",(char *)glGetString(GL_VENDOR));
	if(szGPU[0]=='A')
	{
		gpuType=2;
	}
	if(szGPU[0]=='N')
	{
		gpuType=1;
	}
	if(IsSupportFBO)
	{
		int imagesize=1024;

		glGenFramebuffersEXT(1, &fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

		glGenTextures(1, &img);
		glBindTexture(GL_TEXTURE_2D, img);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  imagesize, imagesize, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);//GL_RGBA16F_ARB
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glGenTextures(1, &fboBloomImg);
		glBindTexture(GL_TEXTURE_2D, fboBloomImg);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  imagesize, imagesize, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);//GL_RGBA16F_ARB
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


			
		glGenTextures(1, &dtex);
		glBindTexture(GL_TEXTURE_2D, dtex);
		if(gpuType==0)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		if(gpuType==2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		if(gpuType==1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, imagesize, imagesize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, fboBloomImg, 0);

		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status) 
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				MessageBox (HWND_DESKTOP, "Unsupported framebuffer format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing attachment\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same dimensions\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing draw buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing read buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			default:
				MessageBox (HWND_DESKTOP, "unknown error !!!!\n", "Error", MB_OK | MB_ICONEXCLAMATION);
	         
		}

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, dtex, 0);


		status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status) 
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
				MessageBox (HWND_DESKTOP, "Unsupported framebuffer format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing attachment\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same dimensions\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, attached images must have same format\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing draw buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
				MessageBox (HWND_DESKTOP, "Framebuffer incomplete, missing read buffer\n", "Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			default:
				MessageBox (HWND_DESKTOP, "unknown error !!!!\n", "Error", MB_OK | MB_ICONEXCLAMATION);
	         
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now
	}


}
int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	


	int Status=FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[6];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	/*
	if (TextureImage[0]=LoadBMP("Data/Font.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}
	*/
	/*
	if(LoadTGA(&SkyTex[0],"Data/sky/BK.tga"))
	{
		glGenTextures(1,&SkyTex[0].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[0].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[0].bpp/8, SkyTex[0].width, SkyTex[0].height, 0, SkyTex[0].type, GL_UNSIGNED_BYTE, SkyTex[0].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[0].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[0].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[1]=SkyTex[0].texID;
	
	}
	if(LoadTGA(&SkyTex[1],"Data/sky/DN.tga"))
	{
		glGenTextures(1,&SkyTex[1].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[1].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[1].bpp/8, SkyTex[1].width, SkyTex[1].height, 0, SkyTex[1].type, GL_UNSIGNED_BYTE, SkyTex[1].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[1].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[1].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[1]=SkyTex[1].texID;
	
	}
	if(LoadTGA(&SkyTex[2],"Data/sky/FR.tga"))
	{
		glGenTextures(1,&SkyTex[2].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[2].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[2].bpp/8, SkyTex[2].width, SkyTex[2].height, 0, SkyTex[2].type, GL_UNSIGNED_BYTE, SkyTex[2].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[2].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[2].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[2]=SkyTex[2].texID;
	
	}

	if(LoadTGA(&SkyTex[3],"Data/sky/LF.tga"))
	{
		glGenTextures(1,&SkyTex[3].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[3].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[3].bpp/8, SkyTex[3].width, SkyTex[3].height, 0, SkyTex[3].type, GL_UNSIGNED_BYTE, SkyTex[3].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[3].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[3].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[3]=SkyTex[3].texID;
	
	}

	if(LoadTGA(&SkyTex[4],"Data/sky/RT.tga"))
	{
		glGenTextures(1,&SkyTex[4].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[4].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[4].bpp/8, SkyTex[4].width, SkyTex[4].height, 0, SkyTex[4].type, GL_UNSIGNED_BYTE, SkyTex[4].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[4].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[4].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[4]=SkyTex[4].texID;
	
	}
	if(LoadTGA(&SkyTex[5],"Data/sky/UP.tga"))
	{
		glGenTextures(1,&SkyTex[5].texID);
		glBindTexture(GL_TEXTURE_2D, SkyTex[5].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, SkyTex[5].bpp/8, SkyTex[5].width, SkyTex[5].height, 0, SkyTex[5].type, GL_UNSIGNED_BYTE, SkyTex[5].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (SkyTex[5].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(SkyTex[5].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		texture[5]=SkyTex[5].texID;
	
	}
*/
	if(LoadTGA(&textureLock[0],"Data/lock.TGA"))
	{
		glGenTextures(1,&textureLock[0].texID);
		glBindTexture(GL_TEXTURE_2D, textureLock[0].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, textureLock[0].bpp/8, textureLock[0].width, textureLock[0].height, 0, textureLock[0].type, GL_UNSIGNED_BYTE, textureLock[0].imageData);
		if(IsSupportFBO)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}
		if (textureLock[0].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(textureLock[0].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		//texture[1]=textureLock[0].texID;
	
	}
		/*
	if (TextureImage[1]=LoadBMP("Data/lock.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[1]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[1])									// If Texture Exists
	{
		if (TextureImage[1]->data)							// If Texture Image Exists
		{
			free(TextureImage[1]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[1]);								// Free The Image Structure
	}
*/
	CDDS loadDDS;
	textureRedar=loadDDS.loadCompressedTexture("Data/redar.dds");
	ShowHPTexID=loadDDS.loadCompressedTexture("Data/showHP.dds");
	/*
	if (TextureImage[2]=LoadBMP("Data/redar.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &textureRedar);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, textureRedar);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[2])									// If Texture Exists
	{
		if (TextureImage[2]->data)							// If Texture Image Exists
		{
			free(TextureImage[2]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[2]);								// Free The Image Structure
	}
*/

	if (TextureImage[3]=LoadBMP("Data/UI1.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &UItexture4);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, UItexture4);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[3])									// If Texture Exists
	{
		if (TextureImage[3]->data)							// If Texture Image Exists
		{
			free(TextureImage[3]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[3]);								// Free The Image Structure
	}
/*		
	if (TextureImage[4]=LoadBMP("Data/map.BMP"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &Maptexture);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, Maptexture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[4])									// If Texture Exists
	{
		if (TextureImage[4]->data)							// If Texture Image Exists
		{
			free(TextureImage[4]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[4]);								// Free The Image Structure
	}
*/
	if (TextureImage[5]=LoadBMP("Data/PlayerSign.BMP"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &PlayerSign);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, PlayerSign);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[5]->sizeX, TextureImage[5]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[5]->data);
		if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}
	}

	if (TextureImage[5])									// If Texture Exists
	{
		if (TextureImage[5]->data)							// If Texture Image Exists
		{
			free(TextureImage[5]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[5]);								// Free The Image Structure
	}
/*
	if (LoadTGA(&textureAlpha[0], "Data/fog.tga"))
	{											


			// Typical Texture Generation Using Data From The TGA ( CHANGE )textureAlphaFont[1]
			glGenTextures(1, &textureAlpha[0].texID);				// Create The Texture ( CHANGE )
			glBindTexture(GL_TEXTURE_2D, textureAlpha[0].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, textureAlpha[0].bpp / 8, textureAlpha[0].width, textureAlpha[0].height, 0, textureAlpha[0].type, GL_UNSIGNED_BYTE, textureAlpha[0].imageData);
			if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}

			if (textureAlpha[0].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(textureAlpha[0].imageData);					// Free The Texture Image Memory ( CHANGE )
			}

	}
	*/


	
//**************************************************
//爆炸测试
//**************************************************
/*
	for(int i=0;i<21;i++)
	{
		char bomFileName[64]={0};
		if(i<9)
			sprintf(bomFileName,"Data/boom/boom0%d.tga",i+1);
		else
			sprintf(bomFileName,"Data/boom/boom%d.tga",i+1);
		if (LoadTGA(&textureBom[i], bomFileName))
		{											


				// Typical Texture Generation Using Data From The TGA ( CHANGE )textureAlphaFontFont[1]
				glGenTextures(1, &textureBom[i].texID);				// Create The Texture ( CHANGE )
				glBindTexture(GL_TEXTURE_2D, textureBom[i].texID);
				glTexImage2D(GL_TEXTURE_2D, 0, textureBom[i].bpp / 8, textureBom[i].width, textureBom[i].height, 0, textureBom[i].type, GL_UNSIGNED_BYTE, textureBom[i].imageData);
				if(IsSupportFBO)
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				}
				else
				{
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				}

				if (textureBom[i].imageData)						// If Texture Image Exists ( CHANGE )
				{
					free(textureBom[i].imageData);					// Free The Texture Image Memory ( CHANGE )
				}

		}
	}
	*/
//**************************************************
//爆炸
//**************************************************
	/*
	FILE *File=NULL;
	File=fopen(".\\Data\\Boms\\BomsSet.ini","r");	
	if(File)
	{
		fclose(File);
		BomPsNumber=GetPrivateProfileInt("MainSet","PnumMax",0,".\\Data\\Boms\\BomsSet.ini");
		if(BomPsNumber>0)
		{

			BomsNumber=GetPrivateProfileInt("MainSet","BomnumMax",0,".\\Data\\Boms\\BomsSet.ini");
			if(BomsNumber>MAXBOMS)
				BomsNumber=MAXBOMS;
			if(BomsNumber>0)
			{
				for(int i=0;i<BomsNumber;i++)
				{
					BomsSets[i].m_IsSupportFBO=IsSupportFBO;
					char BomsIniName[64]={0};
					sprintf(BomsIniName,"Bom%d",i);
					int Ploadnum=GetPrivateProfileInt(BomsIniName,"Pnum",-1,".\\Data\\Boms\\BomsSet.ini");
					if((Ploadnum>-1)&&(BomsSets[i].LoadBoms(Ploadnum)))
					{
						
						//BomsSets[i].Pnum=textureBoms[Ploadnum].texID;
						BomsSets[i].SizeStart=GetPrivateProfileInt(BomsIniName,"SizeStart",0,".\\Data\\Boms\\BomsSet.ini");
						BomsSets[i].SizeEnd=GetPrivateProfileInt(BomsIniName,"SizeEnd",0,".\\Data\\Boms\\BomsSet.ini");
						BomsSets[i].ShowTimeStart=GetPrivateProfileInt(BomsIniName,"ShowTimeStart",0,".\\Data\\Boms\\BomsSet.ini");
						BomsSets[i].ShowTimeEnd=GetPrivateProfileInt(BomsIniName,"ShowTimeEnd",0,".\\Data\\Boms\\BomsSet.ini");
						BomsSets[i].ColorAlphaStart=GetPrivateProfileInt(BomsIniName,"ColorAlphaStart",0,".\\Data\\Boms\\BomsSet.ini");
						BomsSets[i].ColorAlphaEnd=GetPrivateProfileInt(BomsIniName,"ColorAlphaEnd",0,".\\Data\\Boms\\BomsSet.ini");
					}
				}
			}
		}
/*
		while(LoadBoms(BomPsNumber))
		{
			//windowswidth=GetPrivateProfileInt("Resolution","width",800,".\\set.ini");
			BomsSets[BomsNumber].Pnum=textureBoms[BomsNumber].texID;
			char BomsIniName[64]={0};
			sprintf(BomsIniName,"Bom%d",BomsNumber);
			BomsSets[BomsNumber].RandomSizeMIN=GetPrivateProfileInt(BomsIniName,"RandomSizeMIN",0,".\\Data\\Boms\\BomsSet.ini");
			BomsSets[BomsNumber].RandomSizeMAX=GetPrivateProfileInt(BomsIniName,"RandomSizeMAX",0,".\\Data\\Boms\\BomsSet.ini");
			BomsSets[BomsNumber].RandomMoveMIN=GetPrivateProfileInt(BomsIniName,"RandomMoveMIN",0,".\\Data\\Boms\\BomsSet.ini");
			BomsSets[BomsNumber].RandomMoveMAX=GetPrivateProfileInt(BomsIniName,"RandomMoveMAX",0,".\\Data\\Boms\\BomsSet.ini");
			BomsSets[BomsNumber].ShowTimeStart=GetPrivateProfileInt(BomsIniName,"ShowTimeStart",0,".\\Data\\Boms\\BomsSet.ini");
			BomsSets[BomsNumber].ShowTimeEnd=GetPrivateProfileInt(BomsIniName,"ShowTimeEnd",0,".\\Data\\Boms\\BomsSet.ini");
			
			BomPsNumber=BomPsNumber+1;
			if(BomsNumber==MAXBOMS)
				break;
		}
*/
/*	}
	
	else
	{
		WritePrivateProfileString("MainSet","PnumMax","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("MainSet","BomnumMax","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","Pnum","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","SizeStart","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","SizeEnd","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","ShowTimeStart","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","ShowTimeEnd","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","ColorAlphaStart","0",".\\Data\\Boms\\BomsSet.ini");
		WritePrivateProfileString("Bom0","ColorAlphaEnd","0",".\\Data\\Boms\\BomsSet.ini");
		//WritePrivateProfileString("Bom0","Enable","0",".\\Data\\Boms\\BomsSet.ini");
	}
	*/
//**************************************************
//尾烟
//**************************************************
		//while(LoadSmoke(SmokeNumber))
		//SmokeNumber=SmokeNumber+1;
//**************************************************
//FBO
//**************************************************

	return Status;										// Return The Status
}
