#include "DrawTests.h"
#include "Glsl.h"

_TestMeshVBOID TestMeshVBOID;
GLuint TestModelVAO=0;

void InitTestModel()
{
	int TestModelFaces[]={
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
	};
	float TestModelPos[]={
			0.0f,   0.0f,-050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			-050.0f,   0.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,

			0.0f,   0.0f,-050.0f,
			-050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,

			-050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f,
			0.0f, 050.0f, 050.0f,

			0.0f, 050.0f, 050.0f,
			050.0f,   0.0f, 050.0f,
			0.0f,-050.0f, 050.0f
	};
	float TestModelNormal[]={
			0.0f, 0.0f,-1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			-1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,

			0.0f, 0.0f,-1.0f,
			-1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,
	
			-1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f,-1.0f, 0.0f
	};
	float TestModelColor[]={
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,

			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			0.0f,1.0f,0.0f,1.0f,

			0.0f,1.0f,0.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,1.0f
	};

	float TestModelTexCoord[]={
		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f,

		0.0f,   0.0f,
		1.0f,   0.0f,
		0.0f,   1.0f
	};
	
	glGenBuffersARB( 1,&TestMeshVBOID.VerticeID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.VerticeID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelPos), TestModelPos, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.NormalID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.NormalID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelNormal), TestModelNormal, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.ColorID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.ColorID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelColor), TestModelColor, GL_STATIC_DRAW_ARB );
	glGenBuffersARB( 1,&TestMeshVBOID.TexCoordID);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.TexCoordID );
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(TestModelTexCoord), TestModelTexCoord, GL_STATIC_DRAW_ARB );
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glGenBuffersARB( 1,&TestMeshVBOID.FaceID);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, TestMeshVBOID.FaceID );
	glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(TestModelFaces), TestModelFaces, GL_STATIC_DRAW_ARB );
	
	glGenVertexArrays(1,&TestModelVAO);
	glBindVertexArray(TestModelVAO);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.VerticeID );
	glVertexAttribPointer(AbLoc_Pos,3,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Pos);
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.NormalID );
	glVertexAttribPointer(AbLoc_Normal,3,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Normal);
	
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.ColorID );
	glVertexAttribPointer(AbLoc_Color,4,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Color);

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, TestMeshVBOID.TexCoordID );
	glVertexAttribPointer(AbLoc_Tex0,2,GL_FLOAT,0,0,0);
	glEnableVertexAttribArray(AbLoc_Tex0);
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, TestMeshVBOID.FaceID );
	glBindVertexArray(0);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0);

}
void DrawTestModel(unsigned int TestModelDrawMode)
{
	glDisable( GL_TEXTURE_2D );
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBindVertexArray(TestModelVAO);
    glDrawElements(TestModelDrawMode, 18, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(AbLoc_Color);
	glDisableVertexAttribArray(AbLoc_Normal);
	glDisableVertexAttribArray(AbLoc_Pos);
	glDisableVertexAttribArray(AbLoc_Tex0);
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
}
void DeinitTestModel()
{
	glDeleteBuffersARB(1,&TestMeshVBOID.VerticeID);
	glDeleteBuffersARB(1,&TestMeshVBOID.NormalID);
	glDeleteBuffersARB(1,&TestMeshVBOID.ColorID);
	glDeleteBuffersARB(1,&TestMeshVBOID.TexCoordID);
}
void DrawTestLines()
{
	glDisable( GL_TEXTURE_2D );
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 0.0f, 0.0f, 100000.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);

		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 0.0f, 0.0f,      0.0f);
		glVertex3f( 0.0f, 0.0f,-100000.0f);

		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( 0.0f, 100000.0f, 0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);

		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f( 0.0f,      0.0f, 0.0f);
		glVertex3f( 0.0f,-100000.0f, 0.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 100000.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-100000.0f, 0.0f, 0.0f);
		glVertex3f(      0.0f, 0.0f, 0.0f);


		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f( 100.0f, 100.0f, 100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f( 100.0f, 100.0f, 100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f, 100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f, 100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);


		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f,-100.0f);

		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f,-100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f,-100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f,-100.0f);



		glVertex3f( 100.0f, 100.0f,-100.0f);
		glVertex3f( 100.0f, 100.0f, 100.0f);

		glVertex3f(-100.0f, 100.0f,-100.0f);
		glVertex3f(-100.0f, 100.0f, 100.0f);

		glVertex3f( 100.0f,-100.0f,-100.0f);
		glVertex3f( 100.0f,-100.0f, 100.0f);

		glVertex3f(-100.0f,-100.0f,-100.0f);
		glVertex3f(-100.0f,-100.0f, 100.0f);

	glEnd();

	glEnable( GL_TEXTURE_2D );
}