#include "Mathematics.h"
#include "VBMD.h"


using namespace std;

const unsigned int MAX_VBMD = 100;								// 最大模型数量
tVBMD	VBMD[MAX_VBMD];								// VBMD模型数据

// VBMD构造器
CLoadVBMD::CLoadVBMD()
:TotalMid(0)
,ModelId(0)
{	
	if (glewIsSupported("GL_ARB_vertex_buffer_object"))
		VBOSupported=true;
	else
		VBOSupported=false;

	for(unsigned int i=0; i<MAX_VBMD; i++)
	{
		VBMD[i].NormalTexID=0;	
		VBMD[i].SpecularTexID=0;	
		VBMD[i].TextureID=0;	
		VBMD[i].UseTangentArray=false;	
		VBMD[i].VBONormals=0;
		VBMD[i].VBOTangent=0;
		VBMD[i].VBOTexCoords=0;
		VBMD[i].VBOVertices=0;
		VBMD[i].VertexCount=0;
	}

	for(unsigned int i=0; i<MAX_VBMD; i++)
		CleanUpVBMD(i);

	m_FilePointer= new FILE;	
	memset(m_FilePointer, NULL, sizeof(FILE));
}

// VBMD析构器
CLoadVBMD::~CLoadVBMD()
{
	for(unsigned int i=0; i<MAX_VBMD; i++)
		CleanUpVBMD(i);

	if(m_FilePointer) 
		fclose(m_FilePointer);
}

// 清除/初始化指定VBMD
void CLoadVBMD::CleanUpVBMD(unsigned int MID)
{
	if(VBMD[MID].VertexCount && MID<MAX_VBMD)
	{
		
		// 删除顶点缓存
		if( VBMD[MID].VBOVertices )
		{
			unsigned int nBuffers[3] = { VBMD[MID].VBOVertices, VBMD[MID].VBONormals, VBMD[MID].VBOTexCoords };
			glDeleteBuffersARB( 3, nBuffers );						// 释放内存
			if(VBMD[MID].UseTangentArray)
			{
				glDeleteBuffersARB(1,&VBMD[MID].VBOTangent);
			}
		}
		VBMD[MID].VBOTangent=0;

		VBMD[MID].VBOVertices = VBMD[MID].VBONormals = VBMD[MID].VBOTexCoords = 0;

		// 删除贴图
		if( VBMD[MID].TextureID )
		{
			glDeleteTextures(1, &VBMD[MID].TextureID);
			VBMD[MID].TextureID = 0;
		}

		if( VBMD[MID].NormalTexID )
		{
			glDeleteTextures(1, &VBMD[MID].NormalTexID);
			VBMD[MID].NormalTexID = 0;
		}

		if( VBMD[MID].SpecularTexID )
		{
			glDeleteTextures(1, &VBMD[MID].SpecularTexID);
			VBMD[MID].SpecularTexID = 0;
		}

		// 删除顶点数组数据
		if( VBMD[MID].pVertices )									// 释放顶点数据
			delete [] VBMD[MID].pVertices;
		VBMD[MID].pVertices = NULL;
		if( VBMD[MID].pNormals )									// 释放法线数据
			delete [] VBMD[MID].pNormals;
		VBMD[MID].pNormals = NULL;
		if( VBMD[MID].pTexCoords )								// 释放纹理坐标数据
			delete [] VBMD[MID].pTexCoords;
		VBMD[MID].pTexCoords = NULL;

		VBMD[MID].VertexCount = 0;
		TotalMid=TotalMid-1;
	}
	VBMD[MID].Islife=false;
	
}

