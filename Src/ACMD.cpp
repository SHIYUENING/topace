// ACMD.cpp : 定义控制台应用程序的入口点。
//
#include "ACMD.h"

using namespace std;

const unsigned long MAX_3DMODELS = 100;		// 确定最大模型数量
const float PI = 3.1415926589793284646433832795f;

tACMD	ACMD[MAX_3DMODELS];
GLuint	TEX[2];

CLoadACMD::CLoadACMD()
{	
	m_FilePointer= new FILE;	
	m_DumpFilePointer = new FILE;
	memset(m_FilePointer, NULL, sizeof(FILE));
}

CLoadACMD::~CLoadACMD()
{	
	CleanUp();// 释放内存空间
	
	for(unsigned long i=0; i<MAX_3DMODELS; i++)
	{
		DeleteACMD(i);
	}
}

void CLoadACMD::Init(char *filename, unsigned long MID,int modeltype)
{	
	mtype=modeltype;
	if(ACMD[MID].pData)
	{
		DeleteACMD(MID);
	}
		
	
	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		exit(0);
	}

	m_DumpFilePointer = fopen("DUMP.TXT", "wb");

	while (!feof(m_FilePointer))
	{
		fgetc(m_FilePointer);
		ACMD[MID].size++;
	}
	ACMD[MID].size--;
	//cout << "统计文件大小 " << ACMD[MID].size << "\n";

	rewind(m_FilePointer);

	ACMD[MID].pData = new unsigned char[ACMD[MID].size];	// 分配pData空间
	fread(ACMD[MID].pData, sizeof(unsigned char), ACMD[MID].size, m_FilePointer);	// 文件读入pData

	fclose(m_FilePointer);	// 关闭目标文件

	unsigned long *pHeader;	// 创建文件头
	pHeader = (unsigned long*)ACMD[MID].pData;		// 指向文件头

	glGenTextures(3, ACMD[MID].texture);
	unsigned long TID = 0;
	for(unsigned long i=1; i<=pHeader[0]; i++)
	{
		if((ACMD[MID].pData+pHeader[i])[0] != 'A')
		{
			if((ACMD[MID].pData+pHeader[i])[0] == 'G' && (ACMD[MID].pData+pHeader[i])[1] == 'I' && (ACMD[MID].pData+pHeader[i])[2] == 'M')
			{

				ReadGIM(ACMD[MID].pData+pHeader[i], MID, TID);
				TID++;
				//break;	// 目前只需要机身贴图
			}
			else 
			{
				unsigned long *pGIMPack;
				pGIMPack = (unsigned long *)(ACMD[MID].pData+pHeader[i]);

				// 贴图包模式
				for(unsigned long gid=1; gid<=pGIMPack[0]; gid++)
				{
					if((ACMD[MID].pData+pHeader[i]+pGIMPack[gid])[0] == 'G' && (ACMD[MID].pData+pHeader[i]+pGIMPack[gid])[1] == 'I' && (ACMD[MID].pData+pHeader[i]+pGIMPack[gid])[2] == 'M')
					{

						ReadGIM(ACMD[MID].pData+pHeader[i]+pGIMPack[gid], MID, TID);
						TID++;
						//break;	// 目前只需要机身贴图
					}
				}
			}

		}
	}

	/* //载入外置BMP时使用的

	AUX_RGBImageRec *pBitmap = NULL;

	pBitmap = auxDIBImageLoad("TEX.BMP");

	if(pBitmap)
	{
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, ACMD[MID].texture[0]);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

		if (pBitmap->data)	free(pBitmap->data);							
		free(pBitmap);		
	}

	m_FilePointer = NULL;		// 重置文件指针
*/
	
}

void CLoadACMD::CleanUp()
{
	if(m_FilePointer) 
	{
		fclose(m_FilePointer);
	}

	if(m_DumpFilePointer) 
	{
		fclose(m_DumpFilePointer);
	}
	
}

void CLoadACMD::DeleteACMD(unsigned long MID)
{
	glDeleteTextures(2,ACMD[MID].texture);	// 删除载入的纹理
	delete[] ACMD[MID].pData;
	ACMD[MID].pData = NULL;
}

void CLoadACMD::ShowACMD(unsigned long MID, unsigned long PID, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz)
{
	
	if(ACMD[MID].pData)
	{
		unsigned long *pHeader;	// 创建文件头
		pHeader = (unsigned long*)ACMD[MID].pData;		// 指向文件头

		if(PID<pHeader[0])
		{
			if((ACMD[MID].pData+pHeader[PID])[0] == 'A' && (ACMD[MID].pData+pHeader[PID])[1] == 'C' && (ACMD[MID].pData+pHeader[PID])[2] == 'M')
			{
				glPushMatrix();

				glTranslatef(tx,ty,tz);	

				
				glRotatef(ry, 0.0f, 1.0f, 0.0f);
				glRotatef(rz, 0.0f, 0.0f, 1.0f);
				glRotatef(rx, 1.0f, 0.0f, 0.0f);

				glScaled(sx,sy,sz);
				
				ReadACM(ACMD[MID].pData+pHeader[PID], MID);	// 读取ACM块
				
				glPopMatrix();
			}
		}
	}

}

