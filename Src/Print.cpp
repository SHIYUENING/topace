#include "HUDUI.h"
#include "DDS.h"
GLuint AsciiFontTexId;
GLuint base;
extern int winwidth,winheight;
extern GLuint LockTexID,PlayerSign;
void BuildFont()								// Build Our Font Display List
{
	/*
	if (LoadTGA(&textureAlphaFont[0], "Data/font.tga"))
	{											


			// Typical Texture Generation Using Data From The TGA ( CHANGE )textureAlphaFontFont[1]
			glGenTextures(1, &textureAlphaFont[0].texID);				// Create The Texture ( CHANGE )
			glBindTexture(GL_TEXTURE_2D, textureAlphaFont[0].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, textureAlphaFont[0].bpp / 8, textureAlphaFont[0].width, textureAlphaFont[0].height, 0, textureAlphaFont[0].type, GL_UNSIGNED_BYTE, textureAlphaFont[0].imageData);
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

			if (textureAlphaFont[0].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(textureAlphaFont[0].imageData);					// Free The Texture Image Memory ( CHANGE )
			}

	}
*/
	CDDS loadDDS;
	AsciiFontTexId=loadDDS.loadCompressedTexture("Data/Font.dds");

	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord

	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, AsciiFontTexId);			// Select Our Font Texture
	for (int loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List	
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx+0.015625f,1.0f-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f+0.015625f,1.0f-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f+0.015625f,1.0f-cy);			// Texture Coord (Top Right)
				glVertex2i(16,16);						// Vertex Coord (Top Right)
				glTexCoord2f(cx+0.015625f,1.0f-cy);					// Texture Coord (Top Left)
				glVertex2i(0,16);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(10.0f,0.0f,0.0f);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
}
void glPrint(int x, int y, char *string, int set,bool isover800_600)	// Where The Printing Happens
{
	if(isover800_600)
	{
		x=x*800/winwidth;
		y=y*600/winheight;
	}
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	if (set>1)
	{
		set=1;
	}
	glBindTexture(GL_TEXTURE_2D, AsciiFontTexId);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	if(isover800_600)
		glOrtho(0,800,0,600,-1,1);	
	else
		glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)

	glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	/*glLoadIdentity();
	glTranslated(wx,wy,0);
		glBegin(GL_QUADS);							
			glVertex3f(-0.1f, 0.1f, -0.1f);			
			glVertex3f( 0.1f, 0.1f, -0.1f);		
			glVertex3f( 0.1f,-0.1f, -0.1f);			
			glVertex3f(-0.1f,-0.1f, -0.1f);				
		glEnd();*/
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

void glPrints(int x, int y, int winW,int winH,char *string)	// Where The Printing Happens
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );

	glBindTexture(GL_TEXTURE_2D, AsciiFontTexId);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winW,0,winH,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)

	glListBase(base-32);						// Choose The Font Set (0 or 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
//绘制绿色的目标框或者红色的锁定框，每桢可以同时多次绘制
void glPrintW(float HUDx,float HUDy, bool locked)	// Where The Printing Happens
{

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glBindTexture(GL_TEXTURE_2D, LockTexID);	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	

	
	glTranslated(HUDx,HUDy,0);
	glScaled((float)winheight/600.0,(float)winheight/600.0,(float)winheight/600.0);
	if(locked)
	{
		
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0.5,0.5);			// Texture Coord (Bottom Left)
				glVertex2i(-8,-8);						// Vertex Coord (Bottom Left)
				glTexCoord2f(1,0.5);	// Texture Coord (Bottom Right)
				glVertex2i(8,-8);						// Vertex Coord (Bottom Right)
				glTexCoord2f(1,1);			// Texture Coord (Top Right)
				glVertex2i(8,8);						// Vertex Coord (Top Right)
				glTexCoord2f(0.5,1);					// Texture Coord (Top Left)
				glVertex2i(-8,8);						// Vertex Coord (Top Left)
			glEnd();
	}
	else
	{
		//glTranslated(wx-8.0,wy-8.0,0);
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0,0.5);			// Texture Coord (Bottom Left)
				glVertex2i(-8,-8);						// Vertex Coord (Bottom Left)
				glTexCoord2f(0.5,0.5);	// Texture Coord (Bottom Right)
				glVertex2i(8,-8);						// Vertex Coord (Bottom Right)
				glTexCoord2f(0.5,1);			// Texture Coord (Top Right)
				glVertex2i(8,8);						// Vertex Coord (Top Right)
				glTexCoord2f(0,1);					// Texture Coord (Top Left)
				glVertex2i(-8,8);						// Vertex Coord (Top Left)
			glEnd();
	
	}


	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}
