#include "waiting.hpp"

extern volatile uint32_t u32Microseconds10Counter; 

uint8_t u8InterruptTimerInitialized = 0;

/* function to wait for an amount of milliseconds */
uint8_t f_u8WaitForMilliseconds(uint16_t iu32MillisecondsToWait)
{
  /* if waitig for 0 seconds return error 1 */
  if (iu32MillisecondsToWait == 0)
    return 1;
  /* if timer not initialized return error 2 */
  if (u8InterruptTimerInitialized == 0)
    return 2;
  /* set start micros10  */
  uint32_t u32StartMilliseconds = u32Microseconds10Counter / 100;
  /* wait till wanted duration is reached */
  while ( ( (u32Microseconds10Counter / 100) - u32StartMilliseconds) < iu32MillisecondsToWait);
  /* no errors return 0 */
  return 0;
}

/* function to wait for an amount of 10 microseconds */
uint8_t f_u8WaitForMicrosenconds10(uint32_t iu32Microseconds10ToWait)
{
  /* if waitig for 0 seconds return error 1 */
  if (iu32Microseconds10ToWait == 0)
    return 1;
  /* if timer not initialized return error 2 */
  if (u8InterruptTimerInitialized == 0)
    return 2;
  /* set start micros10  */
  uint32_t u32StartMicroseconds10 = u32Microseconds10Counter;
  /* wait till wanted duration is reached */
  while ( (u32Microseconds10Counter - u32StartMicroseconds10) < iu32Microseconds10ToWait);
  /* no errors return 0 */
  return 0;
}

/* function to initialize the 16bit timer to update microseconds from start */
uint8_t f_u8InitializeTimerForInterrupt()
{
  /* set prescaler to 8 */
  SET_BIT_IN_REG(TCCR1B, CS10);
  UNSET_BIT_IN_REG(TCCR1B, CS11);
  UNSET_BIT_IN_REG(TCCR1B, CS12);
  /* set to compare mode on ocr1a register */
  UNSET_BIT_IN_REG(TCCR1A, WGM10);
  UNSET_BIT_IN_REG(TCCR1A, WGM11);
  SET_BIT_IN_REG(TCCR1B, WGM12);
  UNSET_BIT_IN_REG(TCCR1B, WGM13);
  /* let timer trigger every microsecond */
  OCR1A = 160;
  /* enable interrupt */
  SET_BIT_IN_REG(TIMSK1, OCIE1A); 
  /* set status variable */
  u8InterruptTimerInitialized = 1; 
  /* no errors return 0 */
  return 0; 
}

///* function to initialize the 16bit timer */
//uint8_t f_u8InitializeTimerForWaiting()
//{
//  /* set prescaler to 1024 */
//  SET_BIT_IN_REG(TCCR1B, CS10);
//  UNSET_BIT_IN_REG(TCCR1B, CS11);
//  SET_BIT_IN_REG(TCCR1B, CS12);
//  /* set to compare mode on ocr1a register */
//  UNSET_BIT_IN_REG(TCCR1A, WGM10);
//  UNSET_BIT_IN_REG(TCCR1A, WGM11);
//  SET_BIT_IN_REG(TCCR1B, WGM12);
//  UNSET_BIT_IN_REG(TCCR1B, WGM13);
//  return 0;
//}
//
///* function to wait for a given milliseconds */
//uint8_t f_u8WaitForMilliseconds(uint32_t i_u32WaitingTime_ms)
//{
//  /* if waiting 0 millis return error 1 */
//  if (i_u32WaitingTime_ms == 0)
//    return 1;
//  /* if macro is 0 return error 2 */
//  if (MILLISECONDS_IN_1_SECOND == 0)
//    return 2;
//
//  /* initialize the timer ot make sure its configure to waiting mode */
//  f_u8InitializeTimerForWaiting();
//
//  /* calculate how many seconds to wait */
//  uint8_t u8WaitingSeconds = (uint8_t)(i_u32WaitingTime_ms / MILLISECONDS_IN_1_SECOND);
//  /* calculate remaining millis seconds */
//  uint16_t u16WaitingExtraMilliseconds = (uint16_t)(i_u32WaitingTime_ms - (u8WaitingSeconds * MILLISECONDS_IN_1_SECOND) );
//
//  /* wait until all seconds are done */
//  OCR1A = TIMER_VALUE_FOR_1_SECOND;
//  TCNT1 = 0;
//  for (uint8_t u8WaitedSecondsCounter = 0; u8WaitedSecondsCounter < u8WaitingSeconds; u8WaitedSecondsCounter++) 
//  {
//    while (GET_BIT_IN_REG(TIFR1, OCF1A) == 0);
//    SET_BIT_IN_REG(TIFR1, OCF1A);
//  }
//  
//  /* wait the remaining milliseconds */
//  if (u16WaitingExtraMilliseconds > 0)
//  {
//    OCR1A = ( (uint32_t)TIMER_VALUE_FOR_1_SECOND * u16WaitingExtraMilliseconds) / MILLISECONDS_IN_1_SECOND;
//    TCNT1 = 0;
//    while (GET_BIT_IN_REG(TIFR1, OCF1A) == 0);
//    SET_BIT_IN_REG(TIFR1, OCF1A);
//  }
//
//  /* return no error */
//  return 0;
//}
//
//