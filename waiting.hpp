#ifndef TIMER_H
#define TIMER_H

#include "main.hpp"

///// MACROS /////
#define TIMER_VALUE_FOR_1_SECOND 15625
#define MILLISECONDS_IN_1_SECOND 1000

///// FUNCTION DECLARATIONS /////
/* function to initialize the 16bit timer to update microseconds from start */
uint8_t f_u8InitializeTimerForInterrupt();

/* function to initialize the 16bit timer to update microseconds from start */
uint8_t f_u8WaitForMicrosenconds10(uint32_t iu32Microseconds10ToWait);

/* function to wait for an amount of milliseconds */
uint8_t f_u8WaitForMilliseconds(uint16_t iu32MillisecondsToWait);

///* function to wait for a given milliseconds */
//uint8_t f_u8WaitForMilliseconds(uint32_t i_u32WaitingTime_ms);

#endif
