/** @file task_motor.h
 *  Header file that contains the interface for a motor task using a 
 *  three-phase brushless DC motor using the DRV8323RH motor driver chip 
 *  on a custom PCB.
 *  
 *  @author Juan Luna
 *  @date   2022-Nov-02 Original file
 *  @date   2022-Dec-05 Modified
 */

#include <Arduino.h>
#include "PrintStream.h"
#include "shares.h"

// Task function implementing motor functionality
void task_motor(void* p_params);