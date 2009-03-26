#include "Cloud.h"

CCloud::CCloud(void)
: CloudTexID(0)
,CloudsPos_index(0)
{
}

CCloud::~CCloud(void)
{
}

bool CCloud::Init(void)
{
	for(int i=0;i<1500;i++)
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
					glVertex2i(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+0.25f,1-cy-0.25f);	// Texture Coord (Bottom Right)
					glVertex2i(500,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+0.25f,1-cy);			// Texture Coord (Top Right)
					glVertex2i(500,500);						// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
					glVertex2i(0,500);						// Vertex Coord (Top Left)
				glEnd();									// Done Building Our Quad (Character)
				glTranslated(10.0f,0.0f,0.0f);						// Move To The Right Of The Character
			glEndList();									// Done Building The Display List
		}	
	}
	return true;
}

void CCloud::SetCloudPos(float posx, float posy, float posz)
{

}

void CCloud::addCloud(float x, float y, float z,GLuint CloudID)
{
	int i=0;
	while(CloudsPos[i].islife)
	{
		i++;
		if(i>=1500)
			return;
	
	}
	CloudsPos[i].islife=true;
	CloudsPos[i].Pos[0]=x;
	CloudsPos[i].Pos[1]=y;
	CloudsPos[i].Pos[2]=z;
}
