
#include "servo.hpp"

extern uint8_t u8PwmTimersInitialized; 

uint8_t u8ServoInitialized = false;

/* set servo to angle */
uint8_t f_u8InitializeServo()
{
  /* set servo signal pin to output */
  SET_BIT_IN_REG(DDRD, SERVO_SIGNAL_LINE_BIT_POS_D_REG);
  /* set status variable */
  u8ServoInitialized = true;
  /* return no errors 0 */
  return 0;
}

/* set servo to angle */
uint8_t f_u8SetServoPosition(uint8_t iu8ServoPosition)
{
  /* if pwm timers not initialized return error 1 */
  if (u8PwmTimersInitialized == false)
    return 1;
  /* if not initialized return error 2 */
  if (u8ServoInitialized == false)
    return 2;
  /* limit servo position */
  iu8ServoPosition = LIMIT(iu8ServoPosition, SERVO_MIN_POS, SERVO_MAX_POS);
  /* write the new positioe to OC2B to update servo position */
  OCR2B = iu8ServoPosition;
  /* return no errors 0 */
  return 0;
}
