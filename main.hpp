#ifndef MAIN_H
#define MAIN_H

///// GLOBAL INCLUDES /////
#include "Arduino.h"

///// MACROS /////
/* bit manipulation macros */
#define SET_BIT_IN_REG(reg, bitPos) (reg |= (1 << bitPos) ) 
#define UNSET_BIT_IN_REG(reg, bitPos) (reg &= ~(1 << bitPos) ) 
#define GET_BIT_IN_REG(reg, bitPos) ( ( (reg >> bitPos) & 1) ) 
#define LIMIT(value, lowerLim, upperLim) ( value >= upperLim ? upperLim : value <= lowerLim ? lowerLim : value ) 
#define GET_SIGN_OF(value) ( value < 0 ? -1 : 1 ) 
/* robot defines */
#define ROBOT_MILLISECONDS_1_360_DEG_2WHEEL_TURN 1300
/* builtin led */
#define BUILTIN_LED_BIT_POS_B_REG PB5 

///// ENUMS /////
enum u8Side_n
{
  leftSide,
  rightSide
};

enum u8Direction_n
{
  forward,
  left,
  backward,
  right,
  up,
  down,
  none
};

///// FUNCTION DECLARATION /////
/* simple function for toggling the builting led */
uint8_t f_u8ToggleBuiltinLed();

#endif 
