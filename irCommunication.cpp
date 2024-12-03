
#include "irCommunication.hpp"

extern volatile uint32_t u32Microseconds10Counter; 
extern uint8_t u8InterruptTimerInitialized;

/* function to initialize the ir sensor */
uint8_t f_u8InitializeIrSensor()
{
  /* set the pin to input */
  UNSET_BIT_IN_REG(DDRB, IR_SIGNAL_BIT_IN_B_REG);
  /* return no errors 0 */
  return 0;
}

/* function to check if an ir message is being sent and get it */
uint8_t f_u8GetNewestIrMessage(IrMessage_struct* pistructIrMessage)
{
  uint32_t u32SignalDuration_us10;
  uint32_t u32MessageBuf = 0;
  static uint32_t u32OldMessageBuf = 0;
  /* if timer for timekeeping not initialized return error 2 */
  if (u8InterruptTimerInitialized == false)
    return 2;
  /* check if ir is starting communication */
  if (GET_IR_SIGNAL_VALUE() == 1)
  {
    /* wait until start signal is finshed */
    while (GET_IR_SIGNAL_VALUE() == 1)
    { }
    /* wait for rising to indicate first bit sent */
    while (GET_IR_SIGNAL_VALUE() == 0)
    { }
    /* get all message bits */
    for (uint8_t u8MessageBitCounter = 0; u8MessageBitCounter <= (IR_MESSAGE_LENGTH_IN_BIT - 1); u8MessageBitCounter++)
    {
      /* get the time at start of pulse */
      u32SignalDuration_us10 = u32Microseconds10Counter;
      /* wait until next pulse starts or timeout, in which case a repeat was most likely triggered */
      while (GET_IR_SIGNAL_VALUE() == 1)
      { }
      while ((GET_IR_SIGNAL_VALUE() == 0) && ((u32Microseconds10Counter - u32SignalDuration_us10) < IR_TIMEOUT_DURATION_US10))
      { }
      /* measure time between pulses, to get the corresponding bit */
      u32SignalDuration_us10 = u32Microseconds10Counter - u32SignalDuration_us10;
      /* decode bit from duration, calculated to milliseconds */
      if (((u32SignalDuration_us10 + 50) / 100) == 2)
      { u32MessageBuf += ((uint32_t)1 << ((IR_MESSAGE_LENGTH_IN_BIT - 1) - u8MessageBitCounter)); }
      /* else bit was 0, so nothing needs to be done */
      /* check for timeout, if repeat has been triggered or message was interrupted, use previous message */
      if (u32SignalDuration_us10 >= IR_TIMEOUT_DURATION_US10)
      {
        u32MessageBuf = u32OldMessageBuf;
        u8MessageBitCounter = IR_MESSAGE_LENGTH_IN_BIT;
      }
    }
    /* make sure last pulse is not detected */
    while (GET_IR_SIGNAL_VALUE() == 1)
    { }
    /* decode message into address and data bytes */
    pistructIrMessage->u8Address = u32MessageBuf >> 24;
    pistructIrMessage->u8Data = (u32MessageBuf >> 8) & 0x0000FF;
    /* check if message is corrupted, by comparing address and data bytes with their non counterparts, checking if a valid address was used and checking if a timeout was triggered */
    pistructIrMessage->u8Valid = false;
    if ((u32SignalDuration_us10 < IR_TIMEOUT_DURATION_US10) && (pistructIrMessage->u8Address == 0) && (pistructIrMessage->u8Address == (~(u32MessageBuf >> 16) & 0x00FF)) && (pistructIrMessage->u8Data == (~(u32MessageBuf) & 0x000000FF)))
    { pistructIrMessage->u8Valid = true; }
    /* update the old message */
    u32OldMessageBuf = u32MessageBuf;
    /* return no error 0 */
    return 0;
  }
  /* return no message error 1 */
  return 1;
}
