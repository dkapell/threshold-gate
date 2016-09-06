#include <Adafruit_LEDBackpack.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Wire.h>
#include "thresholdGate.h"

// Main Countdown Timer
long countdownTimer = 0;
// 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();


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
  Serial.begin(9600);

  timerSetSeconds(90);
  timerStart();

  // init 7 segment displays
  matrix.begin(0x70);
}

void loop()
{
  readButtons(); // check the state of all buttons
  runState(); // Run the state machine
  countdown(); // Run the countdown timer
  if (countdownTimer < 1000*10){
    timerAdd(30);
  }
}
