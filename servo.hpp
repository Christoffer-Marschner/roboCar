#ifndef SERVO_H
#define SERVO_H

#include "main.hpp"
#include "pwm.hpp"

///// MACROS /////
#define SERVO_SIGNAL_LINE_BIT_POS_D_REG PD3
#define SERVO_MIN_POS 0x18
#define SERVO_MAX_POS 0x4D
#define SERVO_MIDDLE_POS (SERVO_MIN_POS + ( (SERVO_MAX_POS - SERVO_MIN_POS) / 2) )
#define SERVO_MAX_SWEEP (SERVO_MIDDLE_POS - SERVO_MIN_POS)

///// FUNCTION DECLARATIONS /////
/* set servo to angle */
uint8_t f_u8InitializeServo();

/* set servo to angle */
uint8_t f_u8SetServoPosition(uint8_t iu8ServoPosition);

#endif