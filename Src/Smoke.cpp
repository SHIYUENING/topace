#include "Smoke.h"
#include <stdio.h>
CSmoke::CSmoke(void)
: SmokeNodeNumber(0)
, SmokeGLlist(0)
, GraphicLevel(1)
, SmokeTexsNum(0)
, CloudTexID(0)
, base(0)
, CloudSize(7500)
,m_IsSkip(false)
{
	LastPos[0]=0.0f;
	LastPos[1]=0.0f;
}

CSmoke::~CSmoke(void)
{
	DeleteCloud();
	DeleteSmoke();

}

void CSmoke::AddSmoke(float posx, float posy, float posz, float size, float sizeMove, float life ,int type,int CloudListNum)
{
	int tmp=0;
	SmokeNodeNumber=SmokeNodeNumber+1;
	if(SmokeNodeNumber>=MAXSMOKESLIST)
	{
		SmokeNodeNumber=0;
		
	}
	while(SmokesList[SmokeNodeNumber].type==2)
	{
		tmp=tmp+1;
		if(tmp>=MAXSMOKESLIST)
			return;

		SmokeNodeNumber=SmokeNodeNumber+1;
		if(SmokeNodeNumber>=MAXSMOKESLIST)
		{
			SmokeNodeNumber=0;
		
		}
	}
	
	if(type!=2)	
		SmokesList[SmokeNodeNumber].TexId=textureSmoke[rand()%SmokeTexsNum].texID;
	else
		SmokesList[SmokeNodeNumber].TexId=CloudListNum;

	SmokesList[SmokeNodeNumber].pos[0]=posx;
	SmokesList[SmokeNodeNumber].pos[1]=posy;
	SmokesList[SmokeNodeNumber].pos[2]=posz;
	if(type!=2)
	{
		SmokesList[SmokeNodeNumber].posMove[0]=(float)(rand()%100-50)/300.0f;
		SmokesList[SmokeNodeNumber].posMove[1]=(float)(rand()%100-50)/300.0f;
		SmokesList[SmokeNodeNumber].posMove[2]=(float)(rand()%100-50)/300.0f;
	}
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
bool CSmoke::BuildCloud(void)
{

	CDDS loadDDS;

	CloudTexID=loadDDS.loadCompressedTexture("Data/sky/Cloud.dds");
	if(CloudTexID==0)
		return false;
	else
	{
		float	cx;											// Holds Our X Character Coord
		float	cy;											// Holds Our Y Character Coord

		base=glGenLists(16);								// Creating 256 Display Lists
		glBindTexture(GL_TEXTURE_2D, CloudTexID);			// Select Our Font Texture
		for (int loop=0; loop<16; loop++)						// Loop Through All 256 Lists
		{
			cx=float(loop%4)/4.0f;						// X Position Of Current Character
			cy=float(loop/4)/4.0f;						// Y Position Of Current Character

			glNewList(base+loop,GL_COMPILE);				// Start Building A List	
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(cx,1-cy-0.25f);		// Texture Coord (Bottom Left)
					glVertex2f(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+0.25f,1-cy-0.25f);	// Texture Coord (Bottom Right)
					glVertex2f(CloudSize,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+0.25f,1-cy);			// Texture Coord (Top Right)
					glVertex2f(CloudSize,CloudSize);						// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
					glVertex2f(0,CloudSize);						// Vertex Coord (Top Left)
				glEnd();									// Done Building Our Quad (Character)
				glTranslated(10.0f,0.0f,0.0f);						// Move To The Right Of The Character
			glEndList();									// Done Building The Display List
		}	
	}
	return true;
}

void CSmoke::BuildSmoke(unsigned int settexID)
{
	SmokeGLlist=glGenLists(1);
	glBindTexture(GL_TEXTURE_2D, settexID);
	glNewList(SmokeGLlist,GL_COMPILE);
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(0.0f,0.0f);			// Texture Coord (Bottom Left)
				glVertex2i(-70,-70);						// Vertex Coord (Bottom Left)
				glTexCoord2f(1.0f,0.0f);	// Texture Coord (Bottom Right)
				glVertex2i(70,-70);						// Vertex Coord (Bottom Right)
				glTexCoord2f(1.0f,1.0f);			// Texture Coord (Top Right)
				glVertex2i(70,70);						// Vertex Coord (Top Right)
				glTexCoord2f(0.0f,1.0f);					// Texture Coord (Top Left)
				glVertex2i(-70,70);						// Vertex Coord (Top Left)
			glEnd();

	glEndList();

}
void CSmoke::DrawSmoke(const Vector3d& ViewPos,Transform& would,int winwidth,int winheight,float LookRenge)
{

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	float ViewPos3f[3]={(float)ViewPos(0),(float)ViewPos(1),(float)ViewPos(2)};
	float LookRenge_2=LookRenge*LookRenge;
		for(int i=0;i<MAXSMOKESLIST;i++)
		{	
			if(SmokesList[i].life>0.0f)//存在
			{
				if(!m_IsSkip)
				{
					tmpX=SmokesList[i].pos[0]-ViewPos3f[0];
					tmpY=SmokesList[i].pos[1]-ViewPos3f[1];
					tmpZ=SmokesList[i].pos[2]-ViewPos3f[2];
					SmoleL=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
					if(SmoleL<LookRenge_2)//在视距内
					{
						if(SmokesList[i].type==2)
						{
							if(SmoleL>2000.0f*2000.0f)
							{
								glGetIntegerv(GL_VIEWPORT,viewport);
								glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
								glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
								gluProject(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2],mvmatrix,projmatrix,viewport,&WinPos[0],&WinPos[1],&WinPos[2]);
								if(WinPos[2]<1.0)
								{
									glBindTexture(GL_TEXTURE_2D, CloudTexID);
									glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
									glPushMatrix();
										SmokeAlpha=1.0f;
										if(SmoleL>(LookRenge_2*4.0f/9.0f))
											SmokeAlpha=SmokeAlpha*(LookRenge_2-SmoleL)/(LookRenge_2*5.0f/9.0f);
										if(SmoleL<8000.0f*8000.0f)
											SmokeAlpha=SmokeAlpha*(SmoleL-2000.0f*2000.0f)/(8000.0f*8000.0f-2000.0f*2000.0f);
										glColor4f(1.0f,1.0f,1.0f,SmokeAlpha);
										glTranslated(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2]);
										glScaled(SmokesList[i].size,SmokesList[i].size,SmokesList[i].size);
										float mat[16]; 
										glGetFloatv(GL_MODELVIEW_MATRIX, mat);
										mat[1] = mat[2] = mat[6] = 0; 
										mat[4] = mat[8] = mat[9] = 0; 
										mat[0] = mat[5] = mat[10] = 1;
										glLoadMatrixf(mat);
										glCallList(base+SmokesList[i].TexId);
										glColor4f(1.0f,1.0f,1.0f,1.0f);
									glPopMatrix();
								}
							}
						}
						else
						{
							if(SmoleL>500.0f*500.0f)
							{
								glGetIntegerv(GL_VIEWPORT,viewport);
								glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
								glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
								gluProject(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2],mvmatrix,projmatrix,viewport,&WinPos[0],&WinPos[1],&WinPos[2]);
								if(WinPos[2]<1.0)
								if(WinPos[0]>-0.2f*(float)winwidth)
								if(WinPos[0]<1.2f*(float)winwidth)
								if(WinPos[1]>-0.2*(float)winheight)
								if(WinPos[1]<1.2*(float)winheight)//在视锥体内
								{
									glBindTexture(GL_TEXTURE_2D, SmokesList[i].TexId);
									glPushMatrix();	
										SmokeAlpha=1.0f;
										if(SmokesList[i].life<30.0f)
											SmokeAlpha=SmokeAlpha*SmokesList[i].life/30.0f;
										if((SmokesList[i].lifeMAX-SmokesList[i].life)<10.0f)
											SmokeAlpha=SmokeAlpha*(SmokesList[i].lifeMAX-SmokesList[i].life)/10.0f;
										if(SmoleL>(LookRenge_2*4.0f/9.0f))
											SmokeAlpha=SmokeAlpha*(LookRenge_2-SmoleL)/(LookRenge_2*5.0f/9.0f);
										if(SmoleL<1000.0f*1000.0f)
											SmokeAlpha=SmokeAlpha*(SmoleL-500.0f*500.0f)/(1000.0f*1000.0f-500.0f*500.0f);
										if(SmokesList[i].type==1)
										{
											glColor4f(1.0f,0.5f,0.0f,SmokeAlpha);
											glBlendFunc(GL_SRC_ALPHA,GL_ONE);
										}
										else
										{
											glColor4f(1.0f,1.0f,1.0f,SmokeAlpha);
											glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
										}
										glTranslated(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2]);
										glScaled(SmokesList[i].size,SmokesList[i].size,SmokesList[i].size);
										float mat[16]; 
										glGetFloatv(GL_MODELVIEW_MATRIX, mat);
										mat[1] = mat[2] = mat[6] = 0; 
										mat[4] = mat[8] = mat[9] = 0; 
										mat[0] = mat[5] = mat[10] = 1;
										glLoadMatrixf(mat);
										glCallList(SmokeGLlist);
										glColor4f(1.0f,1.0f,1.0f,1.0f);
									glPopMatrix();
								}
							}
						}
				/*		glGetIntegerv(GL_VIEWPORT,viewport);
						glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
						glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
						gluProject(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2],mvmatrix,projmatrix,viewport,&WinPos[0],&WinPos[1],&WinPos[2]);
						if(WinPos[2]>0.0)
						if(WinPos[2]<1.0)
						{
							if(SmokesList[i].type==2)
							{
								glBindTexture(GL_TEXTURE_2D, CloudTexID);
									glPushMatrix();
										SmokeAlpha=1.0f;
										if(SmoleL>(LookRenge_2*4.0f/9.0f))
											SmokeAlpha=SmokeAlpha*(LookRenge_2-SmoleL)/(LookRenge_2*5.0f/9.0f);

										if(SmoleL<8000.0f*8000.0f)
											SmokeAlpha=SmokeAlpha*(SmoleL-2000.0f*2000.0f)/(8000.0f*8000.0f-2000.0f*2000.0f);
										glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
										glColor4f(1.0f,1.0f,1.0f,SmokeAlpha);
										glTranslated(SmokesList[i].pos[0],SmokesList[i].pos[1],SmokesList[i].pos[2]);
										glScaled(SmokesList[i].size,SmokesList[i].size,SmokesList[i].size);
										float mat[16]; 
										glGetFloatv(GL_MODELVIEW_MATRIX, mat);
										mat[1] = mat[2] = mat[6] = 0; 
										mat[4] = mat[8] = mat[9] = 0; 
										mat[0] = mat[5] = mat[10] = 1;
										glLoadMatrixf(mat);
										glCallList(base+SmokesList[i].TexId);
										glColor4f(1.0f,1.0f,1.0f,1.0f);
									glPopMatrix();						
							
							
							}

							if(WinPos[0]>-0.2f*(float)winwidth)
							if(WinPos[0]<1.2f*(float)winwidth)
							if(WinPos[1]>-0.2*(float)winheight)
							if(WinPos[1]<1.2*(float)winheight)//在视锥体内
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
								if((Pos3d(2)>-1000.0f)&&(SmokesList[i].type!=1))
									SmokeAlpha=SmokeAlpha*(0.0f-(float)Pos3d(2)-300.0f)/700.0f;

								glColor4f(1.0f,1.0f,1.0f,SmokeAlpha);
								glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
								
								if(SmokesList[i].type==1)
								{
									glColor4f(1.0f,0.5f,0.0f,SmokeAlpha);
									glBlendFunc(GL_SRC_ALPHA,GL_ONE);
								}
								glLoadIdentity();

								glEnable(GL_BLEND);
								glBindTexture(GL_TEXTURE_2D, SmokesList[i].TexId);

								glTranslated(Pos3d(0) , Pos3d(1) , Pos3d(2));
								glScaled(SmokesList[i].size,SmokesList[i].size,SmokesList[i].size);
								if(Pos3d(2)<-500.0f)
									glCallList(SmokeGLlist);
								else
									if((SmokesList[i].type==1)&&(Pos3d(2)<-300.0f))
										glCallList(SmokeGLlist);

								glColor4f(1.0f,1.0f,1.0f,1.0f);
								glPopMatrix();	
								
							
							}
						}
						*/
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

void CSmoke::Init(int setGraphicLevel,int useCloud)
{
	GraphicLevel=setGraphicLevel;
	while(LoadSmoke(SmokeTexsNum))
		SmokeTexsNum=SmokeTexsNum+1;
	if(SmokeTexsNum>0)
		BuildSmoke(textureSmoke[0].texID);
	
	if(useCloud>0)
	{
		BuildCloud();
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<10;j++)
			{
				
				AddCloud(float((i-5)*20000+rand()%1000),float(40000+rand()%10000),float((j-5)*20000+rand()%1000));
			}
		}
	}
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


void CSmoke::DeleteCloud(void)
{
	if(CloudTexID==0)
		return;
	glDeleteLists(base,16);
	glDeleteTextures(1,&CloudTexID);
}

void CSmoke::DeleteSmoke(void)
{
	glDeleteLists(SmokeGLlist,1);
	for(int i=0;i<SmokeTexsNum;i++)
		glDeleteTextures(1,&textureSmoke[i].texID);
}

void CSmoke::AddCloud(float posx, float posy, float posz)
{
	AddSmoke(posx+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
		
	AddSmoke(posx+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx-CloudSize/2.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/2.0f+(float)(rand()%100-50),posz+CloudSize/2.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);

	AddSmoke(posx+CloudSize/4.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize*0.8f+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx+CloudSize/4.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize*0.8f+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx-CloudSize/4.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize*0.8f+(float)(rand()%100-50),posz-CloudSize/4.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);
	AddSmoke(posx-CloudSize/4.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize*0.8f+(float)(rand()%100-50),posz+CloudSize/4.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%12);

	AddSmoke(posx+CloudSize/5.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/3.0f+(float)(rand()%100-50),posz+CloudSize/5.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%16);
	AddSmoke(posx+CloudSize/5.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/3.0f+(float)(rand()%100-50),posz-CloudSize/5.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%16);
	AddSmoke(posx-CloudSize/5.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/3.0f+(float)(rand()%100-50),posz-CloudSize/5.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%16);
	AddSmoke(posx-CloudSize/5.0f+(float)(rand()%100-50)*100.0f,posy+CloudSize/3.0f+(float)(rand()%100-50),posz+CloudSize/5.0f+(float)(rand()%100-50)*100.0f,1.0f,0.0f,150.0f,2,rand()%16);


}