bool CLoadACMD::ReadParts(unsigned long *pDWORD, unsigned long MID)
{
	unsigned long *limt;
	//unsigned long Index = 0;
	//unsigned long numOfStrips = 0;

	//limt = pDWORD + (*pDWORD)*4;
	limt = pDWORD + ((*pDWORD++)&0xFFFF)*4;
	pDWORD++;	// 未知数据，默认为0x0

	CVector3F	*pVerts = NULL;
	CVector3S	*pNormals = NULL;
	CVector4B	*pColors = NULL;
	CVector2F	*pTexCoords = NULL;

	while(pDWORD < limt)
	{
		unsigned long	numOfVerts = 0;

		//fprintf(fp2, "# 三角带 %u\n", numOfStrips);

		// 三角带数据区域
		pDWORD++;	// 不确定数据，猜测为 0x05 5个元素

		if(*pDWORD == 0x64018000)	// 数组成份0内容 顶点个数，未知参数个数
		{
			pDWORD++;
			numOfVerts = *pDWORD++;	// 获得顶点个数
			//cout << "Strip #" << numOfStrips << " 顶点数 " << numOfVerts << "\n";
			//fprintf(fp2, "# - 顶点数 %u\n", numOfVerts);

			pDWORD++;	// 未知参数个数
		}
		else
		{
			cout << "期待值错误！" << *pDWORD << "非数组成份0的头！\n";
			//system("pause");
			//exit(0);
			return false;
		}

		if(((*pDWORD)&0xFF00FFFF) == 0x68008001)	// 判断是否 0x68XX8001 顶点成分
		{
			if(((*pDWORD)&0x00FF0000)>>16 == numOfVerts)	// 判断是否 0x68XX8001 顶点数量与描述一致
			{
				pDWORD++;

				pVerts = (CVector3F *)pDWORD;	// 顶点指针指向pDWORD;

				pDWORD += numOfVerts*3;
			}
			else
			{
				cout << "期待值错误！顶点成分内顶点个数不同！\n";
				//system("pause");
				//exit(0);
				return false;
			}
		}
		else
		{
			cout << "期待值错误！非数组成份1的头！\n";
			//system("pause");
			//exit(0);
			return false;
		}

		if(((*pDWORD)&0xFF00FFFF) == 0x69008002)	// 判断是否 0x69XX8002 法向量成分
		{
			if(((*pDWORD)&0x00FF0000)>>16 == numOfVerts)	// 判断是否 0x69XX8002 顶点数量与描述一致
			{
				pDWORD++;

				pNormals = (CVector3S *)pDWORD;	// 法向量指针指向pDWORD;

				if(numOfVerts%2!=0)	// 处理未达到长整的问题
				{
					pDWORD += (numOfVerts*3+1)/2;
				}
				else
				{
					pDWORD += (numOfVerts*3)/2;
				}
			}
			else
			{
				cout << "期待值错误！法向量成分内顶点个数不同！\n";
				//system("pause");
				//exit(0);
				return false;
			}
		}
		else
		{
			cout << "期待值错误！非数组成份2的头！\n";
			//system("pause");
			//exit(0);
			return false;
		}

		if(((*pDWORD)&0xFF00FFFF) == 0x6E00C003)	// 判断是否 0x6EXXC003 着色成分
		{
			if(((*pDWORD)&0x00FF0000)>>16 == numOfVerts)	// 判断是否 0x6EXXC003 顶点数量与描述一致
			{
				pDWORD++;

				pColors = (CVector4B *)pDWORD;	// 顶点指针指向pDWORD;

				pDWORD += numOfVerts;
			}
			else
			{
				cout << "期待值错误！法向量成分内顶点个数不同！\n";
				//system("pause");
				//exit(0);
				return false;
			}
		}
		else
		{
			cout << "期待值错误！非数组成份3的头！\n";
			//system("pause");
			//exit(0);
			return false;
		}

		if(((*pDWORD)&0xFF00FFFF) == 0x64008004)	// 判断是否 0x64XX8004 纹理坐标成分
		{
			if(((*pDWORD)&0x00FF0000)>>16 == numOfVerts)	// 判断是否 0x64XX8004 顶点数量与描述一致
			{
				pDWORD++;

				pTexCoords = (CVector2F *)pDWORD;	// 纹理坐标指针指向pDWORD;

				pDWORD += numOfVerts*2;
			}
			else
			{
				cout << "期待值错误！纹理坐标成分内顶点个数不同！\n";
				//system("pause");
				//exit(0);
				return false;
			}
		}
		else
		{
			cout << "期待值错误！非数组成份4的头！\n";
			//system("pause");
			//exit(0);
			return false;
		}

		pDWORD++;	// 未知数据
		pDWORD++;	// 未知数据
		pDWORD++;	// 未知数据

		

		glFrontFace(GL_CW);
		
		glBegin(GL_TRIANGLE_STRIP);

		
		//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		for(unsigned long i=0; i<numOfVerts; i++)
		{
			glTexCoord2f(pTexCoords[i].u, pTexCoords[i].v);
			//glColor4ub(pColors[i].r, pColors[i].g, pColors[i].b, pColors[i].a);
			glNormal3f(((float)pNormals[i].x/0x7FFF), ((float)pNormals[i].y/0x7FFF), ((float)pNormals[i].z/0x7FFF));
			//glNormal3s(pNormals[i].x, pNormals[i].y, pNormals[i].z);
			glVertex3f(pVerts[i].x, pVerts[i].y, pVerts[i].z);
		}

		glEnd();
	}

	return true;
}

