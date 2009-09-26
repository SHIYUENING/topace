#include "Unitdata.h"

bool VBOSupported=false;
Unitdata::Unitdata(void)
: UDPstate(UDMplane, 5, CRad(2.0), 0.1, 0.7)
,UDlife(-1)
,UDlockselect(false)
,UDlockde(false)
,waringde(false)
,isRSpeed(false)
,LockListNum(0)
,smokeTime(0)
,attackTGTNum(-1)
,AIact(1)
,AImode(1)
,attackedMissleNum(-1)
,fireTimer(0)
,RefireTime(900)
,LockTimer(0)
,LockOnTime(150)
,attackRange(10000.0f)
,mSpeed(30)
,AIactTimer1(0)
,AIactTimer2(0)
,inGunRange(false)
,inGunSoundRange(false)
,SelfNormalModelID(0)
,SelfLowModelID(0)
, isPlayer(false)
,AIType(0)
,Track_index(0)
,WingWidth(60.0f)
,TrackWidth(10.0f)
,AddTrack_index(0)
,TrackAlpha(0)
{
	for(int i=0;i<MAXTrack;i++)
	{
		//if(i%2==0)
		//	TracksTexCoord[i*2+1]=0.0f;
		//else
		//	TracksTexCoord[i*2+1]=1.0f;

		TracksColor[i*4+3]=0.0f;
		for(int j=0;j<3;j++)
			TracksColor[i*4+j]=1.0f;
	}
	for(int i=0;i<8;i++)
		VBOVertices[i]=0;
	
	for(int i=0;i<2;i++)
		VBOColor[i]=0;

	//for(int i=0;i<2;i++)
	//	VBOTexCoord[i]=0;
}

