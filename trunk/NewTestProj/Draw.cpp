#include"Draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include "Glsl.h"
#include <lib3ds.h>
#include <string.h>	
#include "Load3DS.h"
extern float turn1,turn2,frametest;
extern GLuint Test3DsTexID;
extern float TestPos[3];
extern float TestRot[3];
GLfloat Triangle[36];
GLfloat TriangleO[36] = {000.0f, 100.0f, 000.0f,
						-100.0f,-100.0f, 100.0f,
						 100.0f,-100.0f, 100.0f,
						 000.0f, 100.0f, 000.0f,
						 100.0f,-100.0f, 100.0f,
						 100.0f,-100.0f,-100.0f,
						 000.0f, 100.0f, 000.0f,
						 100.0f,-100.0f,-100.0f,
						-100.0f,-100.0f,-100.0f,
						 000.0f, 100.0f, 000.0f,
						-100.0f,-100.0f,-100.0f,
						-100.0f,-100.0f, 100.0f};
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
GLubyte Tex3DData[32][32][4][4];
GLuint Tex3DID=0;
Lib3dsFile *Model3ds=0;
Lib3dsNode *Node=0;
Lib3dsMesh *Mesh=0;
Lib3dsFace *Face=0;
CLoad3DS Model3DsTest1;
float TestRotSNYC=0.0f;
/*
void Test3DS()
{
	Model3ds=lib3ds_file_open("Data/Model/3ds.3DS");

	Lib3dsMeshInstanceNode *MeshData=0;
	
	Node=Model3ds->nodes;

	while((Node->type!=LIB3DS_NODE_MESH_INSTANCE)||(strcmp(Node->name,"$$$DUMMY")==0))
	{
		Node=Node->next;
		if(!Node)
			return;
	}
	Node=Node->next;
	Node=Node->next;
	Mesh=lib3ds_file_mesh_for_node(Model3ds,Node);
	if(!Mesh)
		return;
		
	//for(Mesh=Model3ds->meshes;Mesh!=NULL;Mesh=Model3ds->)
}*/
void DrawTest3DS()
{

	GLfloat LightPos[]={10000.0f,0.0f,0.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//float tmpxxx=0.0f;
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, Test3DsTexID);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(TestPos[0],TestPos[1],-150.0f+TestPos[2]);				// Move Right 1.5 Units And Into The Screen 6.0
	glRotatef(-turn2*2,0.0f,1.0f,0.0f);			// Rotate The Quad On The X axis
	glRotatef(TestRot[0],1.0f,0.0f,0.0f);
	glRotatef(TestRot[1],0.0f,1.0f,0.0f);
	TestRotSNYC=TestRotSNYC+1;
	if(TestRotSNYC>=100.0f)
		TestRotSNYC=0.0f;
	//frametest=TestRotSNYC;
	Model3DsTest1.Render(frametest);
	//float * pvertices = new float[Mesh->nvertices*3*3*4];
	/*glBegin(GL_TRIANGLES);
	for(int i=0;i<Mesh->nfaces;i++)
	{
		
		Face=&(Mesh->faces[i]);


		//glVertex3fv(Mesh->vertices[Face->index[j]]);
		glTexCoord2f(Mesh->texcos[Face->index[0]][0],Mesh->texcos[Face->index[0]][1]);glVertex3f(Mesh->vertices[Face->index[0]][0],Mesh->vertices[Face->index[0]][2],Mesh->vertices[Face->index[0]][1]);
		glTexCoord2f(Mesh->texcos[Face->index[1]][0],Mesh->texcos[Face->index[1]][1]);glVertex3f(Mesh->vertices[Face->index[1]][0],Mesh->vertices[Face->index[1]][2],Mesh->vertices[Face->index[1]][1]);
		glTexCoord2f(Mesh->texcos[Face->index[2]][0],Mesh->texcos[Face->index[2]][1]);glVertex3f(Mesh->vertices[Face->index[2]][0],Mesh->vertices[Face->index[2]][2],Mesh->vertices[Face->index[2]][1]);
		//tmpxxx=pvertices[(i*3+j)*3+0]=Mesh->vertices[Face->index[j]][0]*0.01f;
		//tmpxxx=pvertices[(i*3+j)*3+1]=Mesh->vertices[Face->index[j]][1]*0.01f;
		//tmpxxx=pvertices[(i*3+j)*3+2]=Mesh->vertices[Face->index[j]][2]*0.01f;
		
		
	}
	glEnd();*/
	glPopMatrix();
	glDisable(GL_LIGHTING);
}
void init3DTexTest()
{
//	Test3DS();
	Model3DsTest1.Loadfile("Data/Model/Test3dsModel.3DS");
	Model3DsTest1.LoadToVRAM();
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			for(int k=0;k<4;k++)
			{
				Tex3DData[i][j][k][0]=rand()%256;
				Tex3DData[i][j][k][1]=rand()%256;
				Tex3DData[i][j][k][2]=rand()%256;
				Tex3DData[i][j][k][3]=rand()%256;
			}
		}
	}
    glGenTextures( 1, &Tex3DID );
	glBindTexture( GL_TEXTURE_3D, Tex3DID ); 
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA,32,32,4,0,GL_RGBA,GL_UNSIGNED_BYTE,Tex3DData);
}
void Draw()
{
 
	glLoadIdentity();									// Reset The Current Modelview Matrix
	DrawTest3DS();
	glPushMatrix();
		glTranslatef(-1.5f,0.0f,-1500.0f);						// Move Left 1.5 Units And Into The Screen 6.0
		glRotatef(turn1,0.0f,1.0f,0.0f);				// Rotate The Triangle On The Y axis

		for(int i=0;i<36;i++)
			Triangle[i]=TriangleO[i]+turn2/3.60f;
		for(int i=0;i<36;i++)
			TriColor[i]=TriColorO[i]+turn2/360.0f;

		glEnable(GL_MULTISAMPLE_ARB);
		glEnable(GL_BLEND);
		glEnable( GL_TEXTURE_2D );
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		//GLSL_Enable_ATC();
		glColor3f(1.0f,1.0f,1.0f);	
		glEnableClientState( GL_COLOR_ARRAY );
   		glEnableClientState( GL_VERTEX_ARRAY );	
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glColorPointer( 3, GL_FLOAT, 0, TriColor );
		glTexCoordPointer( 2, GL_FLOAT, 0, TriTexCoord );
		glVertexPointer( 3, GL_FLOAT, 0, Triangle ); 
		//glDrawArrays( GL_TRIANGLES, 0, 12 );	
		glDisableClientState( GL_COLOR_ARRAY );	
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		//GLSL_Disable_ATC();
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

		/*
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, Test3DsTexID);	
		//glDisable( GL_TEXTURE_2D );
		glLoadIdentity();					// Reset The Current Modelview Matrix
		glTranslatef(1.5f,0.0f,-40.0f);				// Move Right 1.5 Units And Into The Screen 6.0
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
			glTexCoord2f(0.0f,0.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Top Right Of The Quad (Bottom)
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Top Left Of The Quad (Bottom)
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Bottom)
			glTexCoord2f(0.0f,1.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Bottom)
			glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
			glTexCoord2f(0.0f,0.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 			// Top Right Of The Quad (Front)
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 			// Top Left Of The Quad (Front)
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Bottom Left Of The Quad (Front)
			glTexCoord2f(0.0f,1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Bottom Right Of The Quad (Front)
			glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
			glTexCoord2f(0.0f,0.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Back)
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Back)
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 			// Top Right Of The Quad (Back)
			glTexCoord2f(0.0f,1.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 			// Top Left Of The Quad (Back)
			glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
			glTexCoord2f(0.0f,0.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 			// Top Right Of The Quad (Left)
			glTexCoord2f(1.0f,0.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 			// Top Left Of The Quad (Left)
			glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Left)
			glTexCoord2f(0.0f,1.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Bottom Right Of The Quad (Left)
			glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
			glTexCoord2f(0.0f,0.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 			// Top Right Of The Quad (Right)
			glTexCoord2f(1.0f,0.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 			// Top Left Of The Quad (Right)
			glTexCoord2f(1.0f,1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Bottom Left Of The Quad (Right)
			glTexCoord2f(0.0f,1.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Right)
		glEnd();						// Done Drawing The Quad
		*/
	glPopMatrix();
	
	
	glDisable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glEnable( GL_TEXTURE_3D );
	glBindTexture(GL_TEXTURE_3D, Tex3DID);
	
	glPushMatrix();
	glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		glRotatef(turn2,1.0f,1.0f,1.0f);
/*		glBegin(GL_QUADS);
			glColor4f(1.0f,1.0f,1.0f,1.0f);		
			glTexCoord3f(1.0f,1.0f,0.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 	    	// Top Right Of The Quad (Top)
			glTexCoord3f(0.0f,1.0f,0.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 		    // Top Left Of The Quad (Top)
			glTexCoord3f(0.0f,1.0f,1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 				// Bottom Left Of The Quad (Top)
			glTexCoord3f(1.0f,1.0f,1.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 				// Bottom Right Of The Quad (Top)
			
			glTexCoord3f(1.0f,0.0f,1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Top Right Of The Quad (Bottom)
			glTexCoord3f(0.0f,0.0f,1.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Top Left Of The Quad (Bottom)
			glTexCoord3f(0.0f,0.0f,0.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Bottom)
			glTexCoord3f(1.0f,0.0f,0.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Bottom)
			
			glTexCoord3f(1.0f,1.0f,1.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 			// Top Right Of The Quad (Front)
			glTexCoord3f(0.0f,1.0f,1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 			// Top Left Of The Quad (Front)
			glTexCoord3f(0.0f,0.0f,1.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Bottom Left Of The Quad (Front)
			glTexCoord3f(1.0f,0.0f,1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Bottom Right Of The Quad (Front)
			
			glTexCoord3f(1.0f,0.0f,0.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Back)
			glTexCoord3f(0.0f,0.0f,0.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Back)
			glTexCoord3f(0.0f,1.0f,0.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 			// Top Right Of The Quad (Back)
			glTexCoord3f(1.0f,1.0f,0.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 			// Top Left Of The Quad (Back)
			
			glTexCoord3f(0.0f,1.0f,1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f); 			// Top Right Of The Quad (Left)
			glTexCoord3f(0.0f,1.0f,0.0f);	glVertex3f(-1.0f, 1.0f,-1.0f); 			// Top Left Of The Quad (Left)
			glTexCoord3f(0.0f,0.0f,0.0f);	glVertex3f(-1.0f,-1.0f,-1.0f); 			// Bottom Left Of The Quad (Left)
			glTexCoord3f(0.0f,0.0f,1.0f);	glVertex3f(-1.0f,-1.0f, 1.0f); 			// Bottom Right Of The Quad (Left)
			
			glTexCoord3f(1.0f,1.0f,0.0f);	glVertex3f( 1.0f, 1.0f,-1.0f); 			// Top Right Of The Quad (Right)
			glTexCoord3f(1.0f,1.0f,1.0f);	glVertex3f( 1.0f, 1.0f, 1.0f); 			// Top Left Of The Quad (Right)
			glTexCoord3f(1.0f,0.0f,1.0f);	glVertex3f( 1.0f,-1.0f, 1.0f); 			// Bottom Left Of The Quad (Right)
			glTexCoord3f(1.0f,0.0f,0.0f);	glVertex3f( 1.0f,-1.0f,-1.0f); 			// Bottom Right Of The Quad (Right)

		glEnd();
*/
	glPopMatrix();
	glDisable( GL_TEXTURE_3D );
}