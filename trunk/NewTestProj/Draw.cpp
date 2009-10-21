#include"Draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
extern float turn1,turn2;
GLfloat Triangle[36];
GLfloat TriangleO[36] = { 0.0f, 1.0f, 0.0f,
						-1.0f,-1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f,
						 0.0f, 1.0f, 0.0f,
						 1.0f,-1.0f, 1.0f,
						 1.0f,-1.0f,-1.0f,
						 0.0f, 1.0f, 0.0f,
						 1.0f,-1.0f,-1.0f,
						-1.0f,-1.0f,-1.0f,
						 0.0f, 1.0f, 0.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f,-1.0f, 1.0f};
GLfloat TriColor[36];
GLfloat TriColorO[36] = {1.0f,0.0f,0.0f,
						0.0f,1.0f,0.0f,
						0.0f,0.0f,1.0f,
						1.0f,0.0f,0.0f,
						0.0f,0.0f,1.0f,
						0.0f,1.0f,0.0f,
						1.0f,0.0f,0.0f,
						0.0f,1.0f,0.0f,
						0.0f,0.0f,1.0f,
						1.0f,0.0f,0.0f,
						0.0f,0.0f,1.0f,
						0.0f,1.0f,0.0f};
GLfloat TriTexCoord[24] = {
	0.5f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f,
	0.5f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f,
	0.5f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f,
	0.5f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f};
void Draw()
{
 
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glPushMatrix();
		glTranslatef(-1.5f,0.0f,-12.0f);						// Move Left 1.5 Units And Into The Screen 6.0
		glRotatef(turn1,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis

		for(int i=0;i<36;i++)
			Triangle[i]=TriangleO[i]+turn2/360.0f;
		for(int i=0;i<36;i++)
			TriColor[i]=TriColorO[i]+turn2/360.0f;

		glEnable(GL_MULTISAMPLE_ARB);

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glColor3f(1.0f,1.0f,1.0f);	
		glEnableClientState( GL_COLOR_ARRAY );
   		glEnableClientState( GL_VERTEX_ARRAY );	
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glColorPointer( 3, GL_FLOAT, 0, TriColor );
		glTexCoordPointer( 2, GL_FLOAT, 0, TriTexCoord );
		glVertexPointer( 3, GL_FLOAT, 0, Triangle ); 
		glDrawArrays( GL_TRIANGLES, 0, 12 );	
		glDisableClientState( GL_COLOR_ARRAY );	
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	   /*
		glBegin(GL_TRIANGLES);								// Drawing Using Triangles
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f( 1.0f,-1.0f,-1.0f);			// Right Of Triangle (Right)

			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
		glEnd();											// Finished Drawing The Triangle
		*/
		glDisable(GL_MULTISAMPLE_ARB);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, 1);	
		//glDisable( GL_TEXTURE_2D );
		glLoadIdentity();					// Reset The Current Modelview Matrix
		glTranslatef(1.5f,0.0f,-12.0f);				// Move Right 1.5 Units And Into The Screen 6.0
		glRotatef(turn2,1.0f,0.0f,0.0f);			// Rotate The Quad On The X axis
		glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
		glTexCoord2f(1.0f,1.0f);
		glBegin(GL_QUADS);									// Draw A Quad
			glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
			glTexCoord2f(0.0f,0.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 	    	// Top Right Of The Quad (Top)
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 		    // Top Left Of The Quad (Top)
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 				// Bottom Left Of The Quad (Top)
			glTexCoord2f(0.0f,1.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 				// Bottom Right Of The Quad (Top)
			glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
			glVertex3f( 1.0f,-1.0f, 1.0f); glTexCoord2f(0.0f,0.0f);				// Top Right Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f, 1.0f); glTexCoord2f(1.0f,0.0f);				// Top Left Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f,-1.0f); glTexCoord2f(1.0f,1.0f);				// Bottom Left Of The Quad (Bottom)
			glVertex3f( 1.0f,-1.0f,-1.0f); glTexCoord2f(0.0f,1.0f);				// Bottom Right Of The Quad (Bottom)
			glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
			glVertex3f( 1.0f, 1.0f, 1.0f); glTexCoord2f(0.0f,0.0f);				// Top Right Of The Quad (Front)
			glVertex3f(-1.0f, 1.0f, 1.0f); glTexCoord2f(1.0f,0.0f);				// Top Left Of The Quad (Front)
			glVertex3f(-1.0f,-1.0f, 1.0f); glTexCoord2f(1.0f,1.0f);				// Bottom Left Of The Quad (Front)
			glVertex3f( 1.0f,-1.0f, 1.0f); glTexCoord2f(0.0f,1.0f);				// Bottom Right Of The Quad (Front)
			glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
			glVertex3f( 1.0f,-1.0f,-1.0f); glTexCoord2f(0.0f,0.0f);				// Bottom Left Of The Quad (Back)
			glVertex3f(-1.0f,-1.0f,-1.0f); glTexCoord2f(1.0f,0.0f);				// Bottom Right Of The Quad (Back)
			glVertex3f(-1.0f, 1.0f,-1.0f); glTexCoord2f(1.0f,1.0f);				// Top Right Of The Quad (Back)
			glVertex3f( 1.0f, 1.0f,-1.0f); glTexCoord2f(0.0f,1.0f);				// Top Left Of The Quad (Back)
			glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
			glVertex3f(-1.0f, 1.0f, 1.0f); glTexCoord2f(0.0f,0.0f);				// Top Right Of The Quad (Left)
			glVertex3f(-1.0f, 1.0f,-1.0f); glTexCoord2f(1.0f,0.0f);				// Top Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f,-1.0f); glTexCoord2f(1.0f,1.0f);				// Bottom Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f, 1.0f); glTexCoord2f(0.0f,1.0f);				// Bottom Right Of The Quad (Left)
			glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
			glVertex3f( 1.0f, 1.0f,-1.0f); glTexCoord2f(0.0f,0.0f);				// Top Right Of The Quad (Right)
			glVertex3f( 1.0f, 1.0f, 1.0f); glTexCoord2f(1.0f,0.0f);				// Top Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f, 1.0f); glTexCoord2f(1.0f,1.0f);				// Bottom Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f,-1.0f); glTexCoord2f(0.0f,1.0f);				// Bottom Right Of The Quad (Right)
		glEnd();						// Done Drawing The Quad
	glPopMatrix();
}