Unitdata::~Unitdata(void)
{
	if(VBOVertices[0])
		glDeleteBuffersARB(8,VBOVertices);
	if(VBOColor[0])
		glDeleteBuffersARB(2,VBOColor);
	//if(VBOTexCoord[0])
	//	glDeleteBuffersARB(2,VBOTexCoord);
}
/*
void Unitdata::setLinePos(void)//Transform& MView
{


	Transform TStmp1,TStmp2;
	TStmp1=UDMplane;
	TStmp2=UDMplane;
	TStmp1.TranslateInternal(Vector3d( 40+LinePosIndex%2*m_LineWidth, 0, -40));
	TStmp2.TranslateInternal(Vector3d(-40-LinePosIndex%2*m_LineWidth, 0, -40));
	//Vector3d tmp3d;
	//tmp3d=MView.Matrix() * UDMplane.RefPos() + MView.RefPos();
	if(LinePosIndex==MAXUNITLINE)
		LinePosIndex=0;

	LinePosL[LinePosIndex][0]=(float)TStmp1.RefPos()(0);
	LinePosL[LinePosIndex][1]=(float)TStmp1.RefPos()(1);
	LinePosL[LinePosIndex][2]=(float)TStmp1.RefPos()(2);

	LinePosR[LinePosIndex][0]=(float)TStmp2.RefPos()(0);
	LinePosR[LinePosIndex][1]=(float)TStmp2.RefPos()(1);
	LinePosR[LinePosIndex][2]=(float)TStmp2.RefPos()(2);
	LinePosIndex=LinePosIndex+1;

	if(LinePosIndex==MAXUNITLINE)
	{
		LinePosIndex=0;
		LinePosL[LinePosIndex][0]=(float)TStmp1.RefPos()(0);
		LinePosL[LinePosIndex][1]=(float)TStmp1.RefPos()(1);
		LinePosL[LinePosIndex][2]=(float)TStmp1.RefPos()(2);

		LinePosR[LinePosIndex][0]=(float)TStmp2.RefPos()(0);
		LinePosR[LinePosIndex][1]=(float)TStmp2.RefPos()(1);
		LinePosR[LinePosIndex][2]=(float)TStmp2.RefPos()(2);
		LinePosIndex=LinePosIndex+1;
	
	}

}


void Unitdata::PrintLinePos(Transform& MView)
{
	glPushMatrix();	
	glLoadIdentity();
	glLoadMatrixd(MView.Matrix4());
	glColor3f(1.0f,1.0f,1.0f);
	glDisable(GL_TEXTURE_2D);

	glLineWidth(2.0);
	glBegin(GL_TRIANGLE_FAN);

	for(int i=0;i<LinePosIndex;i++)
	{
		glVertex3f(LinePosL[i][0]+m_LineWidth,LinePosL[i][1],LinePosL[i][2]);
		glVertex3f(LinePosL[i][0],LinePosL[i][1]+m_LineWidth,LinePosL[i][2]);
		glVertex3f(LinePosL[i][0],LinePosL[i][1],LinePosL[i][2]+m_LineWidth);
	}


	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	for(int i=LinePosIndex;i<MAXUNITLINE;i++)
	{
		glVertex3f(LinePosL[i][0]+m_LineWidth,LinePosL[i][1],LinePosL[i][2]);
		glVertex3f(LinePosL[i][0],LinePosL[i][1]+m_LineWidth,LinePosL[i][2]);
		glVertex3f(LinePosL[i][0],LinePosL[i][1],LinePosL[i][2]+m_LineWidth);
	}


	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	for(int i=0;i<LinePosIndex;i++)
	{
		glVertex3f(LinePosR[i][0]+m_LineWidth,LinePosR[i][1],LinePosR[i][2]);
		glVertex3f(LinePosR[i][0],LinePosR[i][1]+m_LineWidth,LinePosR[i][2]);
		glVertex3f(LinePosR[i][0],LinePosR[i][1],LinePosR[i][2]+m_LineWidth);
	}


	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	for(int i=LinePosIndex;i<MAXUNITLINE;i++)
	{
		glVertex3f(LinePosR[i][0]+m_LineWidth,LinePosR[i][1],LinePosR[i][2]);
		glVertex3f(LinePosR[i][0],LinePosR[i][1]+m_LineWidth,LinePosR[i][2]);
		glVertex3f(LinePosR[i][0],LinePosR[i][1],LinePosR[i][2]+m_LineWidth);
	}


	glEnd();

	glEnable(GL_TEXTURE_2D);
	glPopMatrix();	

}

void Unitdata::setpos(int smokeN)
{
	if(UDposflag==MAXUNITSMOKE)
		UDposflag=0;
	UDposx[UDposflag]=(float)UDMplane.RefPos()(0);
	UDposy[UDposflag]=(float)UDMplane.RefPos()(1);
	UDposz[UDposflag]=(float)UDMplane.RefPos()(2);//(float)(rand()%100-50)/30.0f;
	UDposxMove[UDposflag]=(float)(rand()%100-50)/350.0f;
	UDposyMove[UDposflag]=(float)(rand()%100-50)/350.0f;
	UDposzMove[UDposflag]=(float)(rand()%100-50)/350.0f;
	smokeNum[UDposflag]=smokeN;
	UDposflag=UDposflag+1;
	
	


}
*/
void Unitdata::TurnTom(const Vector3d& Position){
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
void Unitdata::TurnTo(const Vector3d& Position){

	

    UDPstate.Acceleration = UDMplane.Matrix() * Vector3d(0, 0, 1) * 1.0;
    UDPstate.AngleAcceleration = 0, 0, 0;
    
    Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (all_elements(current == 0)){ return; }
    current = normalize(current);

    Vector3d top;
    top = UDMplane.Matrix() * Vector3d(0, 1, 0);
    if (all_elements(top == 0)){ return; }
    top = normalize(top);

    Vector3d target;
    target = Position - UDMplane.RefPos();
    if (all_elements(target == 0)){ return; }
    target = normalize(target);

    //首先求top在current、target平面上在垂直current方向上的投影方向newTopDirection
    Vector3d newTopDirection;
    newTopDirection = cross(cross(current, target), current);
    if (all_elements(newTopDirection == 0)){ return; }
    newTopDirection = normalize(newTopDirection);

    //求出newTop和top的夹角
    double theta = acos_s(dot(top, newTopDirection));
    if (theta > pi / 2.){
        theta = pi - theta;
        newTopDirection = -newTopDirection;
    }

    if (theta > pi / 16){
        //侧向翻滚
        Vector3d rotateAxis;
        rotateAxis = cross(top, newTopDirection);
        if (all_elements(rotateAxis == 0)){ return; }
        rotateAxis = normalize(rotateAxis);
        double rotateAngle = theta;
		TrackAlpha=0.0f;
		if(rotateAngle>pi / 32)
			TrackAlpha=1.2f;
		if(isRSpeed)
			rotateAngle=0.0;
		if(UDflag!=2)
			mSpeed=mSpeed-0.01f*float(rotateAngle*rotateAngle);
        UDPstate.AngleAcceleration = rotateAxis * rotateAngle - UDPstate.AngleVelocity;
    }
    else{
        //上下

        //改变target的方向，使其投影到top、current平面上
        Vector3d noTargetDirection;
        noTargetDirection = cross(current, top);
        if (all_elements(noTargetDirection == 0)){ return; }
        noTargetDirection = normalize(noTargetDirection);
        target -= dot(target, noTargetDirection) * noTargetDirection;

        //执行原跟踪程序
        double k = dot(current, target);

        Vector3d rotateAxis;
        rotateAxis = cross(current, target);
        if (all_elements(rotateAxis == 0)){ return; }
        rotateAxis = normalize(rotateAxis);

        double rotateAngle = acos_s(dot(current, target));

		if(isRSpeed)
			rotateAngle=0.0;

		TrackAlpha=0.0f;
		if(rotateAngle>pi / 2)
			TrackAlpha=1.2f;

		if((UDflag!=2)&&(AIType=0))
			mSpeed=mSpeed-0.002f*float(rotateAngle*rotateAngle);
		UDPstate.AngleAcceleration = rotateAxis * rotateAngle - UDPstate.AngleVelocity;
    }
}
double Unitdata::WaringTo(const Vector3d& Position)
{
	Vector3d target;
    target = Position - UDMplane.RefPos();
    if (norm2(target)<0.001){ return -2; }
    target = normalize(target);

	Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (norm2(current)<0.001){ return -2; }
    current = normalize(current);

	double cos_angle = dot(target, current);
	if((cos_angle>0.4)||(cos_angle<-0.4))
	{
		if(cos_angle<-0.9)
			TurnTo(Position);
		else
		{
			Transform TFEscape;
			TFEscape=UDMplane;
			TFEscape.TranslateInternal(Vector3d(0, 1000, 10));
			TurnTo(TFEscape.RefPos());
		}
	}

	return cos_angle;
}
/*
void Unitdata::m_DrawMissle(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge)
{
	
	for(int i=0;i<MAXUNITMISSLES;i++)
	{
		UNITMissles[i].m_Draw(m_world,m_winwidth,m_winheight,m_tmpLookRenge);
	}
	
}
*/
bool Unitdata::m_DrawSelf(const Vector3d& ViewPos,int m_winwidth,int m_winheight,float m_tmpLookRenge)
{

	
	//DrawTrack();
	inGunSoundRange=false;
	bool m_isDraw=false;
	if((UDlife>0)||(smokeTime>90))
	{


		float tmpX=(float)(ViewPos(0)-UDMplane.RefPos()(0));
		float tmpY=(float)(ViewPos(1)-UDMplane.RefPos()(1));
		float tmpZ=(float)(ViewPos(2)-UDMplane.RefPos()(2));
		UDwinl=tmpX*tmpX+tmpY*tmpY+tmpZ*tmpZ;
		if(UDwinl<m_tmpLookRenge*m_tmpLookRenge)
		{
			if(UDwinl<m_tmpLookRenge*m_tmpLookRenge*0.01)
				inGunSoundRange=true;
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
					m_isDraw=true;
					glDisable(GL_BLEND);
					glPushMatrix();
						if(isPlayer)
							glRotatef(180.0f, 0.0f, 1.0f, 0.0);
						if(UDfighterType==1)
						{//glScaled(0.01, 0.01, 0.01);
							if(ModelID[UDfighterType].Normal>-1)
								m_VBMD->ShowVBMD(ModelID[UDfighterType].Normal);
						}
						if(UDfighterType==2)
						{
							glRotatef(180.0f,0.0f,1.0f,0.0f);
							if(UDwinl<(5000.0f*5000.0f))
							{
								if(ModelID[UDfighterType].Normal>-1)
									m_VBMD->ShowVBMD(ModelID[UDfighterType].Normal);
							}
							else
							{
								if(ModelID[UDfighterType].Low>-1)
									m_VBMD->ShowVBMD(ModelID[UDfighterType].Low);
							}
						}
						if(UDfighterType==3)
						{
							glRotatef(180.0f, 0.0f, 1.0f, 0.0);
							m_VBMD->ShowVBMD(ModelID_MavePart_Normal);
						}
//							m_nj->ShowACMD(0,7,0,0,0,0,180,0,1.0,1.0,1.0);
					glPopMatrix();
					glEnable(GL_BLEND);
					
				}

			glPopMatrix();
		}
		else
			UDlockselect=false;
	}
	return m_isDraw;
}
void Unitdata::m_LaunchMissle(int m_TGT_Num)
{
}
void Unitdata::AttackTo(const Vector3d& Position)
{
	
	float tmpx=float(UDMplane.RefPos()(0)-Position(0));
	float tmpy=float(UDMplane.RefPos()(1)-Position(1));
	float tmpz=float(UDMplane.RefPos()(2)-Position(2));
	if((tmpx*tmpx+tmpy*tmpy+tmpz*tmpz)>attackRange*attackRange)
	{
		LockTimer=0;
		
		return;
	}

	Vector3d target;
    target = Position - UDMplane.RefPos();
    if (norm2(target)<0.001){ return; }
    target = normalize(target);

	Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (norm2(current)<0.001){ return; }
    current = normalize(current);

	double cos_angle = dot(target, current);

	if(((tmpx*tmpx+tmpy*tmpy+tmpz*tmpz)<(attackRange*attackRange/16.0))&&(cos_angle>0.95))
		inGunRange=true;
	else
		inGunRange=false;
	if(cos_angle>0.9)
		LockTimer=LockTimer+1;
	else
	{
		LockTimer=0;
		
	}

}
void Unitdata::MoveSpeed(void)
{

	if((mSpeed<25.0f)&&(!isRSpeed))
		isRSpeed=true;
	if(isRSpeed)
		mSpeed=mSpeed+0.05f;

	if(mSpeed>30.0f)
		isRSpeed=false;

	//addTrack();


}
void Unitdata::ResetData(void)
{
	
	UDlockselect=false;
	UDlockde=false;
	waringde=false;
	isRSpeed=false;
	LockListNum=0;
	smokeTime=0;
	attackTGTNum=-1;
	AIact=1;
	AImode=1;
	attackedMissleNum=-1;
	fireTimer=0;
	RefireTime=900;
	if(this->UDflag==2)
		RefireTime=450;
	LockTimer=0;
	LockOnTime=150;
	if(this->UDflag==2)
		LockOnTime=1;
	attackRange=10000.0f;
	mSpeed=30;
	AIactTimer1=0;
	AIactTimer2=0;
	inGunRange=false;
	if(!VBOSupported)
		return;

	initVBO();
}
void Unitdata::m_Sound(Transform& would,float LookRenge)
{

}
/*
void Unitdata::addTrack(void)
{
	if(!VBOSupported)
		return;
	for(int i=0;i<MAXTrack;i++)
	{
		TracksColor[i*4+3]=TracksColor[i*4+3]-0.012f;
	}
	for(int i=0;i<MAXTrack;i++)
	{
		TracksTexCoord[i*2]=TracksTexCoord[i*2]-1.0f/float(MAXTrack);
	}
	TracksTexCoord[Track_index*2]=1.0f;
	Transform TrackPos;
	if((Track_index%2)==0)
	{
		TracksColor[Track_index*4+3]=TrackAlpha;
		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(-WingWidth-TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0]=float(TrackPos.RefPos()(0));
		Tracks[Track_index*3+1]=float(TrackPos.RefPos()(1));
		Tracks[Track_index*3+2]=float(TrackPos.RefPos()(2));

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(WingWidth-TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*3]=float(TrackPos.RefPos()(0));
		Tracks[Track_index*3+1+MAXTrack*3]=float(TrackPos.RefPos()(1));
		Tracks[Track_index*3+2+MAXTrack*3]=float(TrackPos.RefPos()(2));

	
	}
	if((Track_index%2)==1)
	{
		TrackAlpha=0.0f;
		
		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(-WingWidth+TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0]=float(TrackPos.RefPos()(0));
		Tracks[Track_index*3+1]=float(TrackPos.RefPos()(1));
		Tracks[Track_index*3+2]=float(TrackPos.RefPos()(2));

		

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(WingWidth+TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*3]=float(TrackPos.RefPos()(0));
		Tracks[Track_index*3+1+MAXTrack*3]=float(TrackPos.RefPos()(1));
		Tracks[Track_index*3+2+MAXTrack*3]=float(TrackPos.RefPos()(2));
	}

	Track_index=Track_index+1;
	if(Track_index>=MAXTrack)
		Track_index=0;
}
*/
void Unitdata::addTrack(void)
{
	if(!VBOSupported)
		return;
	for(int i=0;i<(MAXTrack/2);i++)
	{
		TracksColor[i*2*4+3]=TracksColor[i*2*4+3]-0.012f;
	}

	Transform TrackPos;
	if((Track_index%2)==0)
	{

		TracksColor[Track_index*4+3]=TrackAlpha;
		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(-WingWidth,0.0,0.0));
		Tracks[Track_index*3+0]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2]=TrackPos.RefPos()(2);
		Tracks[Track_index*3+0+MAXTrack*3]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*3]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*3]=TrackPos.RefPos()(2);

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(WingWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*6]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*6]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*6]=TrackPos.RefPos()(2);
		Tracks[Track_index*3+0+MAXTrack*9]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*9]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*9]=TrackPos.RefPos()(2);
	
	}
	if((Track_index%2)==1)
	{
		
		TrackAlpha=0.0f;
		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(-WingWidth-TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2]=TrackPos.RefPos()(2);

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(-WingWidth+TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*3]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*3]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*3]=TrackPos.RefPos()(2);

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(WingWidth+TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*6]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*6]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*6]=TrackPos.RefPos()(2);

		TrackPos=UDMplane;
		TrackPos.TranslateInternal(Vector3d(WingWidth-TrackWidth,0.0,0.0));
		Tracks[Track_index*3+0+MAXTrack*9]=TrackPos.RefPos()(0);
		Tracks[Track_index*3+1+MAXTrack*9]=TrackPos.RefPos()(1);
		Tracks[Track_index*3+2+MAXTrack*9]=TrackPos.RefPos()(2);
	
	}

	
	Track_index=Track_index+1;
	if(Track_index>=MAXTrack)
		Track_index=0;

	

}

