/*
  NOT USED used: ultrasonic sensor is not accurate enough to detect objects
*/

#include "objectFollow.hpp"

/* function for searching mode, returns servo value of found object */
uint8_t f_u8SearchClosestServoValue()
{
  uint16_t u16LowestDistance_cm = 300;
  uint16_t u16CurrentDistance_cm;
  uint8_t u8CurrentServoPosition = SERVO_MIN_POS;
  uint8_t u8ServoPositionAtClosestObject;
  /* loop until distance under the limit has been found */
  while (u16LowestDistance_cm > OBJECT_FOLLOW_DISTANCE_TO_FOLLOW_OBJECT_AT_CM)
  {
    /* set angle of servo */
    f_u8SetServoPosition(u8CurrentServoPosition);
    u8CurrentServoPosition += OBJECT_FOLLOW_SERVO_VALUE_STEPS_IN_STATIONARY; 
    if (u8CurrentServoPosition > SERVO_MAX_POS) 
    { u8CurrentServoPosition = SERVO_MIN_POS; }
    /* wait a bit for the servo to get to position */
    f_u8WaitForMilliseconds(OBJECT_FOLLOW_WAITING_TIME_AFTER_SERVO_STEPS_MS);
    /* get distance and check if lowest */
    u16CurrentDistance_cm = f_u8GetUltrasonicDistance_cm();
    if (u16CurrentDistance_cm < u16LowestDistance_cm) 
    { 
      u16LowestDistance_cm = u16CurrentDistance_cm; 
      u8ServoPositionAtClosestObject = u8CurrentServoPosition;
    }
  }
  /* return the lowest distance */
  return u8ServoPositionAtClosestObject;
}

/* function for searching mode, returns servo value of found object */
uint8_t f_u8followClosestServoValue(uint8_t iu8ServoValueAtObject)
{
  uint16_t u16CurrentDistance;
  uint8_t u8CurrentServoPosition = iu8ServoValueAtObject;
  uint8_t u8SweepCounter = 0;
  /* loop forever !! dont loop until forever */
  for (;;)
  {
    /* update distance */
    u16CurrentDistance = f_u8GetUltrasonicDistance_cm();
    /* if distance reduced by threshold follow object */
    if (u16CurrentDistance > OBJECT_FOLLOW_DISTANCE_TO_FOLLOW_OBJECT_AT_CM)
    {
      u8SweepCounter += OBJECT_FOLLOW_SWEEP_COUNTER_STEPS;
      if ( (u8SweepCounter % (OBJECT_FOLLOW_SWEEP_COUNTER_STEPS * 2) ) == 0) 
      { u8CurrentServoPosition = LIMIT( ( (int16_t)u8CurrentServoPosition + u8SweepCounter), SERVO_MIN_POS, SERVO_MAX_POS); }
      else
      { u8CurrentServoPosition = LIMIT( ( (int16_t)u8CurrentServoPosition - u8SweepCounter), SERVO_MIN_POS, SERVO_MAX_POS); }
    }
    else
    { u8SweepCounter = 0; }
    /* update servo position */
    f_u8SetServoPosition(u8CurrentServoPosition);
    f_u8WaitForMilliseconds(OBJECT_FOLLOW_WAITING_TIME_AFTER_SERVO_STEPS_MS);
    /* update motors */
  }
}

/* function for running object follow program */
uint8_t f_u8FollowObject()
{
  uint8_t u8ServoValueAtObject; 
  /* get servo value at closest distance */
  u8ServoValueAtObject = f_u8SearchClosestServoValue();
  /* enter follow mode */
  f_u8followClosestServoValue(u8ServoValueAtObject); 
  return 0;
}
