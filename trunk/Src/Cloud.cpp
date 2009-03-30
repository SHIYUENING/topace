#include "Cloud.h"

CCloud::CCloud(void)
: CloudTexID(0)
,CloudsPos_index(0)
, CloudSize(500)
{
}

CCloud::~CCloud(void)
{
	glDeleteLists(base,16);
	glDeleteTextures(1,&CloudTexID);
}

bool CCloud::Init(void)
{

	for(int i=0;i<MAX_Cloud_NUM;i++)
	{
		CloudsPos[i].islife=false;
	
	}
	CDDS loadDDS;

	CloudTexID=loadDDS.loadCompressedTexture("Data/sky/Cloud.dds");
	if(CloudTexID==0)
		return false;
	else
	{
		float	cx;											// Holds Our X Character Coord
		float	cy;											// Holds Our Y Character Coord

		base=glGenLists(16);								// Creating 256 Display Lists
		glBindTexture(GL_TEXTURE_2D, CloudTexID);			// Select Our Font Texture
		for (int loop=0; loop<16; loop++)						// Loop Through All 256 Lists
		{
			cx=float(loop%4)/32.0f;						// X Position Of Current Character
			cy=float(loop/4)/32.0f;						// Y Position Of Current Character

			glNewList(base+loop,GL_COMPILE);				// Start Building A List	
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(cx,1-cy-0.25f);		// Texture Coord (Bottom Left)
					glVertex2f(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+0.25f,1-cy-0.25f);	// Texture Coord (Bottom Right)
					glVertex2f(CloudSize,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+0.25f,1-cy);			// Texture Coord (Top Right)
					glVertex2f(CloudSize,CloudSize);						// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
					glVertex2f(0,CloudSize);						// Vertex Coord (Top Left)
				glEnd();									// Done Building Our Quad (Character)
				glTranslated(10.0f,0.0f,0.0f);						// Move To The Right Of The Character
			glEndList();									// Done Building The Display List
		}	
	}
	return true;
}

void CCloud::SetCloudPos(float posx, float posy, float posz)
{
	addCloud(posx+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx+CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx-CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz+(float)(rand()%100-50),rand()%12+base);
		
	addCloud(posx+CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx+CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx-CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx-CloudSize/2.0f+(float)(rand()%100-50),posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50),rand()%12+base);

	addCloud(posx+CloudSize/4.0f+(float)(rand()%100-50),posy+CloudSize+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx+CloudSize/4.0f+(float)(rand()%100-50),posy+CloudSize+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx-CloudSize/4.0f+(float)(rand()%100-50),posy+CloudSize+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50),rand()%12+base);
	addCloud(posx-CloudSize/4.0f+(float)(rand()%100-50),posy+CloudSize+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50),rand()%12+base);

	addCloud(posx+CloudSize/4.0f+(float)(rand()%100-50),posy-CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50),rand()%4+base+12);
	addCloud(posx+CloudSize/4.0f+(float)(rand()%100-50),posy-CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50),rand()%4+base+12);
	addCloud(posx-CloudSize/4.0f+(float)(rand()%100-50),posy-CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50),rand()%4+base+12);
	addCloud(posx-CloudSize/4.0f+(float)(rand()%100-50),posy-CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50),rand()%4+base+12);


}

void CCloud::addCloud(float x, float y, float z,GLuint CloudID)
{
	int i=0;
	while(CloudsPos[i].islife)
	{
		i++; 
		if(i>=MAX_Cloud_NUM)
			return;
	
	}
	CloudsPos[i].islife=true;
	CloudsPos[i].Pos[0]=x;
	CloudsPos[i].Pos[1]=y;
	CloudsPos[i].Pos[2]=z;
	CloudsPos[i].CloudID=CloudID;
}

void CCloud::Draw(const Vector3d& ViewPos,Transform& would,float LookRenge)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, CloudTexID);
	for(int i=0;i<MAX_Cloud_NUM;i++)
	{
		if(CloudsPos[i].islife)
		{
			tmpx=CloudsPos[i].Pos[0]-(float)ViewPos(0);
			tmpy=CloudsPos[i].Pos[1]-(float)ViewPos(1);
			tmpz=CloudsPos[i].Pos[2]-(float)ViewPos(2);
			tmpl=tmpx*tmpx+tmpy*tmpy+tmpz*tmpz;
			if(tmpl>LookRenge*LookRenge*2)
				CloudsPos[i].islife=false;
			if(tmpl<LookRenge*LookRenge)
			{

				Pos3d=would.Matrix() * Vector3d(CloudsPos[i].Pos[0],CloudsPos[i].Pos[1],CloudsPos[i].Pos[2]) + would.RefPos();
				tmpAlpha=LookRenge+(float)Pos3d(2);
				if(tmpAlpha<LookRenge)
				{
					if(tmpAlpha>LookRenge*0.9f)
					{
						tmpAlpha=(tmpAlpha-LookRenge*0.9f)/(LookRenge*0.1f);
						tmpAlpha=1.0f-tmpAlpha;
					
					}
					if(tmpAlpha<LookRenge*0.1f)
					{
						tmpAlpha=tmpAlpha/(LookRenge*0.1f);
					
					}
					glPushMatrix();
					glLoadIdentity();
					glTranslated(Pos3d(0) , Pos3d(1) , Pos3d(2));
					glColor4f(1.0f,1.0f,1.0f,tmpAlpha);
					glCallList(CloudsPos[i].CloudID);
					glPopMatrix();
					glColor4f(1.0f,1.0f,1.0f,1.0f);
				}
			}
		}
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}