unsigned long CLoadACMD::ReadPartInfo(tACMHeader *pACMHeader, tPartInfo *pPartInfo, unsigned long MID) 
{
	unsigned long *pPartIndex = (unsigned long*)((unsigned char*)pACMHeader+pACMHeader->PartIndex[1]);	// 确定部件索引区域指针;
	unsigned long *pParts = pPartIndex + pACMHeader->PartIndex[0] + (4-pACMHeader->PartIndex[0]%4)%4;	// 确定部件数据区域指针;


	glBindTexture(GL_TEXTURE_2D, ACMD[MID].texture[pPartInfo->TextureID]);

	glPushMatrix();
	
	glTranslatef(pPartInfo->POS[0], pPartInfo->POS[1], pPartInfo->POS[2]);	// 位置变换

	
	glRotated(pPartInfo->ROT[2]*180/PI, 0.0, 0.0, 1.0);	// Z轴旋转变换
	
	//glRotatef(pPartInfo->ROT[0]*pACMHeader->UnknownData_2F[1], 1.0f, 0.0f, 0.0f);	// X轴旋转变换
	glRotated(pPartInfo->ROT[1]*180/PI, 0.0, 1.0, 0.0);	// Y轴旋转变换
	glRotated(pPartInfo->ROT[0]*180/PI, 1.0, 0.0, 0.0);	// X轴旋转变换
	//描绘模型pPartInfo[i].PartID pPartIndex pParts
	if(pPartInfo->PartID!=0xFFFFFFFF)
	{
		if(pPartInfo->MaterialID == 0x0B || pPartInfo->MaterialID == 0x01|| pPartInfo->MaterialID == 0x0|| pPartInfo->MaterialID == 0xa)
		{
			glEnable(GL_BLEND);

			if(pPartInfo->MaterialID == 0x0B)
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);			// Enable Alpha Blending
			}
			else
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
			//glColor4f(0.0f,0.0f,0.0f,0.5f);
			//glDisable(GL_DEPTH_TEST);
			//glDepthMask(GL_FALSE);
			}
		}
		else
		{	
			glDisable(GL_BLEND);
			//glBlendFunc(GL_SRC_COLOR,GL_SRC_ALPHA );
			glEnable(GL_DEPTH_TEST);
			
			//glColor4f(0.0f,0.0f,0.0f,1.0f);
			//glEnable(GL_DEPTH_TEST);
			//glDepthMask(GL_TRUE);
		}
		
		//char ObjFileName[20];
		
		//sprintf((char *)ObjFileName, "PART_%u.obj", pPartInfo->PartID);
		//if ((fp2=fopen(ObjFileName,"wb"))==NULL)
		//{
			//cout << "输出文件创建失败!\n";
		//}
		ReadParts(pParts+pPartIndex[pPartInfo->PartID]/4, MID);
		//fclose(fp2);	// 关闭目标文件
	}

	unsigned long NextOffset = 0;

	//cout << "PART " << pPartInfo->PartID << " Has " << pPartInfo->numOfSubParts << " SubPart(s).\n";

	for(unsigned long i=0; i<pPartInfo->numOfSubParts; i++)	// 渲染子对象
	{
		NextOffset++;
		//cout << "SubPart " << (pPartInfo+NextOffset)->PartID << " Of PART " << pPartInfo->PartID << "\n";
		NextOffset += ReadPartInfo(pACMHeader, pPartInfo+NextOffset, MID);
	}

	glPopMatrix();

	return NextOffset;
}

