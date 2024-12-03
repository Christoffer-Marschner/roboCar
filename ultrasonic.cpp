
#include "ultrasonic.hpp"

extern volatile uint32_t u32Microseconds10Counter; 

uint8_t u8UltrasonicInitialized = false;

/* function to initialize the ultrasonic */
uint16_t f_u8InitializeUltrasonic()
{
  /* set ultrasonic pins */
  SET_BIT_IN_REG(DDRC, ULTRASONIC_TRIG_BIT_POS_C_REG);
  UNSET_BIT_IN_REG(DDRC, ULTRASONIC_ECHO_BIT_POS_C_REG);
  /* set status variable to true */
  u8UltrasonicInitialized = true;
  /* return no errors 0 */
  return 0;
}

/* function to read the distance */
uint16_t f_u8GetUltrasonicDistance_cm()
{
  /* if not initialized return error 1 */
  if (u8UltrasonicInitialized == false)
    return 1;
  /* send trigger */
  SET_BIT_IN_REG(PORTC, ULTRASONIC_TRIG_BIT_POS_C_REG);
  f_u8WaitForMicrosenconds10(2);
  UNSET_BIT_IN_REG(PORTC, ULTRASONIC_TRIG_BIT_POS_C_REG);
  /* wait for echo to rise */
  while (GET_BIT_IN_REG(PINC, ULTRASONIC_ECHO_BIT_POS_C_REG) == 0)
  { }
  while (GET_BIT_IN_REG(PINC, ULTRASONIC_ECHO_BIT_POS_C_REG) == 0)
  { }
  /* wait for echo to fall and get the duration */
  uint32_t u32StartMicroseconds10 = u32Microseconds10Counter; 
  while ( (GET_BIT_IN_REG(PINC, ULTRASONIC_ECHO_BIT_POS_C_REG) == 1) )//&& ( (u32Microseconds10Counter - u32StartMicroseconds10) < 2000) );
  { }
  uint16_t u16EchoDurationMicroseconds10 = (u32Microseconds10Counter - u32StartMicroseconds10); 
  uint8_t u8EchoDistance_cm = LIMIT( ( (SPEED_OF_SOUND_CM_MS * (u16EchoDurationMicroseconds10 / 100) ) / 2), ULTRASONIC_MIN_READABLE_DISTANCE, ULTRASONIC_MAX_READABLE_DISTANCE); 
  return u8EchoDistance_cm;
}
