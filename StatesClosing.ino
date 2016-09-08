void stateClosing(){
  if (!stateStarted){
    stateStarted = true;
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundStop();
    //soundPlay(SND_GATE_CLOSING, false, 0);
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
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundStop();
    //soundPlay(SND_GATE_CLOSING_EMERGENCY, false, 0);
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  }

  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 2000){
    changeState(STATE_GATE_OFF);
  } 
}
