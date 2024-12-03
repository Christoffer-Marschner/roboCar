#ifndef IR_COMMUNICATION
#define IR_COMMUNICATION

#include "main.hpp"

/*
  ir mappings:
  button | data (hex)
  -------------------
  up     | 62
  right  | C2
  down   | A8
  left   | 22
  ok     | 02
  0      | 4A
  1      | 68
  2      | 98
  3      | B0
  4      | 30
  5      | 18
  6      | 7A
  7      | 10
  8      | 38
  9      | 5A
  *      | 42
  #      | 52
*/

///// MACROS /////
#define IR_MESSAGE_LENGTH_IN_BIT 32 
#define IR_TIMEOUT_DURATION_US10 400 
#define IR_SIGNAL_BIT_IN_B_REG PB4 

#define GET_IR_SIGNAL_VALUE() (!GET_BIT_IN_REG(PINB, IR_SIGNAL_BIT_IN_B_REG) ) 

///// ENUMS /////
enum u8IrCodes_n
{
  irCodeUp    = 0x62,
  irCodeRight = 0xC2,
  irCodeDown  = 0xA8,
  irCodeLeft  = 0x22,
  irCodeOk    = 0x02,
  irCode0 = 0x4A,
  irCode1 = 0x68,
  irCode2 = 0x98,
  irCode3 = 0xB0,
  irCode4 = 0x30,
  irCode5 = 0x18,
  irCode6 = 0x7A,
  irCode7 = 0x10,
  irCode8 = 0x38,
  irCode9 = 0x5A,
  irCodeStar = 0x42,
  irCodeHash = 0x52,
};

///// STRUCTS /////
struct IrMessage_struct
{
  uint8_t u8Address = 0;
  uint8_t u8Data = 0;
  uint8_t u8Valid = false;
};

///// FUNCTION DECLARATIONS /////
/* function to initialize the ir sensor */
uint8_t f_u8InitializeIrSensor();

/* function to check if an ir message is being sent and get it */
uint8_t f_u8GetNewestIrMessage(IrMessage_struct* pistructIrMessage);

#endif