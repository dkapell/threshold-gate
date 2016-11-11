#include <Adafruit_Soundboard.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Wire.h>

// Common defines
#include "thresholdGate.h"

// Demo mode
boolean demoMode = false;

void setup()
{
  // Initialize Lights
  initLights();
  
  // Initialize Buttons
  initButtons();  
  
  // init 7 segment displays
  initTimer();

  // init Gate lights
  initGate();

  // init sound card
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
  displayGate(); // Run gate lights animations
}
