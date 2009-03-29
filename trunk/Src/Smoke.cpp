#include "Smoke.h"
#include <stdio.h>
CSmoke::CSmoke(void)
: SmokeNodeNumber(0)
, SmokeGLlist(0)
, GraphicLevel(1)
, SmokeTexsNum(0)
{
}

CSmoke::~CSmoke(void)
{
	for(int i=0;i<SmokeTexsNum;i++)
		glDeleteTextures(1,&textureSmoke[i].texID);
}

void CSmoke::AddSmoke(float pos[3], float size, float sizeMove, float life ,int type)
{
	SmokeNodeNumber=SmokeNodeNumber+1;
	if(SmokeNodeNumber==MAXSMOKESLIST)
	{
		SmokeNodeNumber=0;
	
	}
		
	SmokesList[SmokeNodeNumber].TexId=textureSmoke[rand()%SmokeTexsNum].texID;
	SmokesList[SmokeNodeNumber].pos[0]=pos[0];
	SmokesList[SmokeNodeNumber].pos[1]=pos[1];
	SmokesList[SmokeNodeNumber].pos[2]=pos[2];
	SmokesList[SmokeNodeNumber].posMove[0]=(float)(rand()%100-50)/300.0f;
	SmokesList[SmokeNodeNumber].posMove[1]=(float)(rand()%100-50)/300.0f;
	SmokesList[SmokeNodeNumber].posMove[2]=(float)(rand()%100-50)/300.0f;
	SmokesList[SmokeNodeNumber].size=size;
	SmokesList[SmokeNodeNumber].sizeMove=sizeMove;
	SmokesList[SmokeNodeNumber].life=life;
	SmokesList[SmokeNodeNumber].lifeMAX=life;
	SmokesList[SmokeNodeNumber].type=type;
	
	/*
	SmokeListNode * NewNode;
	NewNode=(SmokeListNode*)new(SmokeListNode);//给新节点分配内存
	NewNode->TexId=TexId;
	NewNode->pos[0]=pos[0];
	NewNode->pos[1]=pos[1];
	NewNode->pos[2]=pos[2];
	NewNode->posMove[0]=posMove[0];
	NewNode->posMove[1]=posMove[1];
	NewNode->posMove[2]=posMove[2];
	NewNode->size=size;
	NewNode->next=NULL;
	if(SmokeNode==NULL)//如果是第一个节点
	{
		NewNode->prev=NULL;//第一个节点不存在前一个节点
		SmokeNode=NewNode;//新节点作为当前节点
		SmokeFirstNode=SmokeNode;//当前节点作为第一个节点
		SmokeNodeNumber=1;//总节点数为1
	}
	else
	{
		NewNode->prev=SmokeNode;//新节点的前一个节点为当前节点
		SmokeNode->next=NewNode;//当前节点的下一个节点为新节点
		SmokeNode=NewNode;//新节点作为当前节点
		SmokeNodeNumber=SmokeNodeNumber+1;//总节点数增加1
	}*/
}
/*
void CSmoke::DelSmoke(SmokeListNode * DelNode)
{
	
	SmokeListNode * DelNodePrev;
	DelNodePrev=DelNode->prev;//获取删除节点的前一个节点
	DelNodePrev->next=DelNode->next;//删除节点的下一个节点作为前一个节点的下一个节点
	delete DelNode;
	
}
*/
void CSmoke::BuildSmoke(unsigned int settexID)
{
	SmokeGLlist=glGenLists(1);
	glBindTexture(GL_TEXTURE_2D, settexID);
	glNewList(SmokeGLlist,GL_COMPILE);
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0.0f,0.0f);			// Texture Coord (Bottom Left)
				glVertex2i(-50,-50);						// Vertex Coord (Bottom Left)
				glTexCoord2f(1.0f,0.0f);	// Texture Coord (Bottom Right)
				glVertex2i(50,-50);						// Vertex Coord (Bottom Right)
				glTexCoord2f(1.0f,1.0f);			// Texture Coord (Top Right)
				glVertex2i(50,50);						// Vertex Coord (Top Right)
				glTexCoord2f(0.0f,1.0f);					// Texture Coord (Top Left)
				glVertex2i(-50,50);						// Vertex Coord (Top Left)
			glEnd();

	glEndList();

}
void CSmoke::DrawSmoke(const Vector3d& ViewPos,Transform& would,int winwidth,int winheight,float LookRenge)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glPushMatrix();	
	//glLoadIdentity();
	//glMultMatrixd(ViewPos.Matrix4());
	
		for(int i=0;i<MAXSMOKESLIST;i++)
		{
			//if(SmokesList[i].life>0.0f&&(((SmokesList[i].pos[0]-ViewPos[0])*(SmokesList[i].pos[0]-ViewPos[0])+(SmokesList[i].pos[1]-ViewPos[1])*(SmokesList[i].pos[1]-ViewPos[1])+(SmokesList[i].pos[2]-ViewPos[2])*(SmokesList[i].pos[2]-ViewPos[2]))<LookRenge*LookRenge))
			
			if(SmokesList[i].life>0.0f)//存在
			{
					SmokesList[i].pos[0]=SmokesList[i].pos[0]+SmokesList[i].posMove[0];
					SmokesList[i].pos[1]=SmokesList[i].pos[1]+SmokesList[i].posMove[1];
					SmokesList[i].pos[2]=SmokesList[i].pos[2]+SmokesList[i].posMove[2];
					SmokesList[i].size=SmokesList[i].size+SmokesList[i].sizeMove;
					SmokesList[i].life=SmokesList[i].life-1.0f;

				
				tmpX=SmokesList[i].pos[0]-(float)ViewPos(0);
				tmpY=SmokesList[i].pos[1]-(float)ViewPos(1);
				tmpZ=SmokesList[i].pos[2]-(float)ViewPos(2);
				SmoleL=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
				//SmoleL=LookRenge*LookRenge-(SmokesList[i].pos[0]-ViewPos.RefPos()(0))*(SmokesList[i].pos[0]-ViewPos.RefPos()(0))+(SmokesList[i].pos[1]-ViewPos.RefPos()(1))*(SmokesList[i].pos[1]-ViewPos.RefPos()(1))+(SmokesList[i].pos[2]-ViewPos.RefPos()(2))*(SmokesList[i].pos[2]-ViewPos.RefPos()(2));
				if(SmoleL<LookRenge*LookRenge)//在视距内
				{

					glGetIntegerv(GL_VIEWPORT,viewport);
					glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
					glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
					gluProject(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2],mvmatrix,projmatrix,viewport,&WinPos[0],&WinPos[1],&WinPos[2]);
					if(WinPos[2]>0.0)
					if(WinPos[2]<1.0)
					if(WinPos[0]>-0.1f*(float)winwidth)
					if(WinPos[0]<1.1f*(float)winwidth)
					if(WinPos[1]>-0.1*(float)winheight)
					if(WinPos[1]<1.1*(float)winheight)//在视锥体内
					{
						glPushMatrix();	
						Pos3d=would.Matrix() * Vector3d(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2]) + would.RefPos();

						SmokeAlpha=1.0f;


						
						if(SmokesList[i].life<30.0f)
							SmokeAlpha=SmokeAlpha*SmokesList[i].life/30.0f;
						if((SmokesList[i].lifeMAX-SmokesList[i].life)<10.0f)
						{
							SmokeAlpha=SmokeAlpha*(SmokesList[i].lifeMAX-SmokesList[i].life)/10.0f;
						}

						if(Pos3d(2)<-(LookRenge*(5.0f/6.0f)))
							SmokeAlpha=SmokeAlpha*(LookRenge+(float)Pos3d(2))/(LookRenge/6.0f);
						if(Pos3d(2)>-1000.0f)
							SmokeAlpha=SmokeAlpha*(0.0f-(float)Pos3d(2)-300.0f)/700.0f;

						glColor4f(1.0f,1.0f,1.0f,SmokeAlpha);
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						
						if(SmokesList[i].type==1)
						{
							glColor4f(1.0f,0.5f,0.0f,SmokeAlpha);
							glBlendFunc(GL_SRC_ALPHA,GL_ONE);
						}
						glLoadIdentity();

						glBindTexture(GL_TEXTURE_2D, SmokesList[i].TexId);
						glTranslated(Pos3d(0) , Pos3d(1) , Pos3d(2));
						glScaled(SmokesList[i].size,SmokesList[i].size,SmokesList[i].size);
						if(Pos3d(2)<-500.0f)
						{
							glCallList(SmokeGLlist);
						}


						glColor4f(1.0f,1.0f,1.0f,1.0f);
						glPopMatrix();	
						
					
					}



				}
			}

		}
	//glPopMatrix();	
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void CSmoke::Init(int setGraphicLevel)
{
	GraphicLevel=setGraphicLevel;
	while(LoadSmoke(SmokeTexsNum))
		SmokeTexsNum=SmokeTexsNum+1;
	if(SmokeTexsNum>0)
		BuildSmoke(textureSmoke[0].texID);
}

