#include <Adafruit_Soundboard.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

// Common defines
#include "thresholdGate.h"

void setup()
{
  // Initialize Lights
  initLights();
  
  // Initialize Buttons
  initButtons();  

  // Start Serial output
  //Serial.begin(9600);

  // init 7 segment displays
  initTimer();

  initSound();
}

void loop()
{
  readButtons(); // check the state of all buttons
  runState(); // Run the state machine
  countdown(); // Run the countdown timer
  controlLightsPulse(); // calculate button lights pulse
  controlLightsDisplay(); // turn on lights
  loopSound();  // loop active sound
}