void Unitdata::DrawTrack(void)
{
	if(smokeTime>0)
		for(int i=0;i<(MAXTrack/2);i++)
		{
			TracksColor[i*2*4+3]=TracksColor[i*2*4+3]-0.03f;
		}
	else
	{
		if(UDlife<1)
			return;
	}
	if(Track_index>0)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOColor[0] );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, Track_index*4*sizeof(float), TracksColor, GL_DYNAMIC_DRAW_ARB );
		//glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOTexCoord[0] );
		//glBufferDataARB( GL_ARRAY_BUFFER_ARB, Track_index*2*sizeof(float), TracksTexCoord, GL_DYNAMIC_DRAW_ARB );
		for(int i=0;i<4;i++)
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOVertices[i*2] );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, Track_index*3*sizeof(float), &Tracks[MAXTrack*3*i], GL_DYNAMIC_DRAW_ARB );
		}
	}

	if(Track_index<MAXTrack)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOColor[1] );
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, (MAXTrack-Track_index)*4*sizeof(float), &TracksColor[Track_index*4], GL_DYNAMIC_DRAW_ARB );
		//glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOTexCoord[1] );
		//glBufferDataARB( GL_ARRAY_BUFFER_ARB, (MAXTrack-Track_index)*2*sizeof(float), &TracksTexCoord[Track_index*4], GL_DYNAMIC_DRAW_ARB );
		for(int i=0;i<4;i++)
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOVertices[i*2+1] );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, (MAXTrack-Track_index)*3*sizeof(float), &Tracks[MAXTrack*3*i+Track_index*3], GL_DYNAMIC_DRAW_ARB );
		}
	}

	if(Track_index>0)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOColor[0] );
		glColorPointer( 4, GL_FLOAT, 0, (char *) NULL );
		//glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOTexCoord[0] );
		//glColorPointer( 2, GL_FLOAT, 0, (char *) NULL );
		for(int i=0;i<4;i++)
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOVertices[i*2] );
			glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
			glDrawArrays( GL_TRIANGLE_STRIP, 0, Track_index );
		}
	}

	if(Track_index<MAXTrack)
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOColor[1] );
		glColorPointer( 4, GL_FLOAT, 0, (char *) NULL );
		//glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOTexCoord[1] );
		//glColorPointer( 2, GL_FLOAT, 0, (char *) NULL );
		for(int i=0;i<4;i++)
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, VBOVertices[i*2+1] );
			glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
			glDrawArrays( GL_TRIANGLE_STRIP, 0, MAXTrack-Track_index );
		}
	}


	
	/*
	glEnableClientState( GL_VERTEX_ARRAY );	
	glEnableClientState( GL_COLOR_ARRAY );	
	glVertexPointer( 3, GL_FLOAT, 0, Tracks );
	glColorPointer( 4, GL_FLOAT, 0, TracksColor );
	glDrawArrays( GL_LINE_STRIP, 0, MAXTrack );

	glVertexPointer( 3, GL_FLOAT, 0, Tracks+sizeof(float)*MAXTrack*3 );
	glColorPointer( 4, GL_FLOAT, 0, TracksColor );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, MAXTrack );

	glVertexPointer( 3, GL_FLOAT, 0, Tracks+sizeof(float)*MAXTrack*6 );
	glColorPointer( 4, GL_FLOAT, 0, TracksColor );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, MAXTrack );

	glVertexPointer( 3, GL_FLOAT, 0, Tracks+sizeof(float)*MAXTrack*9 );
	glColorPointer( 4, GL_FLOAT, 0, TracksColor );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, MAXTrack );
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	*/
	
