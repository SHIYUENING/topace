#ifdef _WIN32
#include "JoyStick.h"
#endif
#include "GamePads.h"

tJoyStictKeyVal JoyStictKeyVal;
extern tJoyStictSet JoyStictSet;
float KeyValSpace(LONG KeyVal)
{
	if(KeyVal>100)
		return float(KeyVal-100)/900.0f;
	if(KeyVal<-100)
		return float(KeyVal+100)/900.0f;
	return 0.0f;
}
float GetKeyVal(int KeySetNum,DIJOYSTATE2 js)
{

		
	int KeyType=KeySetNum%10;
	int KeyNum=KeySetNum/10;
	
	float KeyVal=0.0f;
	if(KeyType==1)
	{
		if((KeyNum<0)||(KeyNum>=128))
			return 0.0f;
		if( js.rgbButtons[KeyNum] & 0x80 )
			return 1.0f;
	}
	if(KeyType==2)
	{
		if(KeyNum==0)
		{
			return max(KeyValSpace(js.lX),0.0f);
		}
		if(KeyNum==1)
		{
			return min(KeyValSpace(js.lX),0.0f);
		}
		if(KeyNum==2)
		{
			return max(KeyValSpace(js.lY),0.0f);
		}
		if(KeyNum==3)
		{
			return min(KeyValSpace(js.lY),0.0f);
		}
		if(KeyNum==4)
		{
			return max(KeyValSpace(js.lZ),0.0f);
		}
		if(KeyNum==5)
		{
			return min(KeyValSpace(js.lZ),0.0f);
		}
		if(KeyNum==6)
		{
			return max(KeyValSpace(js.lRx),0.0f);
		}
		if(KeyNum==7)
		{
			return min(KeyValSpace(js.lRx),0.0f);
		}
		if(KeyNum==8)
		{
			return max(KeyValSpace(js.lRy),0.0f);
		}
		if(KeyNum==9)
		{
			return min(KeyValSpace(js.lRy),0.0f);
		}
		if(KeyNum==10)
		{
			return max(KeyValSpace(js.lRz),0.0f);
		}
		if(KeyNum==11)
		{
			return min(KeyValSpace(js.lRz),0.0f);
		}
	}
	if(KeyType==3)
	{
		if(KeyNum==js.rgdwPOV[0])
			return 1.0f;
		if(KeyNum==(js.rgdwPOV[0]+4500))
			return 1.0f;
		if(KeyNum==(js.rgdwPOV[0]-4500))
			return 1.0f;
		if(KeyNum==(js.rgdwPOV[0]-4500+36000))
			return 1.0f;

	}

	return 0.0f;
}
bool JoyStictUpdeta(int shockX,int shockY)
{
	SetDeviceForcesXY(int(JoyStictKeyVal.KeyVal[14])*5000,shockY);
	DIJOYSTATE2 js;
	if(FAILED(UpdateInputState(&js)))
		return false;

	for(int i=0;i<MAX_JOY_KEYS;i++)
		JoyStictKeyVal.KeyVal[i]=GetKeyVal(JoyStictSet.KeySet[i],js);

	return true;
}

bool InitJoyStict(void * MainhDlg)
{
	return SUCCEEDED(InitDirectInput( *(HWND *)MainhDlg ));
}
void FreeJoyStict()
{
	FreeDirectInput();
}
