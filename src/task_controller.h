#include <Arduino.h>
#include <cmath>

class Controller
{
    protected:
        float velocity;
        float angle;
        float angle_acceleration;
        float M_w;
        float F_w;
        float r_CG;
        float J_RW;
        float r_RW;
        float M_RW;
        float J_c;
        float t;
        float r_BNO055;

    public:
        Controller(void);
        float pset_velocity (float motor_velocity, float euler_angle, float euler_angle_acceleration, float pgain);
};
