//#pragma once
#ifndef _SCENEUNIT_H
#define _SCENEUNIT_H
#include "unitmath.h"

typedef enum _UnitType{
	DummyUnit=0,
	Cam=1,
	Fighter=2,
	Missle=3,
	Shell=4,
	Smoke=5
}_UnitType;

typedef enum _ACT_Orders{
	StandBy=0,
	FollowTo=1,
	AttackTo=2,
	Avoid=3
}_ACT_Orders;

typedef enum _ACT_Modes{
	CounterAttack=0,
	OnlyTravel=1,
	OnlyAvoid=2
}_ACT_Modes;

typedef enum _Operator{
	No_Operator=0,
	Player=1,
	AI=2
}_Operator;
class CSceneUnit :
	public CUnitMath
{
public:
	CSceneUnit(void);
	~CSceneUnit(void);
	_UnitType UnitType;
	unsigned int ModelType;
	// Move Speed
	float MoveSPD;
	// Turn Speed
	float TurnSPD;
	// Move Speed Resistance
	float MoveSPD_R;
	// Turn Speed Resistance
	float TurnSPD_R;
	float Life;
	unsigned int Status;
	float TurnSPD_Now;
	void SetTGTPos(__m128 TGTPos);
	void SetTGTPos(float TGTPos[3]);
	// AT Think Time
	float AIThinkTime;
	float LilfTime;
	void Updata(void);
	__m128 TGT_Pos;
	unsigned int TGT_ID;
	unsigned int Leader_ID;
	unsigned int ReAttackTGT_ID;
	_ACT_Orders ACT_Order;
	_ACT_Modes ACT_Modes;
	_Operator Operator;
	unsigned int Group;
	unsigned int FollowTGT_ID;

};
#endif