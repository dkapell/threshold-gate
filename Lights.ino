/* Control Light logic
 *  void light(LED_ID, boolean) - turns a light on or off
 *  void initLights() - initialize all lights, call from setup()
 *  void controlLightsDisplay() - set all lights to the calculated brightness, call from loop()
 *  void controlLightsPulse() - calculate pulsing animation for lights, call from loop()
 */
byte controlMaxBrightness = 128;
byte controlMinBrightness = 8;
long controlFadeTime = 2000;
byte controlLightsPins[] = {PIN_RESET_LED, PIN_CLOSE_LED, PIN_PAUSE_LED, PIN_TIME_LED};

boolean controlLights[4]; // light on/off
byte controlLightsBrightness[4]; // current brightness of each light
long controlLightsStartTime; // store start time for the pulse
byte controlLightsIncreasing; // increasing/decreasing

void light(byte pin, boolean enabled){
  controlLights[pin] = enabled;
}


void initLights(){
  for (byte i = 0;i < 4; i++){
    pinMode(controlLightsPins[i], OUTPUT);
    controlLightsBrightness[i] = 0;
  }
}


void controlLightsDisplay(void){
  for (byte i = 0 ; i < 4 ; i++){
    analogWrite(controlLightsPins[i], controlLightsBrightness[i]);
  }
}

void controlLightsPulse(void){
  long now = millis();
  if ((now - controlLightsStartTime) >= controlFadeTime){
    ++controlLightsIncreasing %= 2;
    controlLightsStartTime = now;
  }
  long currentStep = now - controlLightsStartTime;
  
  for (byte i = 0 ; i < 4 ; i++){
    if (controlLights[i]){
      if (controlLightsIncreasing){
        controlLightsBrightness[i] = controlMaxBrightness - (currentStep*(controlMaxBrightness - controlMinBrightness)/controlFadeTime); // fade out
      } else {
        controlLightsBrightness[i] = controlMinBrightness + currentStep*(controlMaxBrightness - controlMinBrightness)/controlFadeTime; // fade in
      }
    } else {
      controlLightsBrightness[i] = 0;
    }
  }
}


