#include <RobomasterMotorHandler.h>

namespace robomaster_motor_lib
{

    RobomasterMotorHandler::RobomasterMotorHandler()
    {

    }

    RobomasterMotorHandler::RobomasterMotorHandler(FlexCAN* can)
    {
        _can = can;
    }

    void RobomasterMotorHandler::AddMotor(RobomasterMotor* motor)
    {
        int id = motor->GetId();
        if(id < 1 || id > 8) return;
        _motors[id - 1] = motor;
    }

    void RobomasterMotorHandler::Update()
    {
        Read();
        delay(10);
        Write(0);
        Write(1);
    }

    void RobomasterMotorHandler::Read()
    {
        while (_can->available())
        {
            CAN_message_t msg;
            _can->read(msg);
            RobomasterMotor* motor = _motors[msg.id - 0x201];
            if(motor == nullptr) continue;
            motor->UpdateAngle((msg.buf[1] | msg.buf[0] << 8));
            motor->UpdateVelocity(((int16_t)(msg.buf[2] << 8) + msg.buf[3]));
            motor->UpdateCurrent(((int16_t)(msg.buf[4] << 8) + msg.buf[5]));
            motor->UpdateTemperature(msg.buf[6]);
        }
    }

    void RobomasterMotorHandler::Write(bool part)
    {
        CAN_message_t msg;
        msg.ext = 0;
        msg.len = 8;

        msg.id = part ? 0x1ff : 0x200;
        int offset = part ? 4 : 0;

        bool pub_check = false;
        for(int i = 0; i < 4; i++)
        {
            RobomasterMotor* motor = _motors[offset + i];
            if(motor == nullptr) continue;
            delay(1);
            int data = motor->GetTargetCurrentBit();
            msg.buf[i*2] = highByte(data);
            msg.buf[i*2 + 1] = lowByte(data);
            pub_check = true;
        }
        if(!pub_check) return;
        _can->write(msg);
    }

}; // namespace robomaster_motor_lib