int CLoadVBMD::Init(char *filename,bool UseTexture,GLint UserTexture,bool UseTangent)
{
	ModelId=1;

	while(VBMD[ModelId].Islife)
	{
		if(ModelId>=MAX_VBMD)
			return 0;
		else
			ModelId=ModelId+1;
	}
	int	MID=ModelId;
	if(MID>=MAX_VBMD)
		return 0;	// 超出最大个数

	CleanUpVBMD(MID);

	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return 0;	// 打开文件失败
	}

	// 计算文件大小
	unsigned int filesize = 0;
	while (!feof(m_FilePointer))
	{
		fgetc(m_FilePointer);
		filesize++;
	}
	filesize--;
	rewind(m_FilePointer);

	tVBMDHeader Header;
	fread(&Header, sizeof(tVBMDHeader), 1, m_FilePointer);

	if(Header.MAGIC[0]!='V' || Header.MAGIC[1]!='B' || Header.MAGIC[2]!='M')
		return 0;	// 文件类型错误
	
	if(filesize!=Header.Size)
		return 0;	// 文件大小错误

	if(filesize!=16+Header.VertexCount*(4*3*2+4*2+4*3) && filesize!=16+Header.VertexCount*(4*3*2+4*2))
		return 0;	// 文件大小错误

	VBMD[MID].VertexCount = Header.VertexCount;
	VBMD[MID].pTexCoords = new float[VBMD[MID].VertexCount*2];
	VBMD[MID].pNormals = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pVertices = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pTangent = new float[VBMD[MID].VertexCount*3];

	fread(VBMD[MID].pTexCoords, 4*2, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pNormals, 4*3, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pVertices, 4*3, VBMD[MID].VertexCount, m_FilePointer);

	bool tangent; //模型切线信息	
	if(filesize==16+Header.VertexCount*(4*3*2+4*2+4*3)) //读取切线信息	
	{
	fread(VBMD[MID].pTangent,4*3,VBMD[MID].VertexCount, m_FilePointer);
	tangent=true;
	}

	

	fclose(m_FilePointer);

	VBMD[MID].UseTangentArray=UseTangent;

	// 载入贴图
	if((UserTexture==0)&&UseTexture)
	{
		CDDS ddsload;
		char TextureDDSFileName[256] = {0};
		sprintf(&TextureDDSFileName[0], "%s.dds", filename);
		int ddsTexId=0;
		if(m_IsSupportFBO)
			ddsTexId=ddsload.loadCompressedTexture(TextureDDSFileName);


		if(ddsTexId>0)
		{
			VBMD[MID].TextureID=ddsTexId;


		
		}
		else
		{

			char TextureFileName[256] = {0};
			sprintf(&TextureFileName[0], "%s.bmp", filename);

			AUX_RGBImageRec* pTextureImage;
			pTextureImage = auxDIBImageLoad( (char*)TextureFileName );	

			glGenTextures( 1, &VBMD[MID].TextureID );							// 获取贴图编号
			glBindTexture( GL_TEXTURE_2D, VBMD[MID].TextureID );				// 绑定贴图
			glTexImage2D( GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data );
			if(VBOSupported&&m_IsSupportFBO)
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			}

			delete pTextureImage;
		}
		char NormalTexDDSFileName[256] = {0};
		sprintf(&NormalTexDDSFileName[0], "%s_N.dds", filename);
		VBMD[MID].NormalTexID=ddsload.loadCompressedTexture(NormalTexDDSFileName,GL_LINEAR);
		if(VBMD[MID].NormalTexID>0)
		{
			VBMD[MID].UseTangentArray=true;
		
		}
		else
		{
			VBMD[MID].UseTangentArray=false;
		}

		char SpecularTexDDSFileName[256] = {0};
		sprintf(&SpecularTexDDSFileName[0], "%s_S.dds", filename);
		VBMD[MID].SpecularTexID=ddsload.loadCompressedTexture(SpecularTexDDSFileName);
	}
	else
		VBMD[MID].TextureID=UserTexture;

	if(VBMD[MID].UseTangentArray)
	{
			for(unsigned int i=0;i<VBMD[MID].VertexCount;i++)
			{
				if((i*2+1)<(VBMD[MID].VertexCount*2))
				VBMD[MID].pTexCoords[i*2+1]=1.0f-VBMD[MID].pTexCoords[i*2+1];
			
			}
		//*
		//if(tangent==false)	//模型不含切线信息	

		for(unsigned int i=0;i<VBMD[MID].VertexCount;i=i+3)
		{
			if(((i+1)*3+2)<(VBMD[MID].VertexCount*3))
			{
				VerticesInToTBN[0][0]=VBMD[MID].pVertices[i*3+0];
				VerticesInToTBN[0][1]=VBMD[MID].pVertices[i*3+1];
				VerticesInToTBN[0][2]=VBMD[MID].pVertices[i*3+2];

				VerticesInToTBN[1][0]=VBMD[MID].pVertices[(i+1)*3+0];
				VerticesInToTBN[1][1]=VBMD[MID].pVertices[(i+1)*3+1];
				VerticesInToTBN[1][2]=VBMD[MID].pVertices[(i+1)*3+2];

				VerticesInToTBN[2][0]=VBMD[MID].pVertices[(i+2)*3+0];
				VerticesInToTBN[2][1]=VBMD[MID].pVertices[(i+2)*3+1];
				VerticesInToTBN[2][2]=VBMD[MID].pVertices[(i+2)*3+2];

				NormalsInToTBN[0][0]=VBMD[MID].pNormals[i*3+0];
				NormalsInToTBN[0][1]=VBMD[MID].pNormals[i*3+1];
				NormalsInToTBN[0][2]=VBMD[MID].pNormals[i*3+2];

				NormalsInToTBN[1][0]=VBMD[MID].pNormals[(i+1)*3+0];
				NormalsInToTBN[1][1]=VBMD[MID].pNormals[(i+1)*3+1];
				NormalsInToTBN[1][2]=VBMD[MID].pNormals[(i+1)*3+2];

				NormalsInToTBN[2][0]=VBMD[MID].pNormals[(i+2)*3+0];
				NormalsInToTBN[2][1]=VBMD[MID].pNormals[(i+2)*3+1];
				NormalsInToTBN[2][2]=VBMD[MID].pNormals[(i+2)*3+2];

				TexCoordsInToTBN[0][0]=VBMD[MID].pTexCoords[i*2+0];
				TexCoordsInToTBN[0][1]=VBMD[MID].pTexCoords[i*2+1];

				TexCoordsInToTBN[1][0]=VBMD[MID].pTexCoords[(i+1)*2+0];
				TexCoordsInToTBN[1][1]=VBMD[MID].pTexCoords[(i+1)*2+1];

				TexCoordsInToTBN[2][0]=VBMD[MID].pTexCoords[(i+2)*2+0];
				TexCoordsInToTBN[2][1]=VBMD[MID].pTexCoords[(i+2)*2+1];
				TBN();
				VBMD[MID].pTangent[i*3+0]=TBNout[0][0];
				VBMD[MID].pTangent[i*3+1]=TBNout[0][1];
				VBMD[MID].pTangent[i*3+2]=TBNout[0][2];

				VBMD[MID].pTangent[(i+1)*3+0]=TBNout[1][0];
				VBMD[MID].pTangent[(i+1)*3+1]=TBNout[1][1];
				VBMD[MID].pTangent[(i+1)*3+2]=TBNout[1][2];

				VBMD[MID].pTangent[(i+2)*3+0]=TBNout[2][0];
				VBMD[MID].pTangent[(i+2)*3+1]=TBNout[2][1];
				VBMD[MID].pTangent[(i+2)*3+2]=TBNout[2][2];
			}
		
		}
		//*/
	}

	TotalMid=TotalMid+1;
	BuildVBO(MID);
	VBMD[MID].Islife=true;
	return MID;

}

