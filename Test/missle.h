//#pragma once
#ifndef _MISSLE_H
#define _MISSLE_H
#include "Mathematics.h"
#include "Physics.h"
class Missledata
{
public:
	Transform UDMplane;//导弹矩阵
	RigidBody UDPstate;//导弹运动学状态

public:
	Missledata(void);
	~Missledata(void);
    void Missledata::TurnTo(const Vector3d& Position);

};
#endif