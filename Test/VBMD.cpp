#include "Mathematics.h"
#include "VBMD.h"


using namespace std;

const unsigned int MAX_VBMD = 300;						
tVBMD	VBMD[MAX_VBMD];							

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

CLoadVBMD::~CLoadVBMD()
{
	for(unsigned int i=0; i<MAX_VBMD; i++)
		CleanUpVBMD(i);

	if(m_FilePointer) 
		fclose(m_FilePointer);
}

void CLoadVBMD::CleanUpVBMD(unsigned int MID)
{
	if(VBMD[MID].VertexCount && MID<MAX_VBMD)
	{
		
		if( VBMD[MID].VBOVertices )
		{
			unsigned int nBuffers[3] = { VBMD[MID].VBOVertices, VBMD[MID].VBONormals, VBMD[MID].VBOTexCoords };
			glDeleteBuffersARB( 3, nBuffers );					
			if(VBMD[MID].UseTangentArray)
			{
				glDeleteBuffersARB(1,&VBMD[MID].VBOTangent);
			}
		}
		VBMD[MID].VBOTangent=0;

		VBMD[MID].VBOVertices = VBMD[MID].VBONormals = VBMD[MID].VBOTexCoords = 0;

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

		if( VBMD[MID].pVertices )								
			delete [] VBMD[MID].pVertices;
		VBMD[MID].pVertices = NULL;
		if( VBMD[MID].pNormals )								
			delete [] VBMD[MID].pNormals;
		VBMD[MID].pNormals = NULL;
		if( VBMD[MID].pTexCoords )							
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
		return 0;	

	CleanUpVBMD(MID);

	if ((m_FilePointer=fopen(filename,"rb"))==NULL)
	{
		return 0;	
	}

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
		return 0;	
	
	if(filesize!=Header.Size)
		return 0;	

	if(filesize!=16+Header.VertexCount*(4*3*2+4*2+4*3) && filesize!=16+Header.VertexCount*(4*3*2+4*2))
		return 0;	

	VBMD[MID].VertexCount = Header.VertexCount;
	VBMD[MID].pTexCoords = new float[VBMD[MID].VertexCount*2];
	VBMD[MID].pNormals = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pVertices = new float[VBMD[MID].VertexCount*3];
	VBMD[MID].pTangent = new float[VBMD[MID].VertexCount*3];

	fread(VBMD[MID].pTexCoords, 4*2, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pNormals, 4*3, VBMD[MID].VertexCount, m_FilePointer);
	fread(VBMD[MID].pVertices, 4*3, VBMD[MID].VertexCount, m_FilePointer);

	bool tangent=false; 	
	if(filesize==16+Header.VertexCount*(4*3*2+4*2+4*3)) 
	{
	fread(VBMD[MID].pTangent,4*3,VBMD[MID].VertexCount, m_FilePointer);
	tangent=true;
	}

	

	fclose(m_FilePointer);

	VBMD[MID].UseTangentArray=UseTangent;

	if((UserTexture==0)&&UseTexture)
	{
		CDDS ddsload;
		char TextureDDSFileName[256] = {0};
		sprintf(&TextureDDSFileName[0], "%s.dds", filename);
		int ddsTexId=ddsload.loadCompressedTexture(TextureDDSFileName);


		if(ddsTexId>0)
		{
			VBMD[MID].TextureID=ddsTexId;
			for(unsigned int i=0;i<VBMD[MID].VertexCount;i++)
			{
				if((i*2+1)<(VBMD[MID].VertexCount*2))
				VBMD[MID].pTexCoords[i*2+1]=1.0f-VBMD[MID].pTexCoords[i*2+1];
			
			}
		
		}
		else
		{

			char TextureFileName[256] = {0};
			sprintf(&TextureFileName[0], "%s.bmp", filename);

			AUX_RGBImageRec* pTextureImage;
			pTextureImage = auxDIBImageLoad( (char*)TextureFileName );	

			glGenTextures( 1, &VBMD[MID].TextureID );							
			glBindTexture( GL_TEXTURE_2D, VBMD[MID].TextureID );			
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
		char NormalTexDDSFileName[256] = {0};
		sprintf(&NormalTexDDSFileName[0], "%s_N.dds", filename);
		VBMD[MID].NormalTexID=ddsload.loadCompressedTexture(NormalTexDDSFileName);
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
		if(tangent==false)	

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

				TexCoordsInToTBN[0][0]=VBMD[MID].pTexCoords[i*2+0];
				TexCoordsInToTBN[0][1]=VBMD[MID].pTexCoords[i*2+1];

				TexCoordsInToTBN[1][0]=VBMD[MID].pTexCoords[(i+1)*2+0];
				TexCoordsInToTBN[1][1]=VBMD[MID].pTexCoords[(i+1)*2+1];

				TexCoordsInToTBN[2][0]=VBMD[MID].pTexCoords[(i+2)*2+0];
				TexCoordsInToTBN[2][1]=VBMD[MID].pTexCoords[(i+2)*2+1];
				TBN();
				VBMD[MID].pTangent[i*3+0]=TBNout[0];
				VBMD[MID].pTangent[i*3+1]=TBNout[1];
				VBMD[MID].pTangent[i*3+2]=TBNout[2];

				VBMD[MID].pTangent[(i+1)*3+0]=TBNout[0];
				VBMD[MID].pTangent[(i+1)*3+1]=TBNout[1];
				VBMD[MID].pTangent[(i+1)*3+2]=TBNout[2];

				VBMD[MID].pTangent[(i+2)*3+0]=TBNout[0];
				VBMD[MID].pTangent[(i+2)*3+1]=TBNout[1];
				VBMD[MID].pTangent[(i+2)*3+2]=TBNout[2];
			}
		
		}
		//*/
	}

	if(tangent)
		VBMD[MID].UseTangentArray=true;
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
		glGenBuffersARB( 1, &VBMD[MID].VBOVertices);					
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOVertices );	
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pVertices, GL_STATIC_DRAW_ARB );

		glGenBuffersARB( 1, &VBMD[MID].VBONormals );					
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBONormals );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pNormals, GL_STATIC_DRAW_ARB );

		glGenBuffersARB( 1, &VBMD[MID].VBOTexCoords );					
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTexCoords );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*2*sizeof(float), VBMD[MID].pTexCoords, GL_STATIC_DRAW_ARB );

		if(VBMD[MID].UseTangentArray)
		{
			glGenBuffersARB( 1, &VBMD[MID].VBOTangent);					
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VBOTangent );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, VBMD[MID].VertexCount*3*sizeof(float), VBMD[MID].pTangent, GL_STATIC_DRAW_ARB );
		}

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
			glEnableClientState( GL_VERTEX_ARRAY );					
			glEnableClientState( GL_NORMAL_ARRAY );					
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
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
					glEnableClientState( GL_COLOR_ARRAY );
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

			glDisableClientState( GL_COLOR_ARRAY );
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

    TBNout[0] = (float)T(0);
    TBNout[1] = (float)T(1);
    TBNout[2] = (float)T(2);
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
