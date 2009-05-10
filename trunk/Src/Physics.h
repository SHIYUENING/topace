#ifndef _PHYSICS_H
#define _PHYSICS_H
#include "Mathematics.h"

class RigidBody{
private:
    Vector3d AngleAcceleration; //角加速度
public:
    Transform& State; //运动学状态
    Vector3d Velocity; //速度
    Vector3d Acceleration; //加速度
    Vector3d GravityAcceleration; //重力加速度
    Vector3d AngleVelocity; //角速度

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

    double MaxSpeed; //最大速度
    double MaxAngleSpeed; //最大角速度
    double MaxAngleAcceleration; //最大角加速度
    double MaxAngleAccelerationAcceleration; //最大角加加速度
    double VelocityResistance; //速度衰减系数[0,1]
    double AngleVelocityResistance; //角速度衰减系数[0,1]

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