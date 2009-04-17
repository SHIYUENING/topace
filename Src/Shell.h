#ifndef _SHELL_H
#define _SHELL_H
#include "Mathematics.h"
#include <gl\glew.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#define MAXSHELLSLIST 10000
struct ShellListNode
{

	float FrontPos[3];
	float BackPos[3];
	float posMove[3];
	int TGTNum;
	int onwer;
	int type;
	int life;
};
class CShell
{
public:
	ShellListNode ShellList[MAXSHELLSLIST];
	float tmpL;
	float tmpX;
	float tmpY;
	float tmpZ;
	Vector3d Pos3dFront;
	Vector3d Pos3dBack;


	CShell(void);
	~CShell(void);
	void AddNewShell(float posx, float posy, float posz, float movex, float movey, float movez, int TGT, int onwer, int type=0,int life=100);
	int ShellNodeNumber;
	void DrawShell(const Vector3d& ViewPos,Transform& would,int winwidth,int winheight,float LookRenge);
};
#endif