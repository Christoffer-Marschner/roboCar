#ifndef RC_CAR_H
#define RC_CAR_H

#include "main.hpp"
#include "irCommunication.hpp"
#include "motor.hpp"
#include "servo.hpp"
#include "lineFollow.hpp"

///// MACROS /////
#define RC_MODE_EXIT_KEY_CODE irCodeHash
#define RC_MODE_MOTOR_LOW_SPEED     50
#define RC_MODE_MOTOR_MIDDLE_SPEED  75
#define RC_MODE_MOTOR_HIGH_SPEED    100

///// FUNCTION DECLARATIONS /////
/* function to run rc car mode */
uint8_t f_u8RcCarMode(); 

#endif