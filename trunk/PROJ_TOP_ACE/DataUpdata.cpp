#include "DataUpdata.h"
#include "KeyInput.h"
#include "ExchangeThread.h"
#include "UnitsList.h"
#include "SoundSys.h"
#include"IniFile.h"
float angleR=0.0f;
float Test3dsFrame=0.0f;
float maxFreme=100.0f;
int TotalFrame=0;
bool Test3dsFrameSwitch=false;
//extern tKeyInput KeyInput;
CUnitMath TestView;//TestUnit,
CUnitMath TestUnitExchange;
int ReadingThreadNum=0;
float extern moveZ;
float extern moveY;
float extern moveX;
float extern PosOrgY;
float extern PosOrgZ;
float extern GoX;
float extern GoZ;
extern float moveZSpeed;
CExchangeThread ThreadDataUpdata;
CSceneUnit SceneUnitTest;
CUnitsList UnitsList;
CSoundSys * SoundSysTest;
extern float zoomsize;
extern float touchX;
extern float touchY;
extern float Touchang;
extern float TouchangY;
float NoTouchMoveTimes=0.0f;

float TouchMoveOverride=0.0f;
float TouchZoomOverride=0.0f;
__m128 ViewMat[4];
CUnitMath ViewTGTUnit,ViewUnit;
__m128 ViewTGTPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
__m128 ViewPos=_mm_set_ps(1.0f,250.0f,250.0f,250.0f);
float GFXPosMove[2]={0.0f};
float PosMove[3]={0.0f};
float PosTurn[2]={0.0f};
float LimitZ[2]={3500.0f,1900.0f};
float ViewLen=100.0f;
extern float TestNum;
float MoveLimit=0.0f;
extern int SceneSelect;

