#pragma once
#include "structs.h"
#include "testNum.h"
int locknum=1;//同时最大锁定数
int lockflagnum=0;//锁定优先级
bool locksound=false;
bool lockonsound=false;

Vector2d GetNextLockCellPosition(const Vector2d& target, const Vector2d& current, double maxSpeed){
    Vector2d d;
    d = target - current;
    double l = norm2(d);
    if (l <= maxSpeed){ return target; }
    if (l == 0.0f) { return current; }
    return Vector2d(current + normalize(d) * maxSpeed);
}
void initlocks()
{
	for(int i=0;i<locknum;i++)
	{
		lockUnits[i].lockON=false;
		lockUnits[i].locksTGT=0;
		lockUnits[i].locksX=winwidth*0.5f;
		lockUnits[i].locksY=winheight*0.5f;
	}
}
void fireMissle()
{
	for(int i=0;i<locknum;i++)
	{
		if(lockUnits[i].lockON)
		{
			if((lockUnits[i].locksTGT>-1)&&(lockUnits[i].locksTGT<maxUnits))
			{
				//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, &channel2);
				Playfox2voice(rand()%3);
				//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, fox2voice[rand()%3], 0, &fox2voicechannel);
/*
				UDfighers[lockUnits[i].locksTGT].attackedMissleNum=missle_index;
				missle[missle_index].TGTnum=lockUnits[i].locksTGT;
				missle[missle_index].UDlife=600;
				missle[missle_index].UDMplane=MFighter;
				missle[missle_index].UDMplane.TranslateInternal(Vector3d(0.0f, -75.0f, -300.0f));
				
				missle[missle_index].UDMplane.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * CRad(180.0));

					//MFighter.TranslateInternal(Vector3d(0.0f, 0.0f, -moveSpeed * 600));
				missle_index=missle_index+1;
				if(missle_index==maxMissles)
					missle_index=0;
*/
				if((lockUnits[i].locksTGT<0)||(lockUnits[i].locksTGT>=maxUnits))
				{
					char WaringString[64]={0};
					sprintf(WaringString,"locksTGT in fireMissle() more than %d",maxUnits);
					::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
					return;
				}
				UDfighers[lockUnits[i].locksTGT].attackedMissleNum=PMissleList.AddMissle(UDfighers[0].UDMplane,lockUnits[i].locksTGT,0,70.0f);
			}
			
		}
	}
}
void selectLockTGT()
{
	
	for(int i=1;i<maxUnits;i++)
	{
		UDfighers[i].UDlockselect=false;
	}
	if(locklists_index==0)
		lockflagnum=0;
	else
	{
		if(!(locknum<locklists_index))//如果可锁定数大于等于可锁定目标数
		{
			for(int i=0;i<locklists_index;i++)//循环可锁定目标表
			{
				UDfighers[locklists[i].TGTnum].UDlockselect=true;//可锁定目标表中的目标被标记为锁定
				lockUnits[i].locksTGT=locklists[i].TGTnum;
			}
		
		}
		else
		{
			//for(int j=lockflagnum*locknum;j<locklists_index;j=j+locknum)
			//{
				for(int i=0;i<locknum;i++)
				{
					if(!((i+lockflagnum)<locklists_index))
					{
						UDfighers[locklists[i+lockflagnum-locklists_index].TGTnum].UDlockselect=true;//可锁定目标表中的目标被标记为锁定
						lockUnits[i].locksTGT=locklists[i+lockflagnum-locklists_index].TGTnum;
					}
					else
					{
						UDfighers[locklists[i+lockflagnum].TGTnum].UDlockselect=true;//可锁定目标表中的目标被标记为锁定
						lockUnits[i].locksTGT=locklists[i+lockflagnum].TGTnum;
					}
				}
			//}
			lockflagnum=lockflagnum+locknum;
			if(!((lockflagnum)<locklists_index))
				lockflagnum=lockflagnum-locklists_index;
		}
	}
	
	
	

}
void locksmove()
{

	Vector2d vlock;
	for(int i=0;i<locknum;i++)
	{
		if(lockUnits[i].locksTGT>0)
		{
			if(lockUnits[i].locksTGT>maxUnits)
			{
				char WaringString[64]={0};
				sprintf(WaringString,"locksTGT.in locksmove more than %d",maxUnits);
				::MessageBox(HWND_DESKTOP,WaringString,"Error",MB_OK | MB_ICONEXCLAMATION);
			}
			//if(lockUnits[i].locksTGT)
			double targetx=UDfighers[ lockUnits[i].locksTGT ].UDwinx;
			double targety=UDfighers[ lockUnits[i].locksTGT ].UDwiny;
			

			double currentx=lockUnits[i].locksX;
			double currenty=lockUnits[i].locksY ;

			double LMl=(targetx-currentx)*(targetx-currentx)+(targety-currenty)*(targety-currenty);
			if((UDfighers[ lockUnits[i].locksTGT ].UDwinz<1.0)&&(UDfighers[ lockUnits[i].locksTGT ].UDwinl<(tmplockRenge*tmplockRenge))&&(targetx>0.0f)&&(targetx<winwidth)&&(targety>0.0f)&&(targety<winheight)&&UDfighers[ lockUnits[i].locksTGT ].UDlife>0)
			{
				if((LMl>winwidth*0.5)&&(!lockUnits[i].lockON))
				{
					if(!locksound)
					{
						//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, soundLock, 0, &channelLock);
						locksound=true;
					}
					if(lockonsound)
					{
//						FMOD_Channel_Stop(channelLockOn);
						lockonsound=false;
					}


					Vector2d vtarget( targetx , targety );
					Vector2d vcurrent( currentx , currenty );

					//vlock = GetNextLockCellPosition ( Vector2d ( lockUnits[i].locksX , lockUnits[i].locksY ) , Vector2d( UDfighers[ lockUnits[i].locksTGT ].UDwinx , UDfighers[ lockUnits[i].locksTGT ].UDwiny ) , winwidth*0.1);
					vlock = GetNextLockCellPosition (vtarget,vcurrent,winwidth*0.005);
					lockUnits[i].locksX=(float)vlock(0);
					lockUnits[i].locksY=(float)vlock(1);
					
				}
				else
				{
					if(!lockonsound)
					{
						//FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, soundLockOn, 0, &channelLockOn);
						lockonsound=true;
					}

					if(locksound)
					{
						//FMOD_Channel_Stop(channelLock);
						locksound=false;
					}

					lockUnits[i].lockON=true;
					UDfighers[ lockUnits[i].locksTGT ].UDlockde=true;
					lockUnits[i].locksX=(float)targetx;
					lockUnits[i].locksY=(float)targety;
					/*
					if((targetx<0.0f)||(targetx>winwidth)||(targety<0.0f)||(targety>winheight))
					{
						lockUnits[i].lockON=false;
						UDfighers[ lockUnits[i].locksTGT ].UDlockde=false;
						lockUnits[i].locksX=winwidth*0.5;
						lockUnits[i].locksY=winheight*0.5;
						
					}*/
						

				}
				glPrintW(lockUnits[i].locksX,lockUnits[i].locksY,true);
			}
			else
			{
				if(locksound)
				{
//					FMOD_Channel_Stop(channelLock);
					locksound=false;
				}

				if(lockonsound)
				{
//					FMOD_Channel_Stop(channelLockOn);
					lockonsound=false;
				}


				lockUnits[i].locksX=winwidth*0.5f;
				lockUnits[i].locksY=winheight*0.5f;
				lockUnits[i].lockON=false;
				UDfighers[ lockUnits[i].locksTGT ].UDlockde=false;
				if(!(UDfighers[ lockUnits[i].locksTGT ].UDwinl<(tmpredarRenge*tmpredarRenge))||(UDfighers[ lockUnits[i].locksTGT ].UDlife<1))
				{
					
					UDfighers[ lockUnits[i].locksTGT ].UDlockselect=false;
					lockUnits[i].locksTGT=0;
				}
			}
			
		}
	}
}

