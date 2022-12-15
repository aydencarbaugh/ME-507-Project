// Include Statements
#include <Arduino.h>
#include "PrintStream.h"


//Define Statements
#define Hallsens1_PIN 13
#define Hallsens2_PIN 12
#define Hallsens3_PIN 14

/** @brief   Task which implements debounce state diagram.
 *  @details This task sets the GPIO pin 13 to input pullup and reads the voltage of the pin
 *           to increment through the state machine.
 *  @param   p_params An unused pointer to (no) parameters passed to this task
 */
void task_hallsens1 (void* p_params)
{
    // Sets pinmode to a pullup input
    pinMode(Hallsens1_PIN, INPUT);
    while (true)
    {
        int8_t reading1 = digitalRead (Hallsens1_PIN);
        int8_t reading2 = digitalRead (Hallsens2_PIN);
        int8_t reading3 = digitalRead (Hallsens3_PIN);

        if ((reading1 == 0) && (reading2 == 1) && (reading3 == 1))
        {
            Serial << "In Phase 1" << endl;
        }

        if ((reading1 == 1) && (reading2 == 0) && (reading3 == 1))
        {
            Serial << "In Phase 2" << endl;
        }

        if ((reading1 == 1) && (reading2 == 1) && (reading3 == 0))
        {
            Serial << "In Phase 3" << endl;
        }

        else
        {
            Serial << reading1 << reading2 << reading3 << endl;
        }

        vTaskDelay(100);
    }
}

/** @brief   The Arduino setup function.
 *  @details This function is used to set up the microcontroller by starting
 *           the serial port, saying hello, and creating the tasks.
 */
void setup (void) 
{
    // The serial port must begin before it may be used
    Serial.begin (115200);
    while (!Serial) 
    {
    }

    // Creates the task which creates the 500 Hz wave form
    xTaskCreate (task_hallsens1, "Hallsens1", 1024, NULL, 2, NULL);
}

/** @brief   The Arduino loop function.
 *  @details This function is called periodically by the Arduino system. It
 *           runs as a low priority task. On some microcontrollers it will
 *           crash when FreeRTOS is running, so we usually don't use this
 *           function for anything, instead just having it delay itself. 
 */
void loop (void)
{
 // Delay for a whole minute, which is an eternity to a microcontroller
 vTaskDelay (60000);
}
