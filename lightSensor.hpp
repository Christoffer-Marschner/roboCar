#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "main.hpp" 

///// MACROS /////
#define LIGHT_SENSOR_LEFT_BIT_POS_B_REG PB2 
#define LIGHT_SENSOR_MIDDLE_BIT_POS_D_REG PD4 
#define LIGHT_SENSOR_RIGHT_BIT_POS_D_REG PD2 

///// ENUMS /////
enum u8LightSensorPosition_n
{
  leftSensor,
  middleSensor,
  rightSensor
};

///// CLASSES /////
class c_LightSensor
{
  private: 
    uint8_t* pu8SignalDDRegister;  
    uint8_t u8SignalBit;  
  public:
    c_LightSensor(uint8_t* ipu8SignalDDRegister, uint8_t iu8SignalBit);
    uint8_t f_u8GetValue();
};
   
///// FUNCTION DECLARATIONS /////
/* function to read a light sensor */
uint8_t f_u8GetLightSensorValue(u8LightSensorPosition_n iu8WantedPosition);

/* function to initiate the light sensors */
uint8_t f_u8InitializeLightSensors();

#endif
