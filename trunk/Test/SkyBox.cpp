#include "SkyBox.h"

CSkyBox::CSkyBox(void)
:IsSupportFBO(false)
//,SunTexID(0)
{
}

CSkyBox::~CSkyBox(void)
{
}

bool CSkyBox::Init(void)
{
	CDDS loadDDS;
	//SunTexID=loadDDS.loadCompressedTexture("Data/sky/sun.dds");
	SkyTexID[0]=loadDDS.loadCompressedTexture("Data/sky/BK.dds");
	SkyTexID[1]=loadDDS.loadCompressedTexture("Data/sky/DN.dds");
	SkyTexID[2]=loadDDS.loadCompressedTexture("Data/sky/FR.dds");
	SkyTexID[3]=loadDDS.loadCompressedTexture("Data/sky/LF.dds");
	SkyTexID[4]=loadDDS.loadCompressedTexture("Data/sky/RT.dds");
	SkyTexID[5]=loadDDS.loadCompressedTexture("Data/sky/UP.dds");

	return true;
}

void CSkyBox::Draw(void)
{
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, SkyTexID[2]);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		// ǰ��
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
	glEnd();
		// ����
		glBindTexture(GL_TEXTURE_2D, SkyTexID[0]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
	glEnd();
		// ����
		glBindTexture(GL_TEXTURE_2D, SkyTexID[5]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
	glEnd();
		// ����
		glBindTexture(GL_TEXTURE_2D, SkyTexID[1]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
	glEnd();
		// ����
		glBindTexture(GL_TEXTURE_2D, SkyTexID[4]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
	glEnd();
		// ����
		glBindTexture(GL_TEXTURE_2D, SkyTexID[3]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ı��ε�����
	glEnd();
	glEnable(GL_BLEND);
}
/*
void CSkyBox::DrawSun(float x,float y,float z,int winwidth,int winheight)
{
	glPushMatrix();	
	glLoadIdentity();
	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLdouble SUFwinX,SUFwinY,SUFwinZ;
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
	gluProject(x,y,z,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
	glPopMatrix();	

	if(SUFwinZ>1.0001)
		return;
	SUFwinX=SUFwinX-winwidth/2;
	SUFwinY=SUFwinY-winheight/2;
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-winwidth/2,winwidth/2,-winheight/2,winheight/2,-100,100);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix


	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, SunTexID);	

	//glTranslated(0,SUFwinY,0);


		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX-(float)(winwidth/10),(float)SUFwinY-(float)(winwidth/10));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(1.0f,0.5f)	;glVertex2f((float)SUFwinX+(float)(winwidth/10),(float)SUFwinY-(float)(winwidth/10));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(1.0f,1.0f)	;glVertex2f((float)SUFwinX+(float)(winwidth/10),(float)SUFwinY+(float)(winwidth/10));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.5f,1.0f)	;glVertex2f((float)SUFwinX-(float)(winwidth/10),(float)SUFwinY+(float)(winwidth/10));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.5f)	;glVertex2f((float)SUFwinX*0.75f-(float)(winwidth/20),(float)SUFwinY*0.75f-(float)(winwidth/20));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.75f+(float)(winwidth/20),(float)SUFwinY*0.75f-(float)(winwidth/20));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5f,1.0f)	;glVertex2f((float)SUFwinX*0.75f+(float)(winwidth/20),(float)SUFwinY*0.75f+(float)(winwidth/20));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,1.0f)	;glVertex2f((float)SUFwinX*0.75f-(float)(winwidth/20),(float)SUFwinY*0.75f+(float)(winwidth/20));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glColor4f(1.0f,1.0f,0.0f,1.0f);
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.5f)	;glVertex2f((float)SUFwinX*0.5f-(float)(winwidth/20),(float)SUFwinY*0.5f-(float)(winwidth/20));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.5f+(float)(winwidth/20),(float)SUFwinY*0.5f-(float)(winwidth/20));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5f,1.0f)	;glVertex2f((float)SUFwinX*0.5f+(float)(winwidth/20),(float)SUFwinY*0.5f+(float)(winwidth/20));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,1.0f)	;glVertex2f((float)SUFwinX*0.5f-(float)(winwidth/20),(float)SUFwinY*0.5f+(float)(winwidth/20));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glColor4f(0.0f,0.0f,1.0f,1.0f);
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.5f)	;glVertex2f((float)SUFwinX*0.25f-(float)(winwidth/20),(float)SUFwinY*0.25f-(float)(winwidth/20));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.25f+(float)(winwidth/20),(float)SUFwinY*0.25f-(float)(winwidth/20));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5f,1.0f)	;glVertex2f((float)SUFwinX*0.25f+(float)(winwidth/20),(float)SUFwinY*0.25f+(float)(winwidth/20));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,1.0f)	;glVertex2f((float)SUFwinX*0.25f-(float)(winwidth/20),(float)SUFwinY*0.25f+(float)(winwidth/20));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();
		glColor4f(1.0f,1.0f,1.0f,1.0f);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);	
}

*/