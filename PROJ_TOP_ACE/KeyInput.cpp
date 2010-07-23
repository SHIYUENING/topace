#include "KeyInput.h"

tKeyInput KeyInput;
extern tKeyBoardSet KeyBoardSet;
void UpdataKeyInput(int* KeyBoardkeys)
{
	for(int i=0;i<MAX_JOY_KEYS;i++)
	{

		KeyInput.KeyVal[i]=float(KeyBoardkeys[KeyBoardSet.KeySet[i]]);
		if(KeyInput.KeyStats[i]<=-1)
		{
			KeyInput.KeyStats[i]=0;
			continue;
		}
		if(KeyInput.KeyVal[i]>0.1f)
			KeyInput.KeyStats[i]=1;
		else
			KeyInput.KeyStats[i]=-1;
		//if(KeyInput.KeyStats==1)
	}
}