bool CSmoke::LoadSmoke(int SmokeNum)
{
	if(SmokeNum==MAXSMOKETEXS)
		return false;
	char SmokeFileName[64]={0};
	sprintf(SmokeFileName,"Data/Smokes/smoke%d.tga",SmokeNum);
	FILE	*m_Filefighter;
	if ((m_Filefighter=fopen(SmokeFileName,"rb"))==NULL)
		return false;

	if (LoadTGA(&textureSmoke[SmokeNum], SmokeFileName))
	{											


				// Typical Texture Generation Using Data From The TGA ( CHANGE )textureAlphaFontFont[1]
		glGenTextures(1, &textureSmoke[SmokeNum].texID);				// Create The Texture ( CHANGE )
		glBindTexture(GL_TEXTURE_2D, textureSmoke[SmokeNum].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, textureSmoke[SmokeNum].bpp / 8, textureSmoke[SmokeNum].width, textureSmoke[SmokeNum].height, 0, textureSmoke[SmokeNum].type, GL_UNSIGNED_BYTE, textureSmoke[SmokeNum].imageData);
		if(GraphicLevel>0)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		}

		if (textureSmoke[SmokeNum].imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(textureSmoke[SmokeNum].imageData);					// Free The Texture Image Memory ( CHANGE )
		}

		return true;
	}

	return false;

}
