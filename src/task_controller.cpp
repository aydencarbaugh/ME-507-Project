#include <Arduino.h>
#include "controller.h"
#include <cmath> 
#include <math.h>
#include <set>

/** @brief This task is used to initialize the stat_tracker class. 
 *  @details This file creates all the variables needed for all the methods.
 */

Controller :: Controller (void)
{
    float velocity = 0;
    float angle = 0;
    float angle_acceleration = 0;
    float M_w = 500; // mass of total cube in kg
    float F_w = M_w*9.81; // Weight of cube in N
    float r_CG = .0988; // radius to center of gravity in m
    float J_RW = 50; // rotational inertia for reaction wheel in kg*m^2
    float r_RW = .0988; // radius to reaction wheel in m
    float M_RW = 0.5; // mass of reaction wheel in kg
    float J_c = 50; // rotational inertia of the cube
    float t = 100; // time between velocity measurements in ms
    float r_BNO055 = 100; // radius from BNO055 to corner
    
}

float Controller :: pset_velocity (float motor_velocity, float euler_angle, float euler_angle_acceleration, float pgain)
{
    float vel = motor_velocity;
    float ang = euler_angle;
    float ang_acc = euler_angle_acceleration * r_BNO055;
    float gain = pgain;

    float motor_accel = ((F_w*r_CG*sin(ang)) + (J_c*ang_acc))/(J_RW + (M_RW*r_RW*r_RW));
    float mot_speed = pgain*((motor_accel*t) + vel);
    vTaskDelay(100);
    return (mot_speed);

}
