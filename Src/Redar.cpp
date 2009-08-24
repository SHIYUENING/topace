#include "Unitdata.h"
#include "HUDUI.h"
#include "DDS.h"
#include "DefinesFile.h"
extern GLuint RedarTexture;
extern GLuint Maptexture;
extern GLuint textureRedar;
extern GLuint CompassTexID;
extern int winwidth,winheight;
extern float tmpredarRenge;
extern int lockflash;
extern Unitdata UDfighers[maxUnits];
extern float tmpAREAredarRenge;
extern bool PlayerLocked;
extern int hited;
extern int ModelID_redarUI;
//extern GLuint img;
//extern GLuint bloomTexId1,bloomTexId2;
void DrawBlackBack(int Size)
{
	

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix


	glPushMatrix();	
		glDisable(GL_TEXTURE_2D);	

				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glColor4f(0.0f,0.0f,0.0f,1.0f);glVertex2i(0,0);						// Vertex Coord (Bottom Left)
					glColor4f(0.0f,0.0f,0.0f,1.0f);glVertex2i(Size,0);						// Vertex Coord (Bottom Right)
					glColor4f(0.0f,0.0f,0.0f,1.0f);glVertex2i(Size,Size);						// Vertex Coord (Top Right)
					glColor4f(0.0f,0.0f,0.0f,1.0f);glVertex2i(0,Size);						// Vertex Coord (Top Left)
				glEnd();
		glEnable(GL_TEXTURE_2D);
	glPopMatrix();



	

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	glEnable(GL_BLEND);
}
void DrawRedarToTexture()
{
	DrawBlackBack(256);


	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	glEnable(GL_BLEND);
	//glPrintRedar(0,0,-1,tmpredarRenge);
	for(int i=1;i<maxUnits;i++)
	{
		if(UDfighers[i].UDlife>0)
		if(UDfighers[i].UDwinl<(tmpredarRenge*tmpredarRenge))
		{
			float vx,vy,vz;
			//Vredar=MView.Matrix() * UDfighers[i].UDMplane.RefPos() + MView.RefPos();
			//Vredar=UDfighers[i].UDMplane.RefPos()-MFighter.RefPos();
			vx=(float)(UDfighers[i].UDMplane.RefPos()(0)-UDfighers[0].UDMplane.RefPos()(0));
			vy=(float)(UDfighers[i].UDMplane.RefPos()(1)-UDfighers[0].UDMplane.RefPos()(1));
			vz=(float)(UDfighers[i].UDMplane.RefPos()(2)-UDfighers[0].UDMplane.RefPos()(2));

			if(UDfighers[i].UDlockselect)
				{
					if(lockflash>15)
						glPrintRedar(vx,vz,UDfighers[i].UDflag,tmpredarRenge);
				}
				else
					glPrintRedar(vx,vz,UDfighers[i].UDflag,tmpredarRenge);
		}
	
	}
	glBindTexture(GL_TEXTURE_2D,RedarTexture);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 256, 256, 0);
}

void DrawMAP()
{
	glEnable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,0.5f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-winwidth/2,winwidth/2,-winheight/2,winheight/2,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glPushMatrix();	
		//glBindTexture(GL_TEXTURE_2D, bloomTexId1);	
	glBindTexture(GL_TEXTURE_2D, Maptexture);	
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(0.0f,0.0f);glVertex2i(-winheight/2,-winheight/2);						// Vertex Coord (Bottom Left)
					glTexCoord2f(1.0f,0.0f);glVertex2i( winheight/2,-winheight/2);						// Vertex Coord (Bottom Right)
					glTexCoord2f(1.0f,1.0f);glVertex2i( winheight/2, winheight/2);						// Vertex Coord (Top Right)
					glTexCoord2f(0.0f,1.0f);glVertex2i(-winheight/2, winheight/2);						// Vertex Coord (Top Left)
				glEnd();
	glPopMatrix();	

	



	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

void DrawAREARedarToTexture(float turn)
{

	DrawMAP();
	
	for(int i=1;i<maxUnits;i++)
	{
		if(UDfighers[i].UDlife>0)
		//if(UDfighers[i].UDwinl<(tmpredarRenge*tmpredarRenge))
		{
			float vx,vy,vz;
			vx=(float)(UDfighers[i].UDMplane.RefPos()(0));
			vy=(float)(UDfighers[i].UDMplane.RefPos()(1));
			vz=(float)(UDfighers[i].UDMplane.RefPos()(2));
			glPrintAREARedar(vx,-vz,UDfighers[i].UDflag,tmpAREAredarRenge);
		}
	
	}
	glPrintAREARedar((float)UDfighers[0].UDMplane.RefPos()(0),-(float)UDfighers[0].UDMplane.RefPos()(2),4,tmpAREAredarRenge,180.0f-turn);

}

void DrawRedar(float ne)
{
	glEnable(GL_BLEND);
	GLint DRX=(GLint)(winwidth/5.0f);
	GLint DRY=(GLint)(winheight/5.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA   );
	
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-DRY,winwidth+(DRX-DRY),-DRY,winheight,-1,100);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix


	glColor4f(0.5f,1.0f,0.5f,1.0f);
	if(PlayerLocked)
		glColor4f(1.0f,0.5f,0.5f,1.0f);
	glPushMatrix();	
		glBindTexture(GL_TEXTURE_2D, textureRedar);	
		//glTranslated(-DRY,DRY,0);
		
		if(hited>0)
		glTranslated(float(rand()%10-5),float(rand()%10-5),0);
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(0.0f,0.0f);glVertex2f(-DRY*0.9f, DRY*0.9f);						// Vertex Coord (Bottom Left)
					glTexCoord2f(1.0f,0.0f);glVertex2f( DRY*0.9f, DRY*0.9f);						// Vertex Coord (Bottom Right)
					glTexCoord2f(1.0f,1.0f);glVertex2f( DRY*0.9f,-DRY*0.9f);						// Vertex Coord (Top Right)
					glTexCoord2f(0.0f,1.0f);glVertex2f(-DRY*0.9f,-DRY*0.9f);						// Vertex Coord (Top Left)
				glEnd();

				glBindTexture(GL_TEXTURE_2D, CompassTexID);	
				glRotatef(180.0f-ne,0.0f,0.0f,1.0f);
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(0.0f,0.0f);glVertex2f(-DRY*1.1f, DRY*1.1f);						// Vertex Coord (Bottom Left)
					glTexCoord2f(1.0f,0.0f);glVertex2f( DRY*1.1f, DRY*1.1f);						// Vertex Coord (Bottom Right)
					glTexCoord2f(1.0f,1.0f);glVertex2f( DRY*1.1f,-DRY*1.1f);						// Vertex Coord (Top Right)
					glTexCoord2f(0.0f,1.0f);glVertex2f(-DRY*1.1f,-DRY*1.1f);						// Vertex Coord (Top Left)
				glEnd();
	glPopMatrix();	
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBlendFunc(GL_SRC_COLOR,GL_ONE_MINUS_SRC_COLOR   );
	glPushMatrix();
			glRotatef(180.0f-ne+25.0f,0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D, RedarTexture);	
			glScaled(-0.0199*DRY*0.9, 0.0199*DRY*0.9, 0.0199*DRY*0.9);
			m_VBMD->ShowVBMD(ModelID_redarUI,false);
			glColor4f(1.0f,1.0f,1.0f,1.0f);
	glPopMatrix();



	

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

