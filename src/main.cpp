/** @file   main.cpp
 *  This file contains the main script for executing a program
 *  that balances a cube on an edge.
 * 
 *  @author Juan Luna
 *  @date   2022-Nov-02 Original file
 *  @date   2022-Dec-05 Modified
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "shares.h"
#include "task_controller.h"
#include "task_motor.h"
#include "task_web_ui.h"

/// Share that starts the cube-balancing algorithm
Share<bool> begin_balancing ("Start balancing");
/// Share that holds the Euler angle in the y-direction
Share<float> euler_shares ("Euler y-angle");
/// Share that holds the linear acceleration in the y-direction
Share<float> accel_shares ("Linear y-acceleration");
/// Share for the direction of rotation of the motor
Share<bool> direction_shares ("Motor Direction");
/// Share for the setpoint pwm signal of the motor
Share<float> setpoint_pwm_shares ("Setpoint PWM");
/// Share for the measured speed of the motor
Share<float> measured_speed_shares ("Measured Motor Speed");

/** @brief   The Arduino setup function.
 */
void setup()
{
    // Initialize serial port
    Serial.begin(115200);
    // Wait until serial port is ready
    while (!Serial) { }
    
    // Create the task for the IMU task
    xTaskCreate(task_imu, "IMU Task", 248, NULL, 3, NULL);
    // Create the task for the controller task
    xTaskCreate(task_controller, "Controller task", 256, NULL, 1, NULL);
    // Create the task for the motor task
    xTaskCreate(task_motor, "Motor Task", 248, NULL, 4, NULL);
    // Task which runs the web server. It runs at a low priority
    xTaskCreate (task_webserver, "Web Server", 192, NULL, 1, NULL);

    Serial << "Task functions created." << endl;
    vTaskDelay(1000);
}

/** @brief   The Arduino loop function.
 */
void loop()
{
    vTaskDelay(60000);
}
