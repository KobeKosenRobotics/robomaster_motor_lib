#include <Arduino.h>
#include <RobomasterMotorHandler.h>
#include <RobomasterMotor.h>

using namespace robomaster_motor_lib;

RobomasterMotorHandler handler(&Can0);
RobomasterMotor motor(1);

void setup()
{
    Serial.begin(9600);
    handler.AddMotor(&motor);
}

void loop()
{
    handler.Update();

    motor.SetTargetCurrent(1.0);
    
    Serial.print("Raw Angle: ");
    Serial.println(motor.GetRawAngle());
    Serial.print("Incremental Angle: ");
    Serial.println(motor.GetIncrementalAngle());
    Serial.print("Velocity: ");
    Serial.println(motor.GetVelocity());
    Serial.print("Current: ");
    Serial.println(motor.GetCurrent());
}