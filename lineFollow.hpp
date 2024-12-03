#ifndef LINE_FOLLOW_H
#define LINE_FOLLOW_H

#include "main.hpp"
#include "lightSensor.hpp" 
#include "servo.hpp" 
#include "motor.hpp" 
#include "waiting.hpp" 
    
///// MACROS /////
#define LINE_FOLLOW_BASE_SPEED 40
#define LINE_FOLLOW_ERROR_TO_STEERING_FACTOR 200
#define LINE_FOLLOW_TIME_BETWEEN_UPDATES_MS 5

///// FUNCTION DECLARATION /////
/* start line follow for duration */
uint8_t f_u8LineFollowFor(uint32_t iu32FollowDuration_ms);

#endif
