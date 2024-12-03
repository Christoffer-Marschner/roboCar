///// INCLUDES /////
#include "main.hpp"
#include "waiting.hpp"
#include "pwm.hpp"
#include "servo.hpp"
#include "motor.hpp"
#include "ultrasonic.hpp"
#include "lightSensor.hpp"
#include "lineFollow.hpp"
#include "irCommunication.hpp"
#include "rcCar.hpp"
#include "objectFollow.hpp"

volatile uint32_t u32Microseconds10Counter = 0; 

ISR(TIMER1_COMPA_vect)
{
  u32Microseconds10Counter += 1;
}

int main()
{
  ///// SETUP /////
  /* set builtin led to output */
  SET_BIT_IN_REG(DDRB, BUILTIN_LED_BIT_POS_B_REG);
  f_u8InitializeTimersForPWM();
  f_u8InitializeTimerForInterrupt();
  f_u8InitializeUltrasonic();
  f_u8InitializeMotor(); 
  f_u8InitializeServo();
  f_u8InitializeLightSensors();
  f_u8InitializeIrSensor();
  /* enable interrups */
  sei();

  f_u8RcCarMode();
  f_u8StopMotors();

  ///// LOOP /////
  for (;;)
  { }

  return 0;
}

/* simple function for toggling the builting led */
uint8_t f_u8ToggleBuiltinLed()
{
  switch (GET_BIT_IN_REG(PORTB, BUILTIN_LED_BIT_POS_B_REG) ) 
  {
    default:
      /* return error 1 bit value not 1 or 2 */
      return 1;
    case 0:
    SET_BIT_IN_REG(PORTB, BUILTIN_LED_BIT_POS_B_REG);
      break; 
    case 1:
    UNSET_BIT_IN_REG(PORTB, BUILTIN_LED_BIT_POS_B_REG);
      break; 
  }

  /* return no errors */
  return 0;
}