bool CLoadACMD::ReadACM(unsigned char *pData, unsigned long MID)	// 读取ACM块
{
	tACMHeader *pACMHeader;
	pACMHeader = (tACMHeader*)pData;

	tPartInfo *pPartInfo;
	pPartInfo = (tPartInfo*)(pData+pACMHeader->PartInfo[1]);

	for(unsigned long i=0; i<pACMHeader->PartInfo[0]; i++)	// 未达到PartInfo总数
	{
		i += ReadPartInfo(pACMHeader, pPartInfo+i, MID);
	}

	return true;
}

bool CLoadACMD::ReadGIM(unsigned char *pData, unsigned long MID, unsigned long TID) // 读取GIM块
{
	unsigned short	width	= pData[29]*256 + pData[28];
	unsigned short	height	= pData[31]*256 + pData[30];
	unsigned long	indexsize = width * height;

	unsigned char	*pIndex	= pData+32;
	CVector4B		*pPalette = (CVector4B *)(pIndex + indexsize + 16);

	unsigned short	TIM2[256];

	unsigned char	*pImage;

	pImage = new unsigned char [indexsize*4];

	for(unsigned short i=0; i<256; i+=32)
	{
		for(unsigned short j=0; j<8; j++)
		{
			TIM2[i+j] = i+j;
			TIM2[i+j+8] = i+j+16;
			TIM2[i+j+16] = i+j+8;
			TIM2[i+j+24] = i+j+24;
		}
	}
	if(mtype==0)
	for(unsigned long i=0; i<indexsize; i++)
	{
		pImage[i*4]=pPalette[TIM2[pIndex[i]]].r;
		pImage[i*4+1]=pPalette[TIM2[pIndex[i]]].g;
		pImage[i*4+2]=pPalette[TIM2[pIndex[i]]].b;
		pImage[i*4+3]=127+pPalette[TIM2[pIndex[i]]].a;
	}
	
	
	if(mtype==2)
	{
		for(unsigned long i=0; i<indexsize; i++)
		{
			if(pPalette[TIM2[pIndex[i]]].r*2>255)
				pImage[i*4]=255;
			else
				pImage[i*4]	= pPalette[TIM2[pIndex[i]]].r*2;

			if(pPalette[TIM2[pIndex[i]]].g*2>255)
				pImage[i*4+1]=255;
			else
				pImage[i*4+1] = pPalette[TIM2[pIndex[i]]].g*2;

			if(pPalette[TIM2[pIndex[i]]].b*2>255)
				pImage[i*4+2]=255;
			else
				pImage[i*4+2] = pPalette[TIM2[pIndex[i]]].b*2;


			if((pPalette[TIM2[pIndex[i]]].a*2)>255)
				pImage[i*4+3] = pPalette[TIM2[pIndex[i]]].a*2-1;
			else
				pImage[i*4+3] = 127+pPalette[TIM2[pIndex[i]]].a;
			pImage[i*4+3]=255;

				
		}
		
	}
	
	if(mtype==1)
	{
		for(unsigned long i=0; i<indexsize; i++)
		{
			if(pPalette[TIM2[pIndex[i]]].r*3/2>255)
				pImage[i*4]=255;
			else
				pImage[i*4]	= pPalette[TIM2[pIndex[i]]].r*3/2;

			if(pPalette[TIM2[pIndex[i]]].g*3/2>255)
				pImage[i*4+1]=255;
			else
				pImage[i*4+1] = pPalette[TIM2[pIndex[i]]].g*3/2;

			if(pPalette[TIM2[pIndex[i]]].b*3/2>255)
				pImage[i*4+2]=255;
			else
				pImage[i*4+2] = pPalette[TIM2[pIndex[i]]].b*3/2;


				pImage[i*4+3] = 255-pPalette[TIM2[pIndex[i]]].a/2;
			//pImage[i*4+3]=127;

				pImage[i*4+3]=255;

				
		}
		
	}

	

	/*for(unsigned long i=0; i<indexsize; i++)
	{
		//fprintf(m_DumpFilePointer, "%u:	%u	%u	%u	%u\n", i, pImage[i], pImage[i+1], pImage[i+2], pImage[i+3]);
		fputc(pImage[i*4], m_DumpFilePointer);
		fputc(pImage[i*4+1], m_DumpFilePointer);
		fputc(pImage[i*4+2], m_DumpFilePointer);
		fputc(pImage[i*4+3], m_DumpFilePointer);
	}*/

	//glGenTextures(1, &TEX);

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, ACMD[MID].texture[TID]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete pImage;

	return true;
}

