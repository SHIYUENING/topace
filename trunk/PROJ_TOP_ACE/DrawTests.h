#ifndef _DRAWTESTS_H
#define _DRAWTESTS_H
#include <GL/glew.h>
#include "Common.h"
struct _TestMeshVBOID
{
	unsigned int VerticeID;
	unsigned int NormalID;
	unsigned int TexCoordID;
	unsigned int ColorID;
	unsigned int FaceID;
};
void InitTestModel();
void DrawTestModel(unsigned int TestModelDrawMode);
void DeinitTestModel();
void DrawTestLines();
#endif