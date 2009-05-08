#include "Shell.h"

CShell::CShell(void)
: ShellNodeNumber(0)
{
	for(int i=0;i<MAXSHELLSLIST;i++)
		ShellList[ShellNodeNumber].life=0;
}

CShell::~CShell(void)
{
}

void CShell::AddNewShell(float posx, float posy, float posz, float movex, float movey, float movez, int TGT, int onwer, int type, int life)
{
	int tmp=0;
	ShellNodeNumber=ShellNodeNumber+1;
	if(ShellNodeNumber>=MAXSHELLSLIST)
		ShellNodeNumber=0;
	while(ShellList[ShellNodeNumber].life>0)
	{
		tmp=tmp+1;
		if(tmp>=MAXSHELLSLIST)
			return;
		ShellNodeNumber=ShellNodeNumber+1;
		if(ShellNodeNumber>=MAXSHELLSLIST)
			ShellNodeNumber=0;
	}
	ShellList[ShellNodeNumber].onwer=onwer;
	ShellList[ShellNodeNumber].life=life;
	ShellList[ShellNodeNumber].type=type;
	ShellList[ShellNodeNumber].TGTNum=TGT;
	ShellList[ShellNodeNumber].FrontPos[0]=posx+movex*1.5f;
	ShellList[ShellNodeNumber].FrontPos[1]=posy+movey*1.5f;
	ShellList[ShellNodeNumber].FrontPos[2]=posz+movez*1.5f;
	ShellList[ShellNodeNumber].BackPos[0]=posx;
	ShellList[ShellNodeNumber].BackPos[1]=posy;
	ShellList[ShellNodeNumber].BackPos[2]=posz;
	ShellList[ShellNodeNumber].posMove[0]=movex;
	ShellList[ShellNodeNumber].posMove[1]=movey;
	ShellList[ShellNodeNumber].posMove[2]=movez;
}

void CShell::DrawShell(const Vector3d& ViewPos,Transform& would,int winwidth,int winheight,float LookRenge)
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity();
	for(int i=0;i<MAXSHELLSLIST;i++)
	{
		if(ShellList[i].life>0)
		{

			
			tmpX=ShellList[i].FrontPos[0]-(float)ViewPos(0);
			tmpY=ShellList[i].FrontPos[1]-(float)ViewPos(1);
			tmpZ=ShellList[i].FrontPos[2]-(float)ViewPos(2);
			tmpL=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
			if(tmpL<LookRenge*LookRenge)
			{
				
				Pos3dFront=would.Matrix() * Vector3d(ShellList[i].FrontPos[0],ShellList[i].FrontPos[1],ShellList[i].FrontPos[2]) + would.RefPos();
				Pos3dBack=would.Matrix() * Vector3d(ShellList[i].BackPos[0],ShellList[i].BackPos[1],ShellList[i].BackPos[2]) + would.RefPos();
				glPushMatrix();
				glColor4f(1.0f,1.0f,0.9f,1.0f);
				glBegin(GL_TRIANGLE_STRIP);
				glVertex3f(float(Pos3dFront(0)+1.0f),float(Pos3dFront(1)-1.0f),float(Pos3dFront(2)));
				glVertex3f(float(Pos3dBack(0)+1.0f),float(Pos3dBack(1)-1.0f),float(Pos3dBack(2)));
				glVertex3f(float(Pos3dFront(0)+1.0f),float(Pos3dFront(1)+1.0f),float(Pos3dFront(2)));
				glVertex3f(float(Pos3dBack(0)+1.0f),float(Pos3dBack(1)+1.0f),float(Pos3dBack(2)));
				glVertex3f(float(Pos3dFront(0)-1.0f),float(Pos3dFront(1)+1.0f),float(Pos3dFront(2)));
				glVertex3f(float(Pos3dBack(0)-1.0f),float(Pos3dBack(1)+1.0f),float(Pos3dBack(2)));
				glVertex3f(float(Pos3dFront(0)-1.0f),float(Pos3dFront(1)-1.0f),float(Pos3dFront(2)));
				glVertex3f(float(Pos3dBack(0)-1.0f),float(Pos3dBack(1)-1.0f),float(Pos3dBack(2)));
				glEnd();
				glColor4f(1.0f,1.0f,1.0f,1.0f);
				glPopMatrix();	
			
			}
		
		}
	
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
