
#include "lightSensor.hpp" 

uint8_t u8LightSensorsInitialized = false;

///// LIGHT SENSOR CLASS /////
/* read a light sensor */
uint8_t c_LightSensor::f_u8GetValue()
{
  /* return the bit value in the pin register */
  return GET_BIT_IN_REG(*(pu8SignalDDRegister-1), u8SignalBit);
}

/* initiate the light sensor */
c_LightSensor::c_LightSensor(uint8_t* ipu8SignalDDRegister, uint8_t iu8SignalBit)
{
  /* set the private register and pin variable */
  pu8SignalDDRegister = ipu8SignalDDRegister;
  u8SignalBit = iu8SignalBit;
  /* set the light sensor pins as inputs */
  UNSET_BIT_IN_REG(*pu8SignalDDRegister, u8SignalBit);
}
   
///// FUNCITONS /////
/* function to initiate the light sensors */
uint8_t f_u8InitializeLightSensors()
{
  /* set the light sensor pins as inputs */
  UNSET_BIT_IN_REG(DDRB, LIGHT_SENSOR_LEFT_BIT_POS_B_REG);
  UNSET_BIT_IN_REG(DDRD, LIGHT_SENSOR_MIDDLE_BIT_POS_D_REG);
  UNSET_BIT_IN_REG(DDRD, LIGHT_SENSOR_RIGHT_BIT_POS_D_REG);
  /* set status variable */
  u8LightSensorsInitialized = true;
  /* return no errors 0 */
  return 0;
}

/* function to read a light sensor */
uint8_t f_u8GetLightSensorValue(u8LightSensorPosition_n iu8WantedPosition)
{
  /* if not initialized return error 2 */
//  if (u8LightSensorsInitialized == false)
//    return 2;
  /* check rthe wanted position to read at */
  switch (iu8WantedPosition)
  {
    /* if position invalid return error 3 */
    default:
      return 3;
    /* return the light sensor at wanted position */
    case leftSensor:
      return GET_BIT_IN_REG(PINB, LIGHT_SENSOR_LEFT_BIT_POS_B_REG);
    case middleSensor:
      return GET_BIT_IN_REG(PIND, LIGHT_SENSOR_MIDDLE_BIT_POS_D_REG);
    case rightSensor:
      return GET_BIT_IN_REG(PIND, LIGHT_SENSOR_RIGHT_BIT_POS_D_REG);
  }
}







































