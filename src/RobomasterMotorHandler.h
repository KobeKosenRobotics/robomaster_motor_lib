#ifndef ROBOMASTER_MOTOR_LIB_ROBOMASTER_MOTOR_HANDLER_H
#define ROBOMASTER_MOTOR_LIB_ROBOMASTER_MOTOR_HANDLER_H

#include <FlexCAN.h>
#include <RobomasterMotor.h>

namespace robomaster_motor_lib
{
    class RobomasterMotorHandler
    {
        public:
            RobomasterMotorHandler();
            RobomasterMotorHandler(FlexCAN* can);
            void AddMotor(RobomasterMotor* motor);
            void Update();
        
        private:
            void Read();
            void Write(bool part);

            FlexCAN* _can;
            RobomasterMotor* _motors[8];

    }; // class RobomasterMotorHandler

}; // namespace robomaster_motor_lib

#endif