/** @file   shares.h
 *  This file contains extern declarations of shares and queues which are
 *  used in more than one file of the self-balancing cube project.
 * 
 *  @author  Juan Luna
 *  @date    2022-Nov-15 
 */

#include "PrintStream.h"
#include "taskshare.h"
#include "taskqueue.h"

/// A share that triggers the self-balancing algorithm
extern Share<bool> begin_balancing;
/// A share that holds the Euler angle in y-direction
extern Share<float> euler_shares;
/// A share that holds the linear acceleration in y-direction
extern Share<float> accel_shares;
/// A share for the direction of rotation of the motor
extern Share<bool> direction_shares;
/// A share for the setpoint pwm signal of the motor
extern Share<float> setpoint_pwm_shares;
/// A share for the setpoint pwm signal of the motor
extern Share<float> measured_speed_shares;
