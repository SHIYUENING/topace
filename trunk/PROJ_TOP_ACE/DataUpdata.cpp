﻿#include "DataUpdata.h"
#include "KeyInput.h"
#include "UnitMath.h"
float angleR=0.0f;
float Test3dsFrame=0.0f;
float maxFreme=100.0f;
bool Test3dsFrameSwitch=false;
extern tKeyInput KeyInput;
CUnitMath TestUnit,TestView;
CUnitMath TestUnitExchange;
int ReadingThreadNum=0;
float extern moveZ;
float extern moveY;
float extern moveX;
float extern PosOrgY;
float extern PosOrgZ;
extern _UnitData UnitDatas[100];
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
	TestUnit.PosTo(TestView.UnitPos,1.25f);
	TestView.PosTo(_mm_set_ps(1.0f,0.0f,0.0f,0.0f));
	CUnitMath UnitMathDraw;
	UnitMathDraw.UnitPos=TestUnit.UnitPos;
	UnitMathDraw.UnitQuat=TestUnit.UnitQuat;
	UnitMathDraw.RotExternal(-90,1.0f,0.0f,0.0f);
	int ReadingThreadWait=0;
	while(ReadingThreadNum==1)
	{
		ReadingThreadWait++;
	}
	ReadingThreadNum=2;
	TestView.GetMatrix(UnitDatas[0].UnitMatrix);
	UnitMathDraw.GetMatrix(UnitDatas[1].UnitMatrix);
	ReadingThreadNum=0;
}