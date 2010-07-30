#include "SceneUnit.h"

CSceneUnit::CSceneUnit(void)
: UnitType(0)
, ModelType(0)
, MoveSPD(0)
, TurnSPD(0)
, MoveSPD_R(0)
, TurnSPD_R(0)
, Life(0)
, Status(0)
, TurnSPD_Now(0)
, AIThinkTime(0)
, LilfTime(0)
{
}

CSceneUnit::~CSceneUnit(void)
{
}

void CSceneUnit::TurnTo(__m128 TGTPos)
{
	PosToDir(TGTPos);
	if((TurnX*TurnX)>0.001f)
		RotInternal(TurnSPD*TurnX,1.0f,0.0f,0.0f);
	if((TurnZ*TurnZ)>0.001f)
		RotInternal(TurnSPD*TurnZ,0.0f,0.0f,1.0f);
	TurnX=TurnX*(max(0.0f,1.0f-TurnSPD_R));
	TurnZ=TurnZ*(max(0.0f,1.0f-TurnSPD_R));
}
void CSceneUnit::TurnTo(float TGTPos[3])
{
	TurnTo(_mm_set_ps(1.0f,TGTPos[2],TGTPos[1],TGTPos[0]));
}
