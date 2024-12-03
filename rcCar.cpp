
#include "rcCar.hpp"

/* function for updating the motors in rc car mode */
uint8_t f_u8UpdateMotors(u8Direction_n iu8DrivingDirection, uint8_t iu8CurrentSpeed)
{
  /* update the motors depending on the direction */
  switch (iu8DrivingDirection)
  {
    /* if invalid return error 1 */
    default:
      return 1;
    case forward:
      f_u8SetPercentMotorSpeeds(iu8CurrentSpeed, iu8CurrentSpeed);
      break;
    case backward:
      f_u8SetPercentMotorSpeeds(-iu8CurrentSpeed, -iu8CurrentSpeed);
      break;
    case left:
      f_u8SetPercentMotorSpeeds(0, iu8CurrentSpeed);
      break;
    case right:
      f_u8SetPercentMotorSpeeds(iu8CurrentSpeed, 0);
      break;
    case none:
      f_u8SetPercentMotorSpeeds(0, 0);
      break;
  }
  /* return no errors 0 */
  return 0;
}

/* function to run rc car mode */
uint8_t f_u8RcCarMode()
{
  IrMessage_struct structIrMessage;
  uint8_t u8CurrentMotorSpeed = RC_MODE_MOTOR_LOW_SPEED;
  u8Direction_n u8DrivingDirection = none;
  uint8_t u8OldData = 0;
  /* loop until escape key has been pressed */
  while (structIrMessage.u8Data != RC_MODE_EXIT_KEY_CODE)
  {
    /* update ir message */
    f_u8GetNewestIrMessage(&structIrMessage);
    /* update if the message has changed or following line */
    if ( (u8OldData != structIrMessage.u8Data) || (structIrMessage.u8Data == irCodeStar) )
    {
      /* update the old data */
      u8OldData = structIrMessage.u8Data;
      /* set action depending on the ir data */
      switch (structIrMessage.u8Data)
      {
        /* motor movement */
        case irCodeOk:
          u8DrivingDirection = none;
          break;
        case irCodeUp:
          u8DrivingDirection = forward;
          break;
        case irCodeDown:
          u8DrivingDirection = backward;
          break;
        case irCodeLeft:
          u8DrivingDirection = left;
          break;
        case irCodeRight:
          u8DrivingDirection = right;
          break;
        /* motor speed */
        case irCode1:
          u8CurrentMotorSpeed = RC_MODE_MOTOR_LOW_SPEED;
          break;
        case irCode2:
          u8CurrentMotorSpeed = RC_MODE_MOTOR_MIDDLE_SPEED;
          break;
        case irCode3:
          u8CurrentMotorSpeed = RC_MODE_MOTOR_HIGH_SPEED;
          break;
        /* servo movement */
        case irCode4:
          f_u8SetServoPosition(SERVO_MIDDLE_POS - (SERVO_MAX_SWEEP / 2) );
          break;
        case irCode5:
          f_u8SetServoPosition(SERVO_MIDDLE_POS);
          break;
        case irCode6:
          f_u8SetServoPosition(SERVO_MIDDLE_POS + (SERVO_MAX_SWEEP / 2) );
          break;
        /* start line follow */
        case irCodeStar:
          f_u8LineFollowFor(10);
          break;
        /* if invalid do nothing */
        default:
          break;
      }
      /* update motors */
      f_u8UpdateMotors(u8DrivingDirection, u8CurrentMotorSpeed); 
    }
  }
  /* return no errors 0 */
  return 0;
}

