#include "SkyBox.h"

CSkyBox::CSkyBox(void)
:IsSupportFBO(false)
,SunTexID(0)
{
}

CSkyBox::~CSkyBox(void)
{
}

bool CSkyBox::Init(void)
{
	CDDS loadDDS;
	SunTexID=loadDDS.loadCompressedTexture("Data/sky/sun.dds");
	SkyTexID[0]=loadDDS.loadCompressedTexture("Data/sky/BK.dds");
	SkyTexID[1]=loadDDS.loadCompressedTexture("Data/sky/DN.dds");
	SkyTexID[2]=loadDDS.loadCompressedTexture("Data/sky/FR.dds");
	SkyTexID[3]=loadDDS.loadCompressedTexture("Data/sky/LF.dds");
	SkyTexID[4]=loadDDS.loadCompressedTexture("Data/sky/RT.dds");
	SkyTexID[5]=loadDDS.loadCompressedTexture("Data/sky/UP.dds");
	if(SkyTexID[0]==0)
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
		SkyTexID[0]=SkyTex[0].texID;
	
	}
	else
		return false;

	if(SkyTexID[1]==0)
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
		SkyTexID[1]=SkyTex[1].texID;
	
	}

	else
		return false;

	if(SkyTexID[2]==0)
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
		SkyTexID[2]=SkyTex[2].texID;
	
	}
	else
		return false;

	if(SkyTexID[3]==0)
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
		SkyTexID[3]=SkyTex[3].texID;
	
	}

	else
		return false;

	if(SkyTexID[4]==0)
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
		SkyTexID[4]=SkyTex[4].texID;
	
	}

	else
		return false;

	if(SkyTexID[5]==0)
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
		SkyTexID[5]=SkyTex[5].texID;
	
	}

	else
		return false;

	return true;
}

void CSkyBox::Draw(void)
{
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, SkyTexID[2]);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		// 前面
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
	glEnd();
		// 后面
		glBindTexture(GL_TEXTURE_2D, SkyTexID[0]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
	glEnd();
		// 顶面
		glBindTexture(GL_TEXTURE_2D, SkyTexID[5]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
	glEnd();
		// 底面
		glBindTexture(GL_TEXTURE_2D, SkyTexID[1]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
	glEnd();
		// 右面
		glBindTexture(GL_TEXTURE_2D, SkyTexID[4]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// 纹理和四边形的左上
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// 纹理和四边形的左下
	glEnd();
		// 左面
		glBindTexture(GL_TEXTURE_2D, SkyTexID[3]);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// 纹理和四边形的左上
	glEnd();
	glEnable(GL_BLEND);
}

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
/*
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.0f)	;glVertex2f((float)SUFwinX*0.75f-(float)(winwidth/10),(float)SUFwinY*0.75f-(float)(winwidth/10));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5f,0.0f)	;glVertex2f((float)SUFwinX*0.75f+(float)(winwidth/10),(float)SUFwinY*0.75f-(float)(winwidth/10));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.75f+(float)(winwidth/10),(float)SUFwinY*0.75f+(float)(winwidth/10));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,0.5f)	;glVertex2f((float)SUFwinX*0.75f-(float)(winwidth/10),(float)SUFwinY*0.75f+(float)(winwidth/10));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.5f)	;glVertex2f((float)SUFwinX*0.5f-(float)(winwidth/10),(float)SUFwinY*0.5f-(float)(winwidth/10));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.5f+(float)(winwidth/10),(float)SUFwinY*0.5f-(float)(winwidth/10));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5f,1.0f)	;glVertex2f((float)SUFwinX*0.5f+(float)(winwidth/10),(float)SUFwinY*0.5f+(float)(winwidth/10));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,1.0f)	;glVertex2f((float)SUFwinX*0.5f-(float)(winwidth/10),(float)SUFwinY*0.5f+(float)(winwidth/10));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.5f,0.0f)	;glVertex2f((float)SUFwinX*0.25f-(float)(winwidth/10),(float)SUFwinY*0.25f-(float)(winwidth/10));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(1.0f,0.0f)	;glVertex2f((float)SUFwinX*0.25f+(float)(winwidth/10),(float)SUFwinY*0.25f-(float)(winwidth/10));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(1.0f,0.5f)	;glVertex2f((float)SUFwinX*0.25f+(float)(winwidth/10),(float)SUFwinY*0.25f+(float)(winwidth/10));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.5f,0.5f)	;glVertex2f((float)SUFwinX*0.25f-(float)(winwidth/10),(float)SUFwinY*0.25f+(float)(winwidth/10));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();
		*/
/*
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0.5,0.5);	glVertex2i(-80,-80);						// Vertex Coord (Bottom Left)
				glTexCoord2f(1,0.5);	glVertex2i(80,-80);						// Vertex Coord (Bottom Right)
				glTexCoord2f(1,1);		glVertex2i(80,80);						// Vertex Coord (Top Right)
				glTexCoord2f(0.5,1);	glVertex2i(-80,80);						// Vertex Coord (Top Left)
			glEnd();
	
*/
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);	
}
