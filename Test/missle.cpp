#include "missle.h"
Missledata::Missledata(void)
: UDPstate(UDMplane, 6, CRad(2.5), 0.1, 0.4)
{
}

Missledata::~Missledata(void)
{
}

void Missledata::TurnTo(const Vector3d& Position){
	Vector3d current;
    current = UDMplane.Matrix() * Vector3d(0, 0, 1);
    if (!all_elements(current == 0)){
        current = normalize(current);
    }

    Vector3d target;
    target = Position - UDMplane.RefPos();
    if (!all_elements(target == 0)){
        target = normalize(target);
    }

    double k = dot(current, target);

    Vector3d rotateAxis;
    rotateAxis = cross(current, target);
    if (!all_elements(rotateAxis == 0)){
        rotateAxis = normalize(rotateAxis);
    }

    double rotateAngle = acos_s(dot(current, target));

    UDPstate.State.Rotate(rotateAxis * rotateAngle - UDPstate.AngleVelocity);
	//UDPstate.Acceleration = UDMplane.Matrix() * Vector3d(0, 0, 1) * 35;
	
}

