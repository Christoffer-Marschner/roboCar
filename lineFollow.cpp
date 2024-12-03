
#include "lineFollow.hpp"

extern volatile uint32_t u32Microseconds10Counter; 

/* start line follow for duration */
uint8_t f_u8LineFollowFor(uint32_t iu32FollowDuration_ms)
{
  int16_t n16Steering;
  int8_t n8Error;  
  uint32_t u32StartTime_ms = u32Microseconds10Counter / 100;

  /* start a loop until spedified time has been reached or forever if time == 0 */
  while( ( ( (u32Microseconds10Counter / 100) - u32StartTime_ms) < iu32FollowDuration_ms) || (iu32FollowDuration_ms == 0) )
  {
    /* get the new error between left and right sensor */
    n8Error = f_u8GetLightSensorValue(leftSensor) - f_u8GetLightSensorValue(rightSensor) ;
    /* change the steering depending on the error */
    n16Steering = n8Error * LINE_FOLLOW_ERROR_TO_STEERING_FACTOR;
    /* adapt the wheel speeds */
    f_u8SetPercentMotorSpeeds(LIMIT(LINE_FOLLOW_BASE_SPEED - n16Steering, -100, 100), LIMIT(LINE_FOLLOW_BASE_SPEED + n16Steering, -100, 100) );
    /* wait for a while */
    f_u8WaitForMilliseconds(LINE_FOLLOW_TIME_BETWEEN_UPDATES_MS);
  }
  /* return no errors 0 */
  return 0;
}

