void stateCountdown(){
  if (!stateStarted){
    stateStarted = true;
    timerSetSeconds(10); // should be 300
    timerStart();
    controlLights[LED_RESET] = true;
    controlLights[LED_CLOSE] = false;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = false;
    
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_OPEN)){
    changeState(STATE_OPEN);
  }

  if (timerEnded){
    changeState(STATE_OPENING);
  }
}

void stateOpening(){
  if (!stateStarted){
    stateStarted = true;
    timerSetSeconds(30); // 30*60
    timerStart();
    controlLights[LED_RESET] = true;
    controlLights[LED_CLOSE] = true;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = true; 
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_OPEN)){
    changeState(STATE_OPEN);
  } else if (readButtonPress(BTN_CLOSE)){
    changeState(STATE_CLOSING_EMERGENCY);
  } else if (readButtonPress(BTN_ADD_MIN)){
    timerAdd(60);
  } else if (readButtonPress(BTN_SUB_MIN)){
    timerSubtract(60);
  }


  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 5000){
    changeState(STATE_OPEN);
  }
}
