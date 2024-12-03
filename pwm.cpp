
#include "pwm.hpp"

uint8_t u8PwmTimersInitialized = false; 

/* initialize timers for pwm for motors and servo */
uint8_t f_u8InitializeTimersForPWM()
{
  u8PwmTimersInitialized = true;
  /* timer 2 */
  /* set pwm phase correct mode */
  SET_BIT_IN_REG(TCCR2A, WGM20);
  UNSET_BIT_IN_REG(TCCR2A, WGM21);
  UNSET_BIT_IN_REG(TCCR2B, WGM22);
  /* set prescaler to 256 */
  UNSET_BIT_IN_REG(TCCR2B, CS20);
  SET_BIT_IN_REG(TCCR2B, CS21);
  SET_BIT_IN_REG(TCCR2B, CS22);
  /* set output pins OC2A(PB3), OC2B(PD3) */
  UNSET_BIT_IN_REG(TCCR2A, COM2A0);
  SET_BIT_IN_REG(TCCR2A, COM2A1);
  UNSET_BIT_IN_REG(TCCR2A, COM2B0);
  SET_BIT_IN_REG(TCCR2A, COM2B1);
  /* timer 0 */
  /* set pwm phase correct mode */
  SET_BIT_IN_REG(TCCR0A, WGM00);
  UNSET_BIT_IN_REG(TCCR0A, WGM01);
  UNSET_BIT_IN_REG(TCCR0B, WGM02);
  /* set prescaler to 256 */
  UNSET_BIT_IN_REG(TCCR0B, CS00);
  UNSET_BIT_IN_REG(TCCR0B, CS01);
  SET_BIT_IN_REG(TCCR0B, CS02);
  /* set output pins OC0B(PD5) */
  UNSET_BIT_IN_REG(TCCR0A, COM0B0);
  SET_BIT_IN_REG(TCCR0A, COM0B1);
  /* return no errors 0 */
  return 0;
}
