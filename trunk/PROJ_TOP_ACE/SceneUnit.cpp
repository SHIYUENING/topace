#include "SceneUnit.h"

CSceneUnit::CSceneUnit(void)
: UnitType(0)
, ModelType(0)
, MoveSPD(0)
, TurnSPD(0.5f)
, MoveSPD_R(0)
, TurnSPD_R(0.05f)
, Life(0)
, Status(0)
, TurnSPD_Now(0)
, AIThinkTime(10)
, LilfTime(0)
, TGT_Pos(_mm_set_ps(1.0f,0.0f,0.0f,0.0f))
{
}

CSceneUnit::~CSceneUnit(void)
{
}

void CSceneUnit::SetTGTPos(__m128 TGTPos)
{
	TGT_Pos=TGTPos;
}
void CSceneUnit::SetTGTPos(float TGTPos[3])
{
	SetTGTPos(_mm_set_ps(1.0f,TGTPos[2],TGTPos[1],TGTPos[0]));
}

void CSceneUnit::Updata(void)
{
	if((int(LilfTime)%max(1,int(AIThinkTime)))==0)
		PosToDir(TGT_Pos);
	if((TurnZ*TurnZ)>0.001f) RotInternal(TurnSPD*TurnZ,0.0f,0.0f,1.0f);
	if((TurnX*TurnX)>0.001f) RotInternal(TurnSPD*TurnX,1.0f,0.0f,0.0f);
	if((TurnY*TurnY)>0.001f) RotInternal(TurnSPD*TurnY,0.0f,1.0f,0.0f);
	if(NoTurn)
	{
		TurnX=TurnX*(max(0.0f,1.0f-TurnSPD_R));
		TurnY=TurnY*(max(0.0f,1.0f-TurnSPD_R));
		TurnZ=TurnZ*(max(0.0f,1.0f-TurnSPD_R));
	}
	if((MoveSPD*MoveSPD)>0.0000001f)
		MovInternal(_mm_set_ps(1.0f,-MoveSPD,0.0f,0.0f));
	MoveSPD=max(0.0f,MoveSPD-MoveSPD_R);
	LilfTime=LilfTime+1.0f;
}
