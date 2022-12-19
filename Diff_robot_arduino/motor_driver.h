/***************************************************************
   Motor driver function definitions - by Juan Mercado
   *************************************************************/

#ifdef IBT_2_MOTOR_DRIVER
  #define LEFT_MOTOR_FORWARD   6   // RPWM_PIN_IZQ
  #define LEFT_MOTOR_BACKWARD  5    // LPWM_PIN_IZQ
  #define LEFT_MOTOR_ENABLE    4      // EN_PIN_IZQ

  #define RIGHT_MOTOR_FORWARD  8    // RPWM_PIN_DER
  #define RIGHT_MOTOR_BACKWARD 9     // LPWM_PIN_DER
  #define RIGHT_MOTOR_ENABLE   12     // EN_PIN_DER

  #define R_EXTERNAL    390 // ohm
  #define R_INTERNAL  10000 // ohm
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
