#ifndef ROBOMASTER_MOTOR_LIB_ROBOMASTER_MOTOR_H
#define ROBOMASTER_MOTOR_LIB_ROBOMASTER_MOTOR_H

#include <Arduino.h>

namespace robomaster_motor_lib
{
    class RobomasterMotor
    {
        public:
            RobomasterMotor();
            RobomasterMotor(int id);

            // ID
            inline int GetId(){ return _id; }

            /// @brief 
            /// @param target_current [A]
            inline void SetTargetCurrent(double target_current) { _target_current_bit = constrain(target_current * _current_coef, -16384, 16384); }
            inline int GetTargetCurrentBit() { return _target_current_bit; }

            void UpdateAngle(int angle_bit);

            /// @brief 
            /// @return [deg]
            inline double GetRawAngle() { return _angle_raw; }

            /// @brief 
            /// @return [deg] 
            inline double GetIncrementalAngle() { return _angle_incremental; }

            /// @brief 
            /// @return []
            inline int GetRoundCount() { return _round_count; }

            inline void UpdateVelocity(int velocity_bit) { _velocity = (double)velocity_bit * _velocity_coef * _reduction_ratio_inv; }
            
            /// @brief 
            /// @return [rad/s]
            inline double GetVelocity() { return _velocity; }

            inline void UpdateCurrent(int current_bit) { _current = (double)current_bit * _current_coef_inv; }
            
            /// @brief 
            /// @return [A]
            inline double GetCurrent() { return _current; }

            inline void UpdateTemperature(int temperature_bit) { _temperature = temperature_bit; }
            
            /// @brief 
            /// @return degree celsius
            inline int GetTemperature() { return _temperature; }

        private:
            int _id;

            const double _reduction_ratio = 19.20; // = 3591 / 187
            const double _reduction_ratio_inv = 0.05207; // = 187 / 3591

            // Target Current
            int _target_current_bit;
            const double _current_coef = 819.2;  // = 16384 / 20[A]

            // Angle
            double _angle_raw;
            double _angle_incremental;
            int _round_count;
            int _angle_bit_last;
            const double _angle_coef = 0.04395; // 360[deg] / 8192

            // Velocity
            double _velocity;
            const double _velocity_coef = 0.1047; // = 2π / 60

            // Current
            double _current;
            const double _current_coef_inv = 0.001221; // 20[A] / 16384

            // Temperature
            int _temperature;

    }; // class RobomasterMotor

}; // robomaster_motor_lib

#endif