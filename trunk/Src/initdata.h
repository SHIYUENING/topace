#pragma once
#include "structs.h"



void initUnitdata(int stage=0 )
{

	//Msky.Translate(Vector3d(0.0f, 500.0f, 0.0f));
	weapon[0].ATK=50;
	weapon[0].cannotLockType=0;
	weapon[0].damRenge=100;
	weapon[0].fireNum=4;
	weapon[0].fireTime=30;
	weapon[0].flyTime=240;
	weapon[0].lockrenge=10000;
	weapon[0].maxlock=4;
	sprintf(weapon[0].name,"testMissle");
	weapon[0].reloadTime=240;
	weapon[0].roll=5;
	weapon[0].SPEED=50;
	weapon[0].type=2;

	for(int i=0;i<MAXMISSLE;i++)
	{
		PMissleList.Missles[i].UDlife=0;
	}
	for(int i=0;i<MAXSHELLSLIST;i++)
		Shell.ShellList[i].life=0;
	

	for(int i=0;i<maxUnits;i++)
	{
		UDfighers[i].UDlife=-1;

		UDfighers[i].weapon[0]=0;
	}
	if(stage==0)
	{
		moveSpeed=0.01f;
		UDfighers[0].UDMplane.Reset();
		UDfighers[0].UDMplane.Translate(Vector3d(0.0f, 40000.0f, 0.0f));
		UDfighers[0].UDlife=100;
		UDfighers[0].UDflag=2;
		/*
		UDfighers[0].UDlife=100;
		UDfighers[0].UDflag=2;

		UDfighers[1].UDfighterType=1;
		//UDfighers[1].UDlife=100;
		UDfighers[1].UDflag=0;
		sprintf(UDfighers[1].UDname,"YC15");
		UDfighers[1].UDlockselect=false;
		UDfighers[1].UDMplane.Translate(Vector3d(0.0f, 50200.0f, -2000.0f));

		UDfighers[2].UDfighterType=2;
		//UDfighers[2].UDlife=100;
		UDfighers[2].UDflag=1;
		sprintf(UDfighers[2].UDname,"Neo1");
		UDfighers[2].UDlockselect=false;
		UDfighers[2].UDMplane.Translate(Vector3d(1000.0f, 50500.0f, -1000.0f));

		UDfighers[3].UDfighterType=2;
		//UDfighers[3].UDlife=100;
		UDfighers[3].UDflag=1;
		sprintf(UDfighers[3].UDname,"Neo1");
		UDfighers[3].UDlockselect=false;
		UDfighers[3].UDMplane.Translate(Vector3d(300.0f, 50100.0f, -2000.0f));
		*/
		for(int i=1;i<maxUnits;i++)
		{
			UDfighers[i].ResetData();
			UDfighers[i].UDMplane.Reset();
			UDfighers[i].UDfighterType=2;
			UDfighers[i].UDlife=99;
			if(i>=5)
				UDfighers[i].UDflag=1;
			else
				UDfighers[i].UDflag=2;
			if(UDfighers[i].UDflag==2)
			{
				sprintf(UDfighers[i].UDname,"Mave");
			}
			else
			{
				sprintf(UDfighers[i].UDname,"Neo1");
			}
			UDfighers[i].UDlockselect=false;
			UDfighers[i].UDMplane.Translate(Vector3d(500.0f*(i-maxUnits/2), 35000.0f+5000.0f*(i%4), 2000.0f*(i%20-10)));
			UDfighers[i].MoveToPos=Vector3d(500.0f*(i-maxUnits/2), 35000.0f+5000.0f*(i%4), 2000.0f*(i%20-10));
			UDfighers[i].UDMplane.RotateInternal(Vector3d(0.0f, 1.0f, 0.0f) * (i%8+2));
			if(UDfighers[i].UDflag==2)
			{
				UDfighers[i].UDfighterType=3;
				UDfighers[i].LockOnTime=1;
				UDfighers[i].RefireTime=450;
				UDfighers[i].UDPstate.MaxAngleSpeed=CRad(2.0);
				UDfighers[i].UDPstate.MaxSpeed=8.0;
			}
		}

	}

}


