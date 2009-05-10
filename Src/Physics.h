#ifndef _PHYSICS_H
#define _PHYSICS_H
#include "Mathematics.h"

class RigidBody{
private:
    Vector3d AngleAcceleration; //�Ǽ��ٶ�
public:
    Transform& State; //�˶�ѧ״̬
    Vector3d Velocity; //�ٶ�
    Vector3d Acceleration; //���ٶ�
    Vector3d GravityAcceleration; //�������ٶ�
    Vector3d AngleVelocity; //���ٶ�

    Vector3d get_AngleAcceleration() const { return AngleAcceleration; }
    void set_AngleAcceleration(Vector3d val) {
        Vector3d diff;
        diff = val - AngleAcceleration;
        if (norm2(diff) >= MaxAngleAccelerationAcceleration) {
            AngleAcceleration += MaxAngleAccelerationAcceleration * normalize(diff);
        }
        else {
            AngleAcceleration = val;
        }
    }

    double MaxSpeed; //����ٶ�
    double MaxAngleSpeed; //�����ٶ�
    double MaxAngleAcceleration; //���Ǽ��ٶ�
    double MaxAngleAccelerationAcceleration; //���ǼӼ��ٶ�
    double VelocityResistance; //�ٶ�˥��ϵ��[0,1]
    double AngleVelocityResistance; //���ٶ�˥��ϵ��[0,1]

    RigidBody(Transform& State, double MaxSpeed, double MaxAngleSpeed, double MaxAngleAcceleration, double MaxAngleAccelerationAcceleration, double VelocityResistance, double AngleVelocityResistance):State(State){
        Velocity = 0, 0, 0;
        Acceleration = 0, 0, 0;
        GravityAcceleration = 0, 0, 0;
        AngleVelocity = 0, 0, 0;
        AngleAcceleration = 0, 0, 0;
        assert(MaxSpeed >= 0);
        assert(MaxAngleSpeed >= 0);
        this->MaxSpeed = MaxSpeed;
        this->MaxAngleSpeed = MaxAngleSpeed;
        this->MaxAngleAcceleration = MaxAngleAcceleration;
        this->MaxAngleAccelerationAcceleration = MaxAngleAccelerationAcceleration;
        this->VelocityResistance = VelocityResistance;
        this->AngleVelocityResistance = AngleVelocityResistance;
    }

    void NextState(){
        State.Translate(Velocity);
        State.Rotate(AngleVelocity);
        Velocity += Acceleration + GravityAcceleration;
        if (norm2(Velocity) > MaxSpeed){ Velocity = MaxSpeed * normalize(Velocity); }
        if (VelocityResistance >= 1){
            Velocity = 0, 0, 0;
        }
        else{
            Velocity *= 1 - VelocityResistance;
        }

        if (norm2(AngleAcceleration) > MaxAngleAcceleration){ AngleAcceleration = MaxAngleAcceleration * normalize(AngleAcceleration); }
        AngleVelocity += AngleAcceleration;

        if (norm2(AngleVelocity) > MaxAngleSpeed){ AngleVelocity = MaxAngleSpeed * normalize(AngleVelocity); }

        if (AngleVelocityResistance >= 1){
            AngleVelocity = 0, 0, 0;
        }
        else{
            AngleVelocity *= 1.0 - AngleVelocityResistance;
        }
    }
};

#endif