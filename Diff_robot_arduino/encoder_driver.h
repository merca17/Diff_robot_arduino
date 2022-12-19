/* *************************************************************
   Encoder driver function definitions - by JUAN MERCADO
   ************************************************************ */
   
   
#ifdef DC_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A 3  //pin A8
  #define LEFT_ENC_PIN_B 13  //pin A9
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A 2  //pin 10
  #define RIGHT_ENC_PIN_B 11   //pin 11
#endif
void EncoderInit();
void LEFTwheelSpeed();
void RIGHTwheelSpeed();   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
