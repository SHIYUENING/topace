#include "Mathematics.h"
#include "VBMD.h"


using namespace std;

const unsigned int MAX_VBMD = 100;								// ���ģ������
tVBMD	VBMD[MAX_VBMD];								// VBMDģ������

// VBMD������
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

// VBMD������
CLoadVBMD::~CLoadVBMD()
{
	for(unsigned int i=0; i<MAX_VBMD; i++)
		CleanUpVBMD(i);

	if(m_FilePointer) 
		fclose(m_FilePointer);
}

// ���/��ʼ��ָ��VBMD
void CLoadVBMD::CleanUpVBMD(unsigned int MID)
{
	if(VBMD[MID].VertexCount && MID<MAX_VBMD)
	{
		
		// ɾ�����㻺��
		if( VBMD[MID].VBOVertices )
		{
			unsigned int nBuffers[3] = { VBMD[MID].VBOVertices, VBMD[MID].VBONormals, VBMD[MID].VBOTexCoords };
			glDeleteBuffersARB( 3, nBuffers );						// �ͷ��ڴ�
		}
		VBMD[MID].VBOVertices = VBMD[MID].VBONormals = VBMD[MID].VBOTexCoords = 0;

		// ɾ����ͼ
		if( VBMD[MID].TextureID )
		{
			glDeleteTextures(1, &VBMD[MID].TextureID);
			VBMD[MID].TextureID = 0;
		}

		// ɾ��������������
		if( VBMD[MID].pVertices )									// �ͷŶ�������
			delete [] VBMD[MID].pVertices;
		VBMD[MID].pVertices = NULL;
		if( VBMD[MID].pNormals )									// �ͷŷ�������
			delete [] VBMD[MID].pNormals;
		VBMD[MID].pNormals = NULL;
		if( VBMD[MID].pTexCoords )								// �ͷ�������������
			delete [] VBMD[MID].pTexCoords;
		VBMD[MID].pTexCoords = NULL;

		VBMD[MID].VertexCount = 0;
		TotalMid=TotalMid-1;
	}
	VBMD[MID].Islife=false;
	
}

int CLoadVBMD::Init(char *filename,bool UseTexture,GLint UserTexture)
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
		return 0;	// ����������

	CleanUpVBMD(MID);

	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return 0;	// ���ļ�ʧ��
	}

	// �����ļ���С
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
		return 0;	// �ļ����ʹ���
	
	if(filesize!=Header.Size)
		return 0;	// �ļ���С����

	if(filesize!=16+Header.VertexCount*(4*3*2+4*2))
		return 0;	// �ļ���С����

	VBMD[MID].VertexCount = Header.VertexCount;
	VBMD[MID].pTexCoords = new float[VBMD[MID].VertexCount*2];
	VBMD[MID].pNormals = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pVertices = new float[VBMD[MID].VertexCount*3];

	fread(VBMD[MID].pTexCoords, 4*2, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pNormals, 4*3, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pVertices, 4*3, VBMD[MID].VertexCount, m_FilePointer);

	fclose(m_FilePointer);

	// ������ͼ
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

			glGenTextures( 1, &VBMD[MID].TextureID );							// ��ȡ��ͼ���
			glBindTexture( GL_TEXTURE_2D, VBMD[MID].TextureID );				// ����ͼ
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
	if((MID<1)||(MID>=MAX_VBMD))
		return;
	if(VBOSupported)
	if(VBMD[MID].VertexCount && MID<MAX_VBMD)
	{
		// ���ɲ��󶨶��㻺��
		glGenBuffersARB( 1, &VBMD[MID].VBOVertices);					// ��ȡһ����Ч����VBO���
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOVertices );	// ��VBO
		// ��������
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pVertices, GL_STATIC_DRAW_ARB );

		// ���ɲ��󶨷��߻���
		glGenBuffersARB( 1, &VBMD[MID].VBONormals );					// ��ȡһ����Ч����VBO���
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBONormals );	// ��VBO
		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pNormals, GL_STATIC_DRAW_ARB );

		// ���ɲ�����ͼ������
		glGenBuffersARB( 1, &VBMD[MID].VBOTexCoords );					// ��ȡһ����Ч����VBO���
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTexCoords );	// ��VBO
		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*2*sizeof(float), VBMD[MID].pTexCoords, GL_STATIC_DRAW_ARB );

		// �ѽ���Ҫ�����ݸ��Ƶ��Կ���, ��Щ�����Ѿ�����
		delete [] VBMD[MID].pVertices; VBMD[MID].pVertices = NULL;
		delete [] VBMD[MID].pNormals; VBMD[MID].pNormals = NULL;
		delete [] VBMD[MID].pTexCoords; VBMD[MID].pTexCoords = NULL;
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
			glEnableClientState( GL_VERTEX_ARRAY );						// ������������
			glEnableClientState( GL_NORMAL_ARRAY );						// ������������
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// ����������������
			// ��������ָ��
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






void CLoadVBMD::TBN(void)
{
    Matrix44d UV;
    UV = TexCoordsInToTBN[0][0], TexCoordsInToTBN[1][0], TexCoordsInToTBN[2][0], 0,
         TexCoordsInToTBN[0][1], TexCoordsInToTBN[1][1], TexCoordsInToTBN[2][1], 0,
                              0,                      0,                      0, 1,
                              1,                      1,                      1, 0;

    float NormalInToTBN[3] = {0, 0, 0};

    Matrix44d XYZ;
    XYZ = VerticesInToTBN[0][0],  VerticesInToTBN[1][0],  VerticesInToTBN[2][0], NormalInToTBN[0],
          VerticesInToTBN[0][1],  VerticesInToTBN[1][1],  VerticesInToTBN[2][1], NormalInToTBN[1],
          VerticesInToTBN[0][2],  VerticesInToTBN[1][2],  VerticesInToTBN[2][2], NormalInToTBN[2],
                              1,                      1,                      1,                0;

    Matrix44d M;
    M = XYZ * inverse(UV);
    
    Vector4d TInTex;
    TInTex = 1, 0, 0, 0;

    Vector4d T;
    T = M * TInTex;

    TBNout[0] = T(0);
    TBNout[1] = T(1);
    TBNout[2] = T(2);
}
