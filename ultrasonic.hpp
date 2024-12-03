#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "main.hpp"
#include "waiting.hpp"

///// MACROS /////
/* general */
#define ECHO_TIMEOUT_US10 200000
#define SPEED_OF_SOUND_CM_MS 34
#define ULTRASONIC_MIN_READABLE_DISTANCE 0
#define ULTRASONIC_MAX_READABLE_DISTANCE 300
/* pinout */
#define ULTRASONIC_TRIG_BIT_POS_C_REG PC5
#define ULTRASONIC_ECHO_BIT_POS_C_REG PC4

///// FUNCTION DECLARATION /////
/* function to initialize the ultrasonic */
uint16_t f_u8InitializeUltrasonic();

/* function to read the distance */
uint16_t f_u8GetUltrasonicDistance_cm();

#endif