void CLoadVBMD::BuildVBO(unsigned int MID)
{
	if((MID<1)||(MID>=MAX_VBMD))
		return;
	if(VBOSupported)
	if(VBMD[MID].VertexCount && MID<MAX_VBMD)
	{
		// 生成并绑定顶点缓存
		glGenBuffersARB( 1, &VBMD[MID].VBOVertices);					// 获取一个有效顶点VBO编号
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOVertices );	// 绑定VBO
		// 加载数据
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pVertices, GL_STATIC_DRAW_ARB );

		// 生成并绑定法线缓存
		glGenBuffersARB( 1, &VBMD[MID].VBONormals );					// 获取一个有效顶点VBO编号
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBONormals );	// 绑定VBO
		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pNormals, GL_STATIC_DRAW_ARB );

		// 生成并绑定贴图纹理缓存
		glGenBuffersARB( 1, &VBMD[MID].VBOTexCoords );					// 获取一个有效顶点VBO编号
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTexCoords );	// 绑定VBO
		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*2*sizeof(float), VBMD[MID].pTexCoords, GL_STATIC_DRAW_ARB );

		if(VBMD[MID].UseTangentArray)
		{
			glGenBuffersARB( 1, &VBMD[MID].VBOTangent);					// 获取一个有效顶点VBO编号
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTangent );	// 绑定VBO
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pTangent, GL_STATIC_DRAW_ARB );
		}

		// 已将需要的数据复制到显卡中, 这些数据已经无用
		delete [] VBMD[MID].pVertices; VBMD[MID].pVertices = NULL;
		delete [] VBMD[MID].pNormals; VBMD[MID].pNormals = NULL;
		delete [] VBMD[MID].pTexCoords; VBMD[MID].pTexCoords = NULL;
		delete [] VBMD[MID].pTangent; VBMD[MID].pTangent = NULL;
	}
}
bool CLoadVBMD::ShowVBMD(unsigned int MID,bool BindSelfTexture)
{
	if((MID<1)||(MID>=MAX_VBMD))
		return false;
	if(VBMD[MID].Islife)
	{
		if(VBMD[MID].VertexCount && MID<MAX_VBMD)
		{
		
			if(BindSelfTexture)
			glBindTexture( GL_TEXTURE_2D, VBMD[MID].TextureID );	 
			glEnableClientState( GL_VERTEX_ARRAY );						// 开启顶点数组
			glEnableClientState( GL_NORMAL_ARRAY );						// 开启法线数组
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// 开启纹理坐标数组
			if(VBMD[MID].UseTangentArray)
				glEnableClientState( GL_COLOR_ARRAY );
			// 设置数据指针
			if( VBMD[MID].VBOVertices && VBOSupported ) 
			{
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOVertices );
				glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBONormals );
				glNormalPointer( GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTexCoords );
				glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );		// Set The TexCoord Pointer To The TexCoord Buffer
				if(VBMD[MID].UseTangentArray)
				{
					glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTangent );
					glColorPointer( 3, GL_FLOAT, 0, (char *) NULL );		// Set The TexCoord Pointer To The TexCoord Buffer
				}
			}
			else
			{
				glVertexPointer( 3, GL_FLOAT, 0, VBMD[MID].pVertices ); // Set The Vertex Pointer To Our Vertex Data
				glNormalPointer( GL_FLOAT, 0, VBMD[MID].pNormals );
				glTexCoordPointer( 2, GL_FLOAT, 0, VBMD[MID].pTexCoords ); // Set The Vertex Pointer To Our TexCoord Data
			}
			// Render
			glDrawArrays( GL_TRIANGLES, 0, VBMD[MID].VertexCount );	// Draw All Of The Triangles At Once

			// Disable Pointers
			glDisableClientState( GL_VERTEX_ARRAY );					// Disable Vertex Arrays
			glDisableClientState( GL_NORMAL_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );				// Disable Texture Coord Arrays
			if(VBMD[MID].UseTangentArray)
				glDisableClientState( GL_COLOR_ARRAY );	
		}
		return true;
	}
	else
		return false;
}






