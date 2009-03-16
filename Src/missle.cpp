#include "missle.h"
Missledata::Missledata(void)
: UDPstate(UDMplane, 6, CRad(2), 0.1, 0.4),UDlife(0)
 
{

	UDlife=-1;
	UDposflag=0;
	smokeTime=0;
	timer=0;
	
}

Missledata::~Missledata(void)
{
}

void Missledata::TurnTo(const Vector3d& Position){
	Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (!all_elements(current == 0)){
        current = normalize(current);
    }

    Vector3d target;
    target = Position - UDMplane.RefPos();
    if (!all_elements(target == 0)){
        target = normalize(target);
    }

    double k = dot(current, target);

    Vector3d rotateAxis;
    rotateAxis = cross(current, target);
    if (!all_elements(rotateAxis == 0)){
        rotateAxis = normalize(rotateAxis);
    }

    double rotateAngle = acos_s(dot(current, target));

    UDPstate.AngleAcceleration = rotateAxis * rotateAngle - UDPstate.AngleVelocity;
	//UDPstate.Acceleration = UDMplane.Matrix() * Vector3d(0, 0, 1) * 35;
	
}
/*
void Missledata::setpos(int smokeN)
{
	if(UDposflag==MAXMISSLESMOKE)
		UDposflag=0;
	UDposx[UDposflag]=(float)UDMplane.RefPos()(0);
	UDposy[UDposflag]=(float)UDMplane.RefPos()(1);
	UDposz[UDposflag]=(float)UDMplane.RefPos()(2);
	UDposxMove[UDposflag]=(float)(rand()%100-50)/300.0f;
	UDposyMove[UDposflag]=(float)(rand()%100-50)/300.0f;
	UDposzMove[UDposflag]=(float)(rand()%100-50)/300.0f;
	UDposzSIZE[UDposflag]=(float)(rand()%40+80)/100.0f;
	smokeNum[UDposflag]=smokeN;
	UDposflag=UDposflag+1;

}
void Missledata::setposF(void)
{
	if(UDposflagF==MAXMISSLESMOKE)
		UDposflagF=0;
	UDposxF[UDposflag]=(float)UDMplane.RefPos()(0);
	UDposyF[UDposflag]=(float)UDMplane.RefPos()(1);
	UDposzF[UDposflag]=(float)UDMplane.RefPos()(2);
	UDposflagF=UDposflagF+1;

}
*/
void Missledata::m_Draw(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge)
{
	if(UDlife>0)
	{

		//UDlife=UDlife-1;
		//timer=timer+1;
		float tmpX=(float)(m_world(0)-UDMplane.RefPos()(0));
		float tmpY=(float)(m_world(1)-UDMplane.RefPos()(1));
		float tmpZ=(float)(m_world(2)-UDMplane.RefPos()(2));
		UDwinl=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
		if(UDwinl<m_tmpLookRenge*m_tmpLookRenge)
		{
			glPushMatrix();
				glMultMatrixd(UDMplane.Matrix4());
				GLint viewport[4];
				GLdouble mvmatrix[16],projmatrix[16];
				GLdouble SUFwinX,SUFwinY,SUFwinZ;
				glGetIntegerv(GL_VIEWPORT,viewport);
				glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
				glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
				gluProject(0.0,0.0,0.0,mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);
				UDwinx=(float)SUFwinX;
				UDwiny=(float)SUFwinY;
				UDwinz=(float)SUFwinZ;
				if(UDwinz<1.0f)//目标在屏幕前方
				if((UDwinx>-m_winwidth*0.1f)&&(UDwinx<m_winwidth*1.1f)&&(UDwiny>-m_winheight*0.1f)&&(UDwiny<m_winheight*1.1f))
				{
					glDisable(GL_BLEND);
					glPushMatrix();
					//glScaled(10, 10, 10);
					glRotatef(180.0, 0.0, 1.0, 0.0);
					m_VBMD->ShowVBMD(ModelID[3].Normal);
					//m_nj->ShowACMD(0,2,0,0,0,0,180,0,1.0,1.0,1.0);
					glPopMatrix();
					glEnable(GL_BLEND);
				}
			glPopMatrix();
		}
	}
}
//using namespace std;
//list<Missledata>   MissleList;
/*
void Missledata::m_DrawSmoke(
							 int m_winwidth,
							 int m_winheight,
							 int i,
							 float& SmokePosX,
							 float& SmokePosY,
							 float& SmokePosZ,
							 float& SmokeAlpha,
							 float& SmokeMAlpha)
{
	SmokePosX=-1.0f;
	SmokePosY=-1.0f;
	SmokePosZ=-1.0f;
	SmokeAlpha=-1.0f;
	SmokeMAlpha=-1.0f;
	//if((UDlife>0)||(smokeTime>0))
	//{
	//	smokeTime=smokeTime-1;
	//	if(UDlife>0)
	//		setpos(((int)rand())%SmokeNumber);
	//	if(UDwinl<(m_tmpLookRenge*m_tmpLookRenge))
	//	{
	//		for(int i = 0 ; i < MAXMISSLESMOKE ; i + + )
	//		{
				UDposx[i] = UDposx[i] + UDposxMove[i];
				UDposy[i] = UDposy[i] + UDposyMove[i];
				UDposz[i] = UDposz[i] + UDposzMove[i];
				GLint viewport[4];
				GLdouble mvmatrix[16],projmatrix[16];
				GLdouble SUFwinX,SUFwinY,SUFwinZ;
				glGetIntegerv(GL_VIEWPORT,viewport);
				glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
				glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
				gluProject(UDposx[i],UDposy[i],UDposz[i],mvmatrix,projmatrix,viewport,&SUFwinX,&SUFwinY,&SUFwinZ);

				int tmp=i;
				if(tmp==100)
					tmp=0;

				if((SUFwinZ<1.0)&&(SUFwinZ>0.0))//可视范围内
				if((SUFwinX>(-0.1*m_winwidth))&&(SUFwinY>(-0.1*m_winheight))&&(SUFwinX<(m_winwidth*1.1))&&(SUFwinY<(m_winheight*1.1)))//窗口内
				{
					//Vector3d tmp3d;
					//tmp3d=Transform.Matrix() * Vector3d(UDposx[tmp],UDposy[tmp],UDposz[tmp]) + Transform.RefPos();
					SmokePosX=UDposx[tmp];
					SmokePosY=UDposy[tmp];
					SmokePosZ=UDposz[tmp];

					int smokelife=i-UDposflag;
					if(smokelife<0)
							smokelife=smokelife+MAXMISSLESMOKE;
					if(smokelife<(MAXMISSLESMOKE-1))
					{
						if(smokelife>(MAXMISSLESMOKE-10))
						{
							if(UDlife>0)
								SmokeMAlpha=((float)(smokelife-(MAXMISSLESMOKE-10)))/9.0f;
								//glPrintSmokeM((float)tmp3d(0),(float)tmp3d(1),(float)tmp3d(2),(smokelife-(MAXMISSLESMOKE-10))/9.0f);
							smokelife=MAXMISSLESMOKE-(smokelife-(MAXMISSLESMOKE-10))*(MAXMISSLESMOKE/10);
						}
						else
						{
							if(smokelife<(MAXMISSLESMOKE/2))
								smokelife=smokelife*2;
							else
								smokelife=MAXMISSLESMOKE;
						}
						if(UDlife>0)
							SmokeAlpha=(float)smokelife/(float)MAXMISSLESMOKE;
						else
							SmokeAlpha=smokelife*((float)smokeTime/100.0f)/(float)MAXMISSLESMOKE;
					
					
					}
				}
	
			
	//		}
		
		
	//	}
	
	//}
}
*/
