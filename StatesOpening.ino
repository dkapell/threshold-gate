void stateCountdown(){
  if (!stateStarted){
    stateStarted = true;
    timerSetSeconds(20); // should be 300
    timerStart();
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundStop();
    soundPlay(SND_COUNTDOWN_START, false, 0);
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_OPEN)){
    changeState(STATE_OPEN);
  }

  if (isTimerEnded()){
    changeState(STATE_OPENING);
  }
}

void stateOpening(){
  if (!stateStarted){
    stateStarted = true;
    timerSetSeconds(30); // 30*60
    timerStart();
    light(LED_RESET, true);
    light(LED_CLOSE, true);
    light(LED_PAUSE, false);
    light(LED_TIME, true);
    soundPlay(SND_GATE_OPENING, false, 0);
    setGateAnimation(COMET, getColor(255,255, 255), 60);
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
  if ((millis() - stateTimer) > 2745){
    changeState(STATE_OPEN);
  }
}
