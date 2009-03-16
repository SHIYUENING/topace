//redar.h
#pragma once
#include "Prints.h"
#include "structs.h"
#include "UI.h"
#include "testNum.h"

GLuint		RedarTexture;

void DrawRedarToTexture()
{

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
			vx=(float)(UDfighers[i].UDMplane.RefPos()(0)-MFighter.RefPos()(0));
			vy=(float)(UDfighers[i].UDMplane.RefPos()(1)-MFighter.RefPos()(1));
			vz=(float)(UDfighers[i].UDMplane.RefPos()(2)-MFighter.RefPos()(2));

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
		glBindTexture(GL_TEXTURE_2D, Maptexture);	
	//glBindTexture(GL_TEXTURE_2D, img);	
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

void DrawAREARedarToTexture(float turn=0.0f)
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
	glPrintAREARedar((float)MFighter.RefPos()(0),-(float)MFighter.RefPos()(2),4,tmpAREAredarRenge,180.0f-turn);

}

void DrawRedar(float ne=0.0)
{
	glEnable(GL_BLEND);
	GLint DRX=(GLint)(winwidth/5.0f);
	GLint DRY=(GLint)(winheight/5.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_COLOR   );
	
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-DRX,winwidth,-DRY,winheight,-1,100);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	glPushMatrix();
		glDisable(GL_BLEND);
			glRotatef(180.0f-ne+25.0f,0.0f,0.0f,1.0f);
			glBindTexture(GL_TEXTURE_2D, RedarTexture);	
			glScaled(-0.0199*DRY, 0.0199*DRY, 0.0199*DRY);
			m_VBMD->ShowVBMD(6,false);
		glEnable(GL_BLEND);
	glPopMatrix();
	//glDisable(GL_BLEND);
	glPushMatrix();	
		glBindTexture(GL_TEXTURE_2D, textureRedar);	
		glTranslated(-DRY,DRY,0);
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(0.0f,0.0f);			// Texture Coord (Bottom Left)
					glVertex2i(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(1.0,0.0f);	// Texture Coord (Bottom Right)
					glVertex2i(DRY*2,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(1.0f,1.0f);			// Texture Coord (Top Right)
					glVertex2i(DRY*2,-DRY*2);						// Vertex Coord (Top Right)
					glTexCoord2f(0.0f,1.0f);					// Texture Coord (Top Left)
					glVertex2i(0,-DRY*2);						// Vertex Coord (Top Left)
				glEnd();
	glPopMatrix();	

	



	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}

