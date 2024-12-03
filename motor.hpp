#ifndef MOTOR_H
#define MOTOR_H

#include "main.hpp"
#include "pwm.hpp"

///// MACROS /////
/* pin mapping */
#define MOTOR_RIGHT_ENABLE_BIT_POS_D_REG   PD5 /* timer pwm bit OC0B */
#define MOTOR_LEFT_ENABLE_BIT_POS_B_REG    PB3 /* timer pwm bit OC2A */

#define MOTOR_RIGHT_FORWARD_BIT_POS_D_REG  PD6 
#define MOTOR_RIGHT_BACKWARD_BIT_POS_D_REG PD7 
#define MOTOR_LEFT_FORWARD_BIT_POS_B_REG   PB1 
#define MOTOR_LEFT_BACKWARD_BIT_POS_B_REG  PB0 
/* speed control */
#define MOTOR_LEFT_SIDE_MAX_SPEED  0xFF
#define MOTOR_LEFT_SIDE_MIN_SPEED  0x40
#define MOTOR_RIGHT_SIDE_MAX_SPEED  0xCF
#define MOTOR_RIGHT_SIDE_MIN_SPEED  0x30

///// FUNCTION DECLARATIONS /////
/* initialize motor pins */
uint8_t f_u8InitializeMotor();

/* function for setting speed of both wheels in percentage */
uint8_t f_u8SetPercentMotorSpeeds(int8_t in8LeftWheelSpeed_Percent, int8_t in8RightWheelSpeed_Percent);

/* wrapper to stop motors */
uint8_t f_u8StopMotors();

#endif
