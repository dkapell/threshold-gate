#include <Wire.h>
#include "thresholdGate.h"


void setup()
{
  //Init i2c library
  Wire.begin();
    
  // Set LED pins to output mode
  pinMode(PIN_RESET_LED, OUTPUT);
  pinMode(PIN_CLOSE_LED, OUTPUT);
  pinMode(PIN_PAUSE_LED, OUTPUT);
  pinMode(PIN_TIME_LED, OUTPUT);

  // turn on internal resistors for inputs
  setInput(PIN_RESET);
  setInput(PIN_ADD_MIN);
  setInput(PIN_SUB_MIN);
  setInput(PIN_PAUSE);
  setInput(PIN_HQ_PAUSE);
  setInput(PIN_OPEN);
  setInput(PIN_CLOSE);
  
}

void loop()
{

  runState(); // Run the state machine
}
