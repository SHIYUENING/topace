#include "DataUpdata.h"
#include "KeyInput.h"
#include "ExchangeThread.h"
#include "UnitsList.h"
#include "SoundSys.h"
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
void UpdataKeys()
{
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_PRIOR] == TRUE)
		moveZ=moveZ+moveZSpeed;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_NEXT] == TRUE)
		moveZ=moveZ-moveZSpeed;

	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['W'] == TRUE)
		GoZ=GoZ+moveZSpeed;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['S'] == TRUE)
		GoZ=GoZ-moveZSpeed;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['A'] == TRUE)
		GoX=GoX+moveZSpeed;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now['D'] == TRUE)
		GoX=GoX-moveZSpeed;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_UP] == TRUE)
		moveY=moveY+2.0f;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_DOWN] == TRUE)
		moveY=moveY-2.0f;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_RIGHT] == TRUE)
		moveX=moveX+2.0f;
	if(ThreadDataUpdata.DrawToData.Global_Data_Key.keyDown_Now[VK_LEFT] == TRUE)
		moveX=moveX-2.0f;
}
void InitDataThread()
{
	moveZ=-130.0f;
	moveX=45.0f;
	moveY=-45.0f;
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
void DataUpdata()
{
	UpdataKeys();
	TotalFrame=TotalFrame+1;
	if(Test3dsFrameSwitch)
	{
		Test3dsFrame=Test3dsFrame+0.5f;
		if(Test3dsFrame>=maxFreme)
		{
			//Test3dsFrame=0.0f;
			Test3dsFrameSwitch=false;
		}
	}
	else
	{
		Test3dsFrame=Test3dsFrame-0.5f;
		if(Test3dsFrame<=0.0f)
		{
			//Test3dsFrame=0.0f;
			Test3dsFrameSwitch=true;
		}
	}
	angleR=angleR+0.2f;

	TestView.Reset();
	TestView.RotInternal(moveX,0.0f,1.0f,0.0f);
	TestView.RotInternal(moveY,1.0f,0.0f,0.0f);
	TestView.MovInternal(_mm_set_ps(1.0f,-25-moveZ-PosOrgZ+30,PosOrgY,0));
	TestView.MovInternal(_mm_set_ps(1.0f,GoZ,0,GoX));
	//GoZ=GoX=0.0f;
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
	TestLight.UnitPos=_mm_set_ps(1.0f,0.0f,0.0f,0.0f);
	TestLight.RotInternal(float(TotalFrame%360),0.0f,1.0f,0.0f);
	TestLight.MovInternal(_mm_set_ps(1.0f,0.01f,10000.0f,10000.0f));
	
	//TestLight.UnitPos=_mm_set_ps(1.0f,0.0f,10000.0f,0.01f);

	ThreadDataUpdata.DataCount=6;
	ThreadDataUpdata.DataList[1].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[2].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[3].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[4].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[5].UnitData_States=_UnitData_States_Use;
	TestView.GetMatrix(ThreadDataUpdata.DataList[1].Matrix);
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