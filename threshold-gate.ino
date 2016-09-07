#include <Adafruit_LEDBackpack.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Wire.h>
#include "thresholdGate.h"

// Main Countdown Timer
long countdownTimer = 0;
boolean timerEnded = false;

// 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();


void setup()
{
  //Init i2c library
  Wire.begin();
    
  // Set LED pins to output mode
  initLights();
  
  // turn on internal resistors for inputs
  initButtons();  

  // Start Serial output
  Serial.begin(9600);

  // init 7 segment displays
  matrix.begin(0x70);
}

void loop()
{
  readButtons(); // check the state of all buttons
  runState(); // Run the state machine
  countdown(); // Run the countdown timer
  controlLightsPulse();
  controlLightsDisplay(); 
}