void CLoadVBMD::TBN(void)
{
    Matrix44d UV;
    UV = TexCoordsInToTBN[0][0], TexCoordsInToTBN[1][0], TexCoordsInToTBN[2][0], 0,
         TexCoordsInToTBN[0][1], TexCoordsInToTBN[1][1], TexCoordsInToTBN[2][1], 0,
                              0,                      0,                      0, 1,
                              1,                      1,                      1, 0;
    Vector3d AB;
    AB = VerticesInToTBN[1][0] - VerticesInToTBN[0][0],
         VerticesInToTBN[1][1] - VerticesInToTBN[0][1],
         VerticesInToTBN[1][2] - VerticesInToTBN[0][2];

    Vector3d AC;
    AC = VerticesInToTBN[2][0] - VerticesInToTBN[0][0],
         VerticesInToTBN[2][1] - VerticesInToTBN[0][1],
         VerticesInToTBN[2][2] - VerticesInToTBN[0][2];
    
    Vector3d n;
    n = normalize(cross(AB, AC));

    Matrix44d XYZ;
    XYZ = VerticesInToTBN[0][0],  VerticesInToTBN[1][0],  VerticesInToTBN[2][0], n(0),
          VerticesInToTBN[0][1],  VerticesInToTBN[1][1],  VerticesInToTBN[2][1], n(1),
          VerticesInToTBN[0][2],  VerticesInToTBN[1][2],  VerticesInToTBN[2][2], n(2),
                              1,                      1,                      1,    0;

    Matrix44d M;
    M = XYZ * inverse(UV);
    
    Vector4d TInTex;
    TInTex = 1, 0, 0, 0;

    Vector4d T;
    T = M * TInTex;
	Vector3d TOut,ONormal[3];
	TOut=Vector3d(T(0),T(1),T(2));

	for(int i=0;i<3;i++)
	{
		ONormal[i]=normalize(Vector3d(NormalsInToTBN[i][0],NormalsInToTBN[i][1],NormalsInToTBN[i][2]));
		TOut = TOut - ONormal[i] * dot(ONormal[i], TOut);

		TBNout[i][0] = (float)TOut(0);
		TBNout[i][1] = (float)TOut(1);
		TBNout[i][2] = (float)TOut(2);
	}
}

unsigned int CLoadVBMD::GetTextureID(int MID)
{
	return VBMD[MID].TextureID;
}
unsigned int CLoadVBMD::GetNormalTexID(int MID)
{
	return VBMD[MID].NormalTexID;
}
unsigned int CLoadVBMD::GetSpecularTexID(int MID)
{
	return VBMD[MID].SpecularTexID;
}
