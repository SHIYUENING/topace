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
		}
		VBMD[MID].VBOVertices = VBMD[MID].VBONormals = VBMD[MID].VBOTexCoords = 0;

		// 删除贴图
		if( VBMD[MID].TextureID )
		{
			glDeleteTextures(1, &VBMD[MID].TextureID);
			VBMD[MID].TextureID = 0;
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

int CLoadVBMD::Init(char *filename,bool UseTexture,GLint UserTexture)
{
	ModelId=0;

	while(VBMD[ModelId].Islife)
	{
		if(ModelId>=MAX_VBMD)
			return -1;
		else
			ModelId=ModelId+1;
	}
	int	MID=ModelId;
	if(MID>=MAX_VBMD)
		return -1;	// 超出最大个数

	CleanUpVBMD(MID);

	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return -1;	// 打开文件失败
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
		return -1;	// 文件类型错误
	
	if(filesize!=Header.Size)
		return -1;	// 文件大小错误

	if(filesize!=16+Header.VertexCount*(4*3*2+4*2))
		return -1;	// 文件大小错误

	VBMD[MID].VertexCount = Header.VertexCount;
	VBMD[MID].pTexCoords = new float[VBMD[MID].VertexCount*2];
	VBMD[MID].pNormals = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pVertices = new float[VBMD[MID].VertexCount*3];

	fread(VBMD[MID].pTexCoords, 4*2, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pNormals, 4*3, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pVertices, 4*3, VBMD[MID].VertexCount, m_FilePointer);

	fclose(m_FilePointer);

	// 载入贴图
	if((UserTexture==0)&&UseTexture)
	{
		char TextureDDSFileName[256] = {0};
		sprintf(&TextureDDSFileName[0], "%s.dds", filename);
		CDDS ddsload;
		int ddsTexId=ddsload.loadCompressedTexture(TextureDDSFileName);
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
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			}

			delete pTextureImage;
		}
	}
	else
		VBMD[MID].TextureID=UserTexture;
	TotalMid=TotalMid+1;
	BuildVBO(MID);
	VBMD[MID].Islife=true;
	return MID;

}

void CLoadVBMD::BuildVBO(unsigned int MID)
{
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

		// 已将需要的数据复制到显卡中, 这些数据已经无用
		delete [] VBMD[MID].pVertices; VBMD[MID].pVertices = NULL;
		delete [] VBMD[MID].pNormals; VBMD[MID].pNormals = NULL;
		delete [] VBMD[MID].pTexCoords; VBMD[MID].pTexCoords = NULL;
	}
}
bool CLoadVBMD::ShowVBMD(unsigned int MID,bool BindSelfTexture)
{
	if(VBMD[MID].Islife)
	{
		if(VBMD[MID].VertexCount && MID<MAX_VBMD)
		{
		
			if(BindSelfTexture)
			glBindTexture( GL_TEXTURE_2D, VBMD[MID].TextureID );	 
			glEnableClientState( GL_VERTEX_ARRAY );						// 开启顶点数组
			glEnableClientState( GL_NORMAL_ARRAY );						// 开启法线数组
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// 开启纹理坐标数组
			// 设置数据指针
			if( VBMD[MID].VBOVertices && VBOSupported ) 
			{
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOVertices );
				glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBONormals );
				glNormalPointer( GL_FLOAT, 0, (char *) NULL );		// Set The Vertex Pointer To The Vertex Buffer
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTexCoords );
				glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );		// Set The TexCoord Pointer To The TexCoord Buffer
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
		}
		return true;
	}
	else
		return false;
}





