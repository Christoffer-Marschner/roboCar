/*
  NOT USED: ultrasonic sensor is not accurate enough to detect objects
*/

#ifndef OBJECT_FOLLOW_H
#define OBJECT_FOLLOW_H

#include "main.hpp"
#include "servo.hpp"
#include "ultrasonic.hpp"

/*
  notes:
    o 2 states
      o searching
        o stationary
        o servo constantly sweeping
        o checking for low distance to find object to follow 
          -> if found go to following state
      o following
        o servo turns to follow the object
        o robot regulates driving speed depending on distance of object
        o servo angle used fo turning 
*/

///// MACROS /////
#define OBJECT_FOLLOW_DISTANCE_TO_FOLLOW_OBJECT_AT_CM 10  
#define OBJECT_FOLLOW_SERVO_VALUE_STEPS_IN_STATIONARY 1 
#define OBJECT_FOLLOW_WAITING_TIME_AFTER_SERVO_STEPS_MS 200 
#define OBJECT_FOLLOW_DISTANCE_TO_CONSIDER_FOLLOWING_CM 10 
#define OBJECT_FOLLOW_SWEEP_COUNTER_STEPS 2
#define OBJECT_FOLLOW_MAX_SWEEP 50
#define OBJECT_FOLLOW_DISTANCE_REDUCED_TO_CONSIDER_UPDATE 1 
#define OBJECT_FOLLOW_WANTED_DISTANCE_CM (OBJECT_FOLLOW_DISTANCE_TO_FOLLOW_OBJECT_CM) 
#define OBJECT_FOLLOW_MAX_DRIVING_SPEED 80

///// FUNCTION DECLARATIONS /////
/* function for running object follow program */
uint8_t f_u8FollowObject();

#endif
