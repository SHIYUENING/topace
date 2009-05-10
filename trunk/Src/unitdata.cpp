#include "Unitdata.h"

Unitdata::Unitdata(void)
: UDPstate(UDMplane, 5, CRad(2.0), CRad(1), CRad(0.1), 0.1, 0.4)
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
{




	for(int i=0;i<MAXweapon;i++)
		weapon[MAXweapon]=-1;

}

Unitdata::~Unitdata(void)
{
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
void Unitdata::TurnTo(const Vector3d& Position){

	

    UDPstate.Acceleration = UDMplane.Matrix() * Vector3d(0, 0, 1) * 1.0;
    
    Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (all_elements(current == 0)){
        UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
        return;
    }
    current = normalize(current);

    Vector3d top;
    top = UDMplane.Matrix() * Vector3d(0, 1, 0);
    if (all_elements(top == 0)){
        UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
        return;
    }

    top = normalize(top);

    Vector3d target;
    target = Position - UDMplane.RefPos();
    if (all_elements(target == 0)){
        UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
        return;
    }

    target = normalize(target);

    //首先求top在current、target平面上在垂直current方向上的投影方向newTopDirection
    Vector3d newTopDirection;
    newTopDirection = cross(cross(current, target), current);
    if (all_elements(newTopDirection == 0)){
        UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
        return;
    }

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
        if (all_elements(rotateAxis == 0)){
            UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
            return;
        }
        rotateAxis = normalize(rotateAxis);
        double rotateAngle = theta;

		if(isRSpeed)
			rotateAngle=0.0;
		mSpeed=mSpeed-0.01f*float(rotateAngle*rotateAngle);
        UDPstate.set_AngleAcceleration(Vector3d(rotateAxis * rotateAngle - UDPstate.AngleVelocity));
    }
    else{
        //上下

        //改变target的方向，使其投影到top、current平面上
        Vector3d noTargetDirection;
        noTargetDirection = cross(current, top);
        if (all_elements(noTargetDirection == 0)){
            UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
            return;
        }

        noTargetDirection = normalize(noTargetDirection);
        target -= dot(target, noTargetDirection) * noTargetDirection;

        //执行原跟踪程序
        double k = dot(current, target);

        Vector3d rotateAxis;
        rotateAxis = cross(current, target);
        if (all_elements(rotateAxis == 0)){
            UDPstate.set_AngleAcceleration(Vector3d(0, 0, 0));
            return;
        }

        rotateAxis = normalize(rotateAxis);

        double rotateAngle = acos_s(dot(current, target));

		if(isRSpeed)
			rotateAngle=0.0;

		mSpeed=mSpeed-0.002f*float(rotateAngle*rotateAngle);
		UDPstate.set_AngleAcceleration(Vector3d(rotateAxis * rotateAngle - UDPstate.AngleVelocity));
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
bool Unitdata::m_DrawSelf(const Vector3d& m_world,int m_winwidth,int m_winheight,float m_tmpLookRenge)
{

	bool m_isDraw=false;
	if((UDlife>0)||(smokeTime>90))
	{


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
					m_isDraw=true;
					glDisable(GL_BLEND);
					glPushMatrix();
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

	if(((tmpx*tmpx+tmpy*tmpy+tmpz*tmpz)<(attackRange*attackRange/9))&&(cos_angle>0.95))
		inGunRange=true;
	else
		inGunRange=false;
	if(cos_angle>0.5)
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
	LockTimer=0;
	LockOnTime=150;
	attackRange=10000.0f;
	mSpeed=30;
	AIactTimer1=0;
	AIactTimer2=0;
	inGunRange=false;
}
