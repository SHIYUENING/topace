#include "DataUpdata.h"
#include "KeyInput.h"
#include "ExchangeThread.h"
#include "UnitsList.h"
float angleR=0.0f;
float Test3dsFrame=0.0f;
float maxFreme=100.0f;
bool Test3dsFrameSwitch=false;
extern tKeyInput KeyInput;
CUnitMath TestView;//TestUnit,
CUnitMath TestUnitExchange;
int ReadingThreadNum=0;
float extern moveZ;
float extern moveY;
float extern moveX;
float extern PosOrgY;
float extern PosOrgZ;
CExchangeThread ThreadDataUpdata;
CSceneUnit SceneUnitTest;
CUnitsList UnitsList;
void InitDataThread()
{
	int ListNum=0;
	ListNum=UnitsList.AddOneUnit();	
	UnitsList.UnitsList[ListNum]->UnitType=Cam;
	ThreadDataUpdata.Global_Data.Scene.CamID=ListNum;
	ListNum=UnitsList.AddOneUnit();
	UnitsList.UnitsList[ListNum]->UnitType=Fighter;
	UnitsList.UnitsList[ListNum]->Operator=Player;
	ThreadDataUpdata.Global_Data.Scene.PlayerID=ListNum;
}
void DataUpdata()
{
	if(Test3dsFrameSwitch)
	{
		Test3dsFrame=Test3dsFrame+0.5f;
		if(Test3dsFrame>=maxFreme)
		{
			Test3dsFrame=0.0f;
			//Test3dsFrameSwitch=false;
		}
	}
	else
	{
		Test3dsFrame=Test3dsFrame-1.0f;
		if(Test3dsFrame<=0.0f)
		{
			Test3dsFrame=0.0f;
			Test3dsFrameSwitch=true;
		}
	}
	angleR=angleR+0.2f;

	TestView.Reset();
	TestView.MovExternal(_mm_set_ps(1.0f,-25-moveZ-PosOrgZ,moveY+PosOrgY,moveX));
	//SceneUnitTest.SetPos(_mm_set_ps(1.0f,0.0f,0.0f,0.0f));
	SceneUnitTest.SetTGTPos(TestView.UnitPos);
	SceneUnitTest.Updata();
	//TestUnit.PosTo(TestView.UnitPos,1.25f);
	TestView.PosTo(SceneUnitTest.UnitPos);
	CUnitMath UnitMathDraw;
	UnitMathDraw.UnitPos=SceneUnitTest.UnitPos;
	UnitMathDraw.UnitQuat=SceneUnitTest.UnitQuat;
	UnitMathDraw.RotInternal(-90,1.0f,0.0f,0.0f);

	ThreadDataUpdata.DataCount=4;
	ThreadDataUpdata.DataList[1].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[2].UnitData_States=_UnitData_States_Use;
	ThreadDataUpdata.DataList[3].UnitData_States=_UnitData_States_Use;
	TestView.GetMatrix(ThreadDataUpdata.DataList[1].Matrix);
	UnitMathDraw.GetMatrix(ThreadDataUpdata.DataList[2].Matrix);
	SceneUnitTest.GetMatrix(ThreadDataUpdata.DataList[3].Matrix);

	ThreadUpdataToExchange(&ThreadDataUpdata);

}