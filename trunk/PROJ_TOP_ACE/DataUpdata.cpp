#include "DataUpdata.h"
float angleR=0.0f;
float Test3dsFrame=0.0f;
bool Test3dsFrameSwitch=false;
void DataUpdata()
{
	if(Test3dsFrameSwitch)
	{
		Test3dsFrame=Test3dsFrame+0.3f;
		if(Test3dsFrame>=100.0f)
		{
			Test3dsFrame=100.0f;
			Test3dsFrameSwitch=false;
		}
	}
	else
	{
		Test3dsFrame=Test3dsFrame-0.5f;
		if(Test3dsFrame<=0.0f)
		{
			Test3dsFrame=0.0f;
			Test3dsFrameSwitch=true;
		}
	}
	angleR=angleR+0.2f;
}