/*	glBegin(GL_TRIANGLE_STRIP);
	for(int i=Track_index;i<MAXTrack;i++)
	{
		glVertex3f(Tracks[i*3],Tracks[i*3+1],Tracks[i*3+2]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=Track_index;i<MAXTrack;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*3],Tracks[i*3+1+MAXTrack*3],Tracks[i*3+2+MAXTrack*3]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=Track_index;i<MAXTrack;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*6],Tracks[i*3+1+MAXTrack*6],Tracks[i*3+2+MAXTrack*6]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=Track_index;i<MAXTrack;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*9],Tracks[i*3+1+MAXTrack*9],Tracks[i*3+2+MAXTrack*9]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<Track_index;i++)
	{
		glVertex3f(Tracks[i*3],Tracks[i*3+1],Tracks[i*3+2]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<Track_index;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*3],Tracks[i*3+1+MAXTrack*3],Tracks[i*3+2+MAXTrack*3]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<Track_index;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*6],Tracks[i*3+1+MAXTrack*6],Tracks[i*3+2+MAXTrack*6]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<Track_index;i++)
	{
		glVertex3f(Tracks[i*3+MAXTrack*9],Tracks[i*3+1+MAXTrack*9],Tracks[i*3+2+MAXTrack*9]);
		glColor4f(1.0f,1.0f,1.0f,TracksColor[i*4+3]);
	}
	glEnd();
*/
	

}
void Unitdata::initVBO(void)
{
	if(VBOVertices[0])
		glDeleteBuffersARB(8,VBOVertices);
	if(VBOColor[0])
		glDeleteBuffersARB(2,VBOColor);
	//if(VBOTexCoord[0])
	//	glDeleteBuffersARB(2,VBOTexCoord);
	glGenBuffersARB( 8, VBOVertices);
	glGenBuffersARB( 2, VBOColor);
	//glGenBuffersARB( 2, VBOTexCoord);
}