void stateClosing(){
  if (!stateStarted){
    stateStarted = true;
    controlLights[LED_RESET] = true;
    controlLights[LED_CLOSE] = false;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = false; 
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  }

  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 5000){
    changeState(STATE_GATE_OFF);
  } 
}

void stateClosingEmergency(){
  if (!stateStarted){
    stateStarted = true;
    controlLights[LED_RESET] = true;
    controlLights[LED_CLOSE] = false;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = false; 
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  }

  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 2000){
    changeState(STATE_GATE_OFF);
  } 
}