void glPrintRedar(float Rx,float Ry, int TGTflag,float Renge)	// Where The Printing Happens
{
	
	glBindTexture(GL_TEXTURE_2D, LockTexID);	
	
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glTranslated(Rx*256.0f/(Renge*2.0f)+122.5,Ry*256.0f/(Renge*2.0f)+122.5,0);
	if(TGTflag==0)
		glColor3f(0.0f,1.0f,0.0f);
	if(TGTflag==1)
		glColor3f(1.0f,0.0f,0.0f);
	if(TGTflag==2)
		glColor3f(0.0f,0.0f,1.0f);
	if(TGTflag==3)
		glColor3f(1.0f,1.0f,0.0f);
		

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_COLOR   );
	

		/*
			glBegin(GL_QUADS);							// Use A Quad For Each Character

				glTexCoord2f(0.1f,0.1f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(0.4f,0.1f);	// Texture Coord (Bottom Right)
				glVertex2i(8,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(0.4f,0.4f);			// Texture Coord (Top Right)
				glVertex2i(8,8);						// Vertex Coord (Top Right)
				glTexCoord2f(0.1f,0.4f);					// Texture Coord (Top Left)
				glVertex2i(0,8);						// Vertex Coord (Top Left)
			glEnd();
*/
	glEnable(GL_POINT_SMOOTH);

	glDisable(GL_TEXTURE_2D);
	glPointSize(7.0);
	glBegin(GL_POINTS);
	glVertex2i(4,4);
	glEnd();

	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_POINT_SMOOTH);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	
}
void glPrintAREARedar(float Rx,float Ry, int TGTflag,float Renge,float turn)	// Where The Printing Happens
{
	
	glBindTexture(GL_TEXTURE_2D, LockTexID);	
	
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	int posX=(int)(Rx*winheight/(Renge*2.5)*(0.99-0.0050));
	int posY=(int)(Ry*winheight/(Renge*2.5)+winheight*0.03);
	if(TGTflag==4)
		//glOrtho(-posX,winwidth-posX,-posY,winheight-posY,-1,1);	
		glOrtho(-posX-winwidth/2,winwidth/2-posX,-posY-winheight/2,winheight/2-posY,-1,1);	
		
	else
		glOrtho(-winwidth/2,winwidth/2,-winheight/2,winheight/2,-1,1);	
								// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	if(TGTflag!=4)
	glTranslated(posX,posY,0);
	glEnable(GL_BLEND);
	if(TGTflag==0)
		glColor3f(0.0f,1.0f,0.0f);
	if(TGTflag==1)
		glColor3f(1.0f,0.0f,0.0f);
	if(TGTflag==2)
		glColor3f(0.0f,0.0f,1.0f);
	if(TGTflag==3)
		glColor3f(1.0f,1.0f,0.0f);
	if(TGTflag==4)
	{
		glRotatef(-turn,0.0f,0.0f,1.0f);
		glColor3f(1.0f,1.0f,1.0f);
		glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR);
		glBindTexture(GL_TEXTURE_2D, PlayerSign);
		glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0.0f,0.0f);			// Texture Coord (Bottom Left)
				glVertex2i(-8,-8);						// Vertex Coord (Bottom Left)
				glTexCoord2f(1.0f,0.0f);	// Texture Coord (Bottom Right)
				glVertex2i(8,-8);						// Vertex Coord (Bottom Right)
				glTexCoord2f(1.0f,1.0f);			// Texture Coord (Top Right)
				glVertex2i(8,8);						// Vertex Coord (Top Right)
				glTexCoord2f(0.0f,1.0f);					// Texture Coord (Top Left)
				glVertex2i(-8,8);						// Vertex Coord (Top Left)
		glEnd();
	}
	else
	{

		glEnable(GL_POINT_SMOOTH);

		glDisable(GL_TEXTURE_2D);
		glPointSize(5.5);
		glBegin(GL_POINTS);
		glVertex2i(4,4);
		glEnd();

		glColor3f(1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_POINT_SMOOTH);
	}
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	
}