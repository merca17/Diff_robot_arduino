/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINK & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT0_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINB & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#elif defined(DC_ENC_COUNTER)
//The sample code for driving one way motor encoder
// encoder 0 izquierda
  const byte encoder0pinA = LEFT_ENC_PIN_A ;//
  const byte encoder0pinB = LEFT_ENC_PIN_B;//B pin -> the digital pin 4
  byte encoder0PinALast;
  int enc0duration;//the number of the pulses
  boolean enc0Direction;//the rotation direction
  //encoder 1 derecha
  const byte encoder1pinA = RIGHT_ENC_PIN_A ;//
  const byte encoder1pinB = LEFT_ENC_PIN_B;//B pin -> the digital pin 4
  byte encoder1PinALast;
  int enc1duration;//the number of the pulses
  boolean enc1Direction;//the rotation direction
  
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
 
  //EncoderInit();//Initialize the module
  
  void EncoderInit()
  {
    enc0Direction = true;//default -> Forward
    enc1Direction = true;
    enc0duration = 0;
    enc1duration = 0;
    pinMode(encoder0pinB,INPUT);
    pinMode(encoder1pinB,INPUT);
    //attachInterrupt(digitalPinToInterrupt(pinA), encoder, FALLING );
    attachInterrupt(digitalPinToInterrupt(encoder0pinA), LEFTwheelSpeed, CHANGE);//int.0
    attachInterrupt(digitalPinToInterrupt(encoder1pinA), RIGHTwheelSpeed, CHANGE);//int.0
  }
  
  void LEFTwheelSpeed()
  {
    int Lstate = digitalRead(encoder0pinA);
    static uint8_t enc_last=0;
    enc_last <<=2; //shift previous state two places
    enc_last |= (PINE & (1 << PE4)) >> 2; //read the current state into lowest 2 bits
  
    left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
    if((encoder0PinALast == LOW) && Lstate==HIGH)
    {
      int val = digitalRead(encoder0pinB);
      if(val == LOW && enc0Direction)
      {
        enc0Direction = false; //Reverse
      }
     else if(val == HIGH && !enc0Direction)
      {
        enc0Direction = true;  //Forward
      }
    }
    encoder0PinALast = Lstate;
  
    if(!enc0Direction)  enc0duration++;
    else  enc0duration--;
  }
  
  void RIGHTwheelSpeed()
  {
    static uint8_t enc_last=0;       
    enc_last <<=2; //shift previous state two places
    enc_last |= (PINE & (1 << PE5)) >> 2; //read the current state into lowest 2 bits
    right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
    
    int Lstate = digitalRead(encoder1pinA);
    if((encoder1PinALast == LOW) && Lstate==HIGH)
    {
      int val = digitalRead(encoder1pinB);
      if(val == LOW && enc1Direction)
      {
        enc1Direction = false; //Reverse
      }
      else if(val == HIGH && !enc1Direction)
      {
        enc1Direction = true;  //Forward
      }
    }
    encoder1PinALast = Lstate;
  
    if(!enc1Direction)  enc1duration++;
    else  enc1duration--;
  }
    /* Wrap the encoder reading function */
    long readEncoder(int i) {
      if (i == LEFT) return -(left_enc_pos);
      else return right_enc_pos;
      //if (i == LEFT) return enc0duration;
      //else return enc1duration;
    }
  
    /* Wrap the encoder reset function */
    void resetEncoder(int i) {
      if (i == LEFT){
        enc0duration = 0;
        left_enc_pos=0L;
        return;
      } else { 
        enc1duration = 0;
        right_enc_pos=0L;
        return;
      }
    }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif
