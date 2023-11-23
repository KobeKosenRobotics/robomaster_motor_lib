#include <RobomasterMotor.h>

namespace robomaster_motor_lib
{

    RobomasterMotor::RobomasterMotor()
    {   
        _id = -1;
        _round_count = 0;
        _angle_bit_last = -1;
    }

    RobomasterMotor::RobomasterMotor(int id)
    {
        _id = id;
        _round_count = 0;
        _angle_bit_last = -1;
    }

    void RobomasterMotor::UpdateAngle(int angle_bit)
    {
        _angle_raw = (double)angle_bit * _angle_coef;
        if(_angle_bit_last < 0)
        {
            _angle_incremental = 0;
            _angle_bit_last = angle_bit;
            return;
        }

        int angle_bit_diff = angle_bit - _angle_bit_last;
        int round_diff = (angle_bit_diff < -4096) - (angle_bit_diff > 4096);
        _round_count += round_diff;
        _angle_incremental = 360 * _round_count * _reduction_ratio_inv + _angle_raw * _reduction_ratio_inv;

        _angle_bit_last = angle_bit;
    }

}; // namespace robomaster_motor_lib