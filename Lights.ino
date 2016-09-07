byte controlMaxBrightness = 128;
byte controlMinBrightness = 8;
long controlFadeTime = 2000;
byte controlLightsPins[] = {PIN_RESET_LED, PIN_CLOSE_LED, PIN_PAUSE_LED, PIN_TIME_LED};
byte controlLightsBrightness[4];
long controlLightsStartTime;
byte controlLightsState;

// Set these to turn on/off lights
boolean controlLights[4];

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
    ++controlLightsState %= 2;
    controlLightsStartTime = now;
  }
  long currentStep = now - controlLightsStartTime;
  
  for (byte i = 0 ; i < 4 ; i++){
    if (controlLights[i]){
      if (controlLightsState){
        controlLightsBrightness[i] = controlMaxBrightness - (currentStep*(controlMaxBrightness - controlMinBrightness)/controlFadeTime); // fade out
      } else {
        controlLightsBrightness[i] = controlMinBrightness + currentStep*(controlMaxBrightness - controlMinBrightness)/controlFadeTime; // fade in
      }
    } else {
      controlLightsBrightness[i] = 0;
    }
  }
}
