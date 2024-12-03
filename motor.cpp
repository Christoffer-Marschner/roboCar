
#include "motor.hpp"

extern uint8_t u8PwmTimersInitialized; 

uint8_t u8MotorsInitialized = false; 

/* initialize motor pins */
uint8_t f_u8InitializeMotor()
{
  /* set motor enable pins to output */
  SET_BIT_IN_REG(DDRD, MOTOR_RIGHT_ENABLE_BIT_POS_D_REG);
  SET_BIT_IN_REG(DDRB, MOTOR_LEFT_ENABLE_BIT_POS_B_REG);
  /* set motor direction pins to output */
  SET_BIT_IN_REG(DDRD, MOTOR_RIGHT_FORWARD_BIT_POS_D_REG);
  SET_BIT_IN_REG(DDRD, MOTOR_RIGHT_BACKWARD_BIT_POS_D_REG);
  SET_BIT_IN_REG(DDRB, MOTOR_LEFT_FORWARD_BIT_POS_B_REG);
  SET_BIT_IN_REG(DDRB, MOTOR_LEFT_BACKWARD_BIT_POS_B_REG);
  /* set status variable */
  u8MotorsInitialized = true;
  /* return no errors 0 */
  return 0;
}

/* return the correct register depending on a direction */
uint8_t f_u8GetMoveDirectionBit(u8Direction_n iu8Direction, uint8_t iu8BackwardsBitPos, uint8_t iu8ForwardsBitPos)
{
  switch (iu8Direction)
  {
    /* invalid direction return error 1 */
    default:
      return 1;
    case forward:
      return iu8ForwardsBitPos;
    case backward:
      return iu8BackwardsBitPos;
  }
}

/* function for setting speed */
uint8_t f_u8SetRawMotorSpeedOn(u8Side_n iu8SideToChange, u8Direction_n iu8WheelMoveDirection, uint8_t iu8WantedSpeed)
{
  /* if pwm timers not initialized return error 1 */
  if (u8PwmTimersInitialized == 0) 
    return 1;
  /* if direction invalid return error 2 */
  if ( (iu8WheelMoveDirection != forward) && (iu8WheelMoveDirection != backward) ) 
    return 2;
  /* if motors not initialized return error 3 */
  if (u8MotorsInitialized == false)
    return 3;
  /* apply speed */
  switch (iu8SideToChange)
  {
    /* invalid side return error 2 */
    default:
      return 2; 
    /* apply speed to wanted side */
    case rightSide:
      /* update direction */
      UNSET_BIT_IN_REG(PORTD, MOTOR_RIGHT_FORWARD_BIT_POS_D_REG);
      UNSET_BIT_IN_REG(PORTD, MOTOR_RIGHT_BACKWARD_BIT_POS_D_REG);
      SET_BIT_IN_REG(PORTD, f_u8GetMoveDirectionBit(iu8WheelMoveDirection, MOTOR_RIGHT_BACKWARD_BIT_POS_D_REG, MOTOR_RIGHT_FORWARD_BIT_POS_D_REG) );
      /* update pwm */
      OCR0B = LIMIT(iu8WantedSpeed, MOTOR_RIGHT_SIDE_MIN_SPEED, MOTOR_RIGHT_SIDE_MAX_SPEED);
      OCR0B = iu8WantedSpeed;
      break;
    case leftSide:
      /* update direction */
      UNSET_BIT_IN_REG(PORTB, MOTOR_LEFT_FORWARD_BIT_POS_B_REG);
      UNSET_BIT_IN_REG(PORTB, MOTOR_LEFT_BACKWARD_BIT_POS_B_REG);
      SET_BIT_IN_REG(PORTB, f_u8GetMoveDirectionBit(iu8WheelMoveDirection, MOTOR_LEFT_BACKWARD_BIT_POS_B_REG, MOTOR_LEFT_FORWARD_BIT_POS_B_REG) );
      /* update pwm */
      OCR2A = LIMIT(iu8WantedSpeed, MOTOR_LEFT_SIDE_MIN_SPEED, MOTOR_LEFT_SIDE_MAX_SPEED);
      break;
  }
  /* return no errors 0 */
  return 0;
}

/* function for setting speed */
uint8_t f_u8StopMotorOn(u8Side_n iu8SideToStop)
{
  /* set speed to 0 */ 
  switch (iu8SideToStop)
  {
    /* invalid direction return error 1 */
    default:
      return 1;
    case leftSide:
      OCR2A = 0; 
      break;
    case rightSide:
      OCR0B = 0; 
      break;
  }
  /* no errors return 0 */
  return 0;
}

/* function for setting speed of both wheels in percentage */
uint8_t f_u8SetPercentMotorSpeeds(int8_t in8LeftWheelSpeed_Percent, int8_t in8RightWheelSpeed_Percent)
{
  /* left wheel */
  /* if stopping */
  if (in8LeftWheelSpeed_Percent == 0) 
  {
    f_u8StopMotorOn(leftSide);
  }
  /* normal speed */
  else
  {
    /* get directions */
    u8Direction_n u8LeftWheelDirection = forward; 
    if (GET_SIGN_OF(in8LeftWheelSpeed_Percent) == -1 )
    {
      in8LeftWheelSpeed_Percent *= -1; 
      u8LeftWheelDirection = backward;
    }
    /* calculate the raw speed value */
    uint8_t u8LeftWheelRawSpeed = MOTOR_LEFT_SIDE_MIN_SPEED + ( ( (MOTOR_LEFT_SIDE_MAX_SPEED - MOTOR_LEFT_SIDE_MIN_SPEED) * in8LeftWheelSpeed_Percent) / 100 );
    /* apply raw speed value */
    f_u8SetRawMotorSpeedOn(leftSide, u8LeftWheelDirection, u8LeftWheelRawSpeed);
  }
  /* right wheel */
  /* if stopping */
  if (in8RightWheelSpeed_Percent == 0) 
  {
    f_u8StopMotorOn(rightSide);
  }
  /* normal speed */
  else
  {
    /* get direction */
    u8Direction_n u8RightWheelDirection = forward; 
    if (GET_SIGN_OF(in8RightWheelSpeed_Percent) == -1 )
    {
      in8RightWheelSpeed_Percent *= -1;
      u8RightWheelDirection = backward;
    }
    /* calculate the raw speed value */
    uint8_t u8RightWheelRawSpeed = MOTOR_RIGHT_SIDE_MIN_SPEED + ( ( (MOTOR_RIGHT_SIDE_MAX_SPEED - MOTOR_RIGHT_SIDE_MIN_SPEED) * in8RightWheelSpeed_Percent) / 100 );
    /* apply raw speed value */
    f_u8SetRawMotorSpeedOn(rightSide, u8RightWheelDirection, u8RightWheelRawSpeed);
  }
  /* return no errors 0 */
  return 0;
}

/* wrapper to stop motors */
uint8_t f_u8StopMotors()
{
  /* stop motors */
  f_u8SetPercentMotorSpeeds(0, 0);
  /* return no errors 0 */
  return 0;
}



