extern float blurnumtmp1;
float TouchPosO[2]={0.0f};
extern float GFXMoveMask[2];
void UpdataKeys()
{
	PosMove[0]=0.0f;
	PosMove[1]=0.0f;
	PosMove[2]=0.0f;
	PosTurn[0]=0.0f;
	PosTurn[1]=0.0f;
	PosMove[0]=-moveZSpeed*float(GFXMoveMask[0])*0.01f;
	PosMove[1]=-moveZSpeed*float(GFXMoveMask[1])*0.01f;
	if(GFXPosMove[0]<-1.0f)
		PosMove[0]=moveZSpeed;

	if(GFXPosMove[0]>1.0f)
		PosMove[0]=-moveZSpeed;

	if(GFXPosMove[1]<-1.0f)
		PosMove[1]=-moveZSpeed;
	if(GFXPosMove[1]>1.0f)
		PosMove[1]=moveZSpeed;

	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_PRIOR] == TRUE)
	{
		PosMove[2]=moveZSpeed;
		moveZ=moveZ+moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_NEXT] == TRUE)
	{
		PosMove[2]=-moveZSpeed;
		moveZ=moveZ-moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['W'] == TRUE)
	{
		PosMove[1]=moveZSpeed;
		GoZ=GoZ+moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['S'] == TRUE)
	{
		PosMove[1]=-moveZSpeed;
		GoZ=GoZ-moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['A'] == TRUE)
	{
		PosMove[0]=moveZSpeed;
		GoX=GoX+moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['D'] == TRUE)
	{
		PosMove[0]=-moveZSpeed;
		GoX=GoX-moveZSpeed;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_UP] == TRUE)
	{
		PosTurn[1]=2.0f;
		moveY=moveY+2.0f;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_DOWN] == TRUE)
	{
		PosTurn[1]=-2.0f;
		moveY=moveY-2.0f;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_RIGHT] == TRUE)
	{
		PosTurn[0]=2.0f;
		moveX=moveX+2.0f;
	}
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_LEFT] == TRUE)
	{
		PosTurn[0]=-2.0f;
		moveX=moveX-2.0f;
	}
	if(NoTouchMoveTimes<=0.01f)
	{
		moveX=moveX-touchX*TouchMoveOverride;
		PosTurn[0]+=-touchX*7.0f;
		PosTurn[1]+=-touchY*3.0f;
	}
	if(Touchang!=Touchang) 
		Touchang=0.0f;
	if(TouchangY!=TouchangY)
		TouchangY=0.0f;
	if(zoomsize!=zoomsize) 
		zoomsize=0.0f;
	if(SceneSelect==-1)
		moveZ=moveZ-zoomsize*TouchZoomOverride*moveZSpeed*0.1f;
	else
		moveZ=moveZ-zoomsize*TouchZoomOverride*moveZSpeed*0.05f;
	if(Touchang>1000.0f) 
		Touchang=1000.0f;
	if(Touchang<-1000.0f) 
		Touchang=-1000.0f;
	if(TouchangY>1000.0f) 
		TouchangY=1000.0f;
	if(TouchangY<-1000.0f) 
		TouchangY=-1000.0f;
	PosMove[0]+=TouchMoveOverride*Touchang/500.0f*moveZSpeed/25.0f;
	PosMove[1]+=TouchMoveOverride*TouchangY/500.0f*moveZSpeed/25.0f;
	GoX=GoX+Touchang*0.01f;
	//LimitZ
	//if(moveZ<0.0f) moveZ=0.0f;
	//if(moveZ<-350.0f) moveZ=-350.0f;
	moveZ=max(moveZ,LimitZ[1]);
	moveZ=min(moveZ,LimitZ[0]);
	//TestNum=moveZ;
	Touchang=Touchang*0.90f;
	if(abs(Touchang)<0.0001f) Touchang=0.0f;
	TouchangY=TouchangY*0.90f;
	if(abs(TouchangY)<0.0001f) TouchangY=0.0f;
	zoomsize=zoomsize*0.90f;
	if(abs(zoomsize)<0.0001f) zoomsize=0.0f;
	touchX=touchX*0.75f;
	touchY=touchY*0.75f;
	if(abs(touchX)<0.0001f) touchX=0.0f;
	if(abs(touchY)<0.0001f) touchY=0.0f;
	NoTouchMoveTimes=max(0.0f,NoTouchMoveTimes-1.0f);
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_HOME] == TRUE)
	{
		PosMove[0]=0.0f;
		PosMove[1]=0.0f;
		PosTurn[0]=0.0f;
		PosTurn[1]=0.0f;
		ViewTGTUnit.UnitPos=ViewTGTPos;
		ViewUnit.UnitPos=ViewPos;
		moveZ=0.0f;
	}
	
	if(blurnumtmp1>1.0f)
	{
		PosMove[0]=0.0f;
		PosMove[1]=0.0f;
		PosTurn[0]=0.0f;
		PosTurn[1]=0.0f;
	}
}
void InitDataThread()
{
	ViewUnit.UnitPos=_mm_set_ps(1.0f,250.0f,250.0f,250.0f);
	Easy_matrix_identity(ViewMat);
	moveZ=2000.0f;
	moveX=0.0f;
	moveY=0.0f;
	SoundSysTest=new CSoundSys;
	int ListNum=0;
	ListNum=UnitsList.AddOneUnit();	
	UnitsList.UnitsList[ListNum]->UnitType=Cam;
	ThreadDataUpdata.Global_Data.Scene.CamID=ListNum;
	ListNum=UnitsList.AddOneUnit();
	UnitsList.UnitsList[ListNum]->UnitType=Fighter;
	UnitsList.UnitsList[ListNum]->Operator=Player;
	UnitsList.UnitsList[ListNum]->Life=100.0f;
	ThreadDataUpdata.Global_Data.Scene.PlayerID=ListNum;
	
	for(int i=0;i<30;i++)
	{
		int tmp=UnitsList.AddOneUnit();
		if((1%5)==0)
			ListNum=tmp;
		else
			UnitsList.UnitsList[tmp]->Leader_ID=ListNum;
		UnitsList.UnitsList[tmp]->Life=100.0f;
		UnitsList.UnitsList[tmp]->Operator=AI;
		UnitsList.UnitsList[tmp]->UnitType=Fighter;

	}
}
inline void LimitTurnUP()
{
	float Dlimit=min(1.0f,(ViewLen+moveZ-2000.0f)/1600.0f);
	//TestNum=ViewLen+moveZ;
	float TurnUP=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewMat[2]);
	if(SceneSelect>-1) Dlimit=0.0f;
	if(TurnUP<0.25f+Dlimit*0.499f)
	{
		//ViewUnit.RotInternal(min(0.0f,PosTurn[1]),1.0f,0.0f,0.0f);
		__m128 ViewUnitMATTMP1[4];
		ViewUnit.GetMatrix(ViewUnitMATTMP1);
		float TurnUPTMP2=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewUnitMATTMP1[2]);
		if(SceneSelect==-1)
		{
			while(TurnUPTMP2<(0.25f+Dlimit*0.499f))
			{
				ViewUnit.RotInternal(-0.001f,1.0f,0.0f,0.0f);
				ViewUnit.GetMatrix(ViewUnitMATTMP1);
				TurnUPTMP2=Easy_vector_dot(_mm_set_ps(1.0f,0.0f,1.0f,0.0f),ViewUnitMATTMP1[2]);
			}
		}
		return;
	}
	if(TurnUP>0.75f)
	{
		ViewUnit.RotInternal(max(0.0f,PosTurn[1]),1.0f,0.0f,0.0f);
		return;
	}
	ViewUnit.RotInternal(PosTurn[1],1.0f,0.0f,0.0f);
}
void DataUpdata()
{
	UpdataKeys();
	TotalFrame=TotalFrame+1;
	Test3dsFrame=Test3dsFrame+0.25f;
	if(abs(GFXPosMove[0])<9.5f)
	GFXPosMove[0]=GFXPosMove[0]*0.8f;
	if(abs(GFXPosMove[1])<9.5f)
	GFXPosMove[1]=GFXPosMove[1]*0.8f;
	angleR=angleR+0.2f;
	//TestView.Reset();
	//TestView.RotInternal(moveX,0.0f,1.0f,0.0f);
	//TestView.RotInternal(moveY,1.0f,0.0f,0.0f);
	//TestView.MovInternal(_mm_set_ps(1.0f,-25-moveZ-PosOrgZ+30,PosOrgY,0));
	//TestView.MovInternal(_mm_set_ps(1.0f,GoZ,0,GoX));
	//TestView.PosTo(IdentityMatrix3,180.0f);
	if(ThreadDataUpdata.DrawToData.ChangePos)
	{
		ViewPos=_mm_set_ps(1.0f,ThreadDataUpdata.DrawToData.ViewPos[2],ThreadDataUpdata.DrawToData.ViewPos[1],ThreadDataUpdata.DrawToData.ViewPos[0]);
		ViewTGTPos=_mm_set_ps(1.0f,ThreadDataUpdata.DrawToData.ViewTGTPos[2],ThreadDataUpdata.DrawToData.ViewTGTPos[1],ThreadDataUpdata.DrawToData.ViewTGTPos[0]);
		ViewLen=sqrt(Easy_vector_Getlenth_2(ViewPos,ViewTGTPos));
		ViewTGTUnit.UnitPos=ViewTGTPos;
		ViewUnit.UnitPos=ViewPos;
		ThreadDataUpdata.Global_Data.ChangePosOK=1;
		moveZ=0;
		LimitZ[0]=ThreadDataUpdata.DrawToData.LimitZ[0];
		LimitZ[1]=ThreadDataUpdata.DrawToData.LimitZ[1];
	}
	else
	{
		ThreadDataUpdata.Global_Data.ChangePosOK=0;
	}
	ViewUnit.PosTo(&ViewTGTUnit);
	ViewUnit.UnitPos=ViewTGTUnit.UnitPos;
	ViewUnit.RotExternal(PosTurn[0],0.0f,1.0f,0.0f);

	LimitTurnUP();

	ViewUnit.MovInternal(_mm_set_ps(1.0f,ViewLen+moveZ,0.0f,0.0f));
	CUnitMath ViewUnitTMP;
	ViewUnitTMP.UnitPos=ViewUnit.UnitPos;
	ViewUnitTMP.UnitPos.m128_f32[1]=0.0f;
	__m128 ViewTGTPosTMP=ViewTGTUnit.UnitPos;
	ViewTGTPosTMP.m128_f32[1]=0.0f;

	ViewUnitTMP.PosTo(ViewTGTPosTMP);
	ViewUnitTMP.MovInternal(_mm_set_ps(1.0f,-PosMove[1],0.0f,-PosMove[0]));
	__m128 TestPos1=ViewTGTUnit.UnitPos;//TestPos1.m128_f32[1]=0.0f;
	__m128 TestPos2=ViewTGTPos;//TestPos2.m128_f32[1]=0.0f;
	//if((LimitZ[0]+ViewLen)>sqrt(Easy_vector_Getlenth_2(ViewUnitTMP.UnitPos,ViewTGTPos)))
	float LimitFix=0.5f;
	if(LimitZ[0]>300) LimitFix=1.5f;
	if((LimitZ[0]+ViewLen)*LimitFix>sqrt(Easy_vector_Getlenth_2(TestPos1,TestPos2)))
	{
	ViewUnit.UnitPos.m128_f32[0]=ViewUnitTMP.UnitPos.m128_f32[0];
	ViewUnit.UnitPos.m128_f32[2]=ViewUnitTMP.UnitPos.m128_f32[2];
	ViewUnitTMP.UnitPos=ViewTGTPosTMP;
	ViewUnitTMP.MovInternal(_mm_set_ps(1.0f,-PosMove[1],0.0f,-PosMove[0]));
	ViewTGTUnit.UnitPos.m128_f32[0]=ViewUnitTMP.UnitPos.m128_f32[0];
	ViewTGTUnit.UnitPos.m128_f32[2]=ViewUnitTMP.UnitPos.m128_f32[2];
	}
	else
	{
		ViewTGTUnit.PosTo(ViewTGTPos);
		ViewTGTUnit.MovInternal(_mm_set_ps(1.0f,-ViewLen*0.002f*moveZSpeed,0.0f,0.0f));
	}
	ViewUnit.GetMatrix(ViewMat);
	//TestNum=sqrt(Easy_vector_Getlenth_2(TestPos1,TestPos2));
	GoZ=GoX=0.0f;
	//TestView.MovExternal(_mm_set_ps(1.0f,-25-moveZ-PosOrgZ,moveY+PosOrgY,moveX));
	//SceneUnitTest.SetPos(_mm_set_ps(1.0f,0.0f,0.0f,0.0f));
	SceneUnitTest.SetTGTPos(TestView.UnitPos);
	SceneUnitTest.Updata();
	//TestUnit.PosTo(TestView.UnitPos,1.25f);
	//TestView.PosTo(SceneUnitTest.UnitPos);
	CUnitMath UnitMathDraw;
	CUnitMath UnitMathDraw2;
	CUnitMath TestLight;
	UnitMathDraw.UnitPos=SceneUnitTest.UnitPos;
	UnitMathDraw.UnitQuat=SceneUnitTest.UnitQuat;
	UnitMathDraw.RotInternal(-90,1.0f,0.0f,0.0f);
	UnitMathDraw2.RotInternal(-90,1.0f,0.0f,0.0f);
	//UnitMathDraw2.RotExternal(moveX,0.0f,1.0f,0.0f);
	//UnitMathDraw2.RotExternal(moveY,1.0f,0.0f,0.0f);
	TestLight.Reset();
	TestLight.UnitPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	//TestLight.RotInternal(float((TotalFrame/3)%360),0.0f,1.0f,0.0f);
	TestLight.MovInternal(_mm_set_ps(1.0f,-100000.0f,150000.0f,100000.0f));
	
	//TestLight.UnitPos=_mm_set_ps(1.0f,0.0f,10000.0f,0.01f);

	ThreadDataUpdata.DataCount=6;
	ThreadDataUpdata.DataList[1].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[2].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[3].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[4].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[5].UnitData_States=_UnitData_States_Use;
	//TestView.GetMatrix(ThreadDataUpdata.DataList[1].Matrix);
	Easy_matrix_copy(ThreadDataUpdata.DataList[1].Matrix,ViewMat);
	UnitMathDraw.GetMatrix(ThreadDataUpdata.DataList[2].Matrix);
	SceneUnitTest.GetMatrix(ThreadDataUpdata.DataList[3].Matrix);
	UnitMathDraw2.GetMatrix(ThreadDataUpdata.DataList[4].Matrix);
	TestLight.GetMatrix(ThreadDataUpdata.DataList[5].Matrix);

	__m128 SoundPos;
	__m128 SoundMX[4];
	TestView.GetMatrix(SoundMX);
	Easy_matrix_inv(SoundMX,SoundMX);
	Easy_matrix_mult_vector3X3(&SoundPos,SoundMX,SceneUnitTest.UnitPos);
	SoundSysTest->SetTestPos(SoundPos.m128_f32[0]*0.01f,SoundPos.m128_f32[1]*0.01f,SoundPos.m128_f32[2]*0.01f);

	ThreadUpdataToExchange(&ThreadDataUpdata);

}