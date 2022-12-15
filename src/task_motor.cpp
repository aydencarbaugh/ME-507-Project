/** @file task_motor.cpp
 *  This file implements a motor task using a three-phase brushless DC motor
 *  using the DRV8323RH motor driver chip on a custom PCB.
 *  
 *  @author Jarod Lyles
 *  @author Juan Luna
 *  @date   2022-Nov-02 Original file
 *  @date   2022-Dec-05 Modified
 */

#include "task_motor.h"

/** @brief   Task that implements the functionality of a three-phase BLDC motor.
 *  @details Function that sets direction and speed of a three-phase brushless
 *           DC motor for the DRV8323RH motor driver. File sets percent duty
 *           cycle level according to a simple proportional control system.      
 *  @param   p_params A pointer to parameters passed to this task. This 
 *           pointer is ignored; it should be set to @c NULL in the 
 *           call to @c xTaskCreate() which starts this task
 */
void task_motor(void* p_params)
{
    /// Assign GPIO pin 33 to Hall effect sensor input for phase A
    const uint8_t HALL_A_IN = 33;
    /// Assign GPIO pin 32 to Hall effect sensor input for phase B
    const uint8_t HALL_B_IN = 32;
    /// Assign GPIO pin 35 to Hall effect sensor input for phase C
    const uint8_t HALL_C_IN = 35;

    /// Assign GPIO pin 12 to Hall effect sensor output for phase A
    const uint8_t HALL_A_OUT = 12;    // INLC
    /// Assign GPIO pin 14 to Hall effect sensor output for phase B
    const uint8_t HALL_B_OUT = 14;    // INHB
    /// Assign GPIO pin 27 to Hall effect sensor output for phase C
    const uint8_t HALL_C_OUT = 27;    // INLB

    /// Assign GPIO pin 26 to motor brake output 
    const uint8_t INHC = 26;
    /// Assign GPIO pin 25 to motor direction output
    const uint8_t INLC = 25;

    /// Assign GPIO pin 13 to PWM signal output
    const uint8_t INHA = 13;  

    // Motor PWM parameters

    /// Motor PWM frequency; at least 20 kHz
    const uint16_t freq = 50000;
    /// Motor channel number
    const uint8_t channel = 0;
    /// PWM resolution; 8-16 bit available
    const uint8_t resolution = 8;
    /// Converts duty cycle to 8-bit number for ledcWrite function
    float dutyCycle =  255 * setpoint_pwm_shares.get();

    // Configure PWM channels using built-in ledc functions
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(INHA, channel);

    // Set up the brake and direction GPIOs for output
    pinMode(INLC, OUTPUT);
    pinMode(INLC, OUTPUT);

    // Set up the hall sensor inputs GPIOs for input
    pinMode(HALL_A_IN, INPUT);
    pinMode(HALL_B_IN, INPUT);
    pinMode(HALL_C_IN, INPUT);

    // Set up the hall sensor outputs GPIOs for output
    // These are fed into the motor driver
    pinMode(HALL_A_OUT, OUTPUT);
    pinMode(HALL_B_OUT, OUTPUT);
    pinMode(HALL_C_OUT, OUTPUT);
    
    /// Holds the current state of the finite-state machine
    uint8_t state = 0;

    while (true)
    {
        // STATE 0: Wait for input to transition state and start balancing
        if (state == 0)
        {
            // If begin_balancing shares is true
            if (begin_balancing.get ())
            {
                // Lower start-balancing "flag" once actual balancing starts  
                begin_balancing.put(false);
                // Transition to state 1
                state = 1;
            }
        }
        // STATE 1: Run the motor
        else if (state == 1)
        {
            // Turns off the brake
            digitalWrite(INLC, HIGH); 
            // Writes the direction of the motor according to latest share value     
            digitalWrite(INHC, direction_shares.get());
            // Outputs the PWM cycle with calculated duty cycle from controller
            ledcWrite(channel, dutyCycle);  
            
            // The following conditional statements read the input from the 
            // Hall effect sensors on an input pin, then mimic those signals on
            // the output pin that goes into the DRV.
            // We did this for two reasons:
            
            // 1. This allowed us to easily interface with the Hall effect
            // sensors in the motor using our custom board design, whether
            // our custom board worked or not.
            // 2. We read signals from the Hall effect sensors to understand
            // better how they functioned and tired to measure the speed of 
            // the motor from this (though this wasn't implmented).

            if (digitalRead(HALL_A_IN))
            {
                digitalWrite(HALL_A_OUT, HIGH);
            }
            else
            {
                digitalWrite(HALL_A_OUT, LOW);
            }

            if (digitalRead(HALL_B_IN))
            {
                digitalWrite(HALL_B_OUT, HIGH);
            }
            else
            {
                digitalWrite(HALL_B_OUT, LOW);
            }

            if (digitalRead(HALL_C_IN))
            {
                digitalWrite(HALL_C_OUT, HIGH);
            }
            else
            {
                digitalWrite(HALL_C_OUT, LOW);
            }
        }
        // During testing, we found that we needed an extreme low delay to 
        // run the motor correctly. The Hall sensors update very quickly, and
        // if they are not read fast enough, the motor commutation is extremely
        //choppy and does not achieve speed. In future implmentation, 
        // we might want to figure out how to run even faster.
        vTaskDelay(1);
    }
}