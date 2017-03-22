void stateClosing(){
  if (!stateStarted){
    stateStarted = true;
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundStop();
    soundPlay(SND_GATE_CLOSING, false, 0);
    setGateClockwise(false);
    setGateElements(8);
    setGateAnimation(COMET, getColor(255,32, 32), 60);
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
    timerSetSeconds(0);
    timerStop();
    soundStop();
    soundPlay(SND_GATE_CLOSING_EMERGENCY, false, 0);
    setGateClockwise(false);
    setGateElements(8);
    setGateAnimation(COMET, getColor(255,32, 32), 60);
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  }

  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 4495){
    changeState(STATE_GATE_OFF);
  } 
}

