boolean countDownSoundStarted = false;
void stateCountdown(){
  if (!stateStarted){
    stateStarted = true;
    if (demoMode){
      timerSetSeconds(20); 
    } else {
      timerSetSeconds(5 * 60); // 5 minutes
    }
    timerStart();
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundStop();
    soundPlay(SND_COUNTDOWN_START, false, 0);
    countDownSoundStarted = false;
  }
  
  if ((millis() - stateTimer) > 3363 && !countDownSoundStarted){
    soundPlay(SND_GATE_OFF, true, 14100);
    countDownSoundStarted = true;
  }
  
  if (readButtonPress(BTN_RESET)){
    soundStop();
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_OPEN)){
    if (demoMode){
      timerSetSeconds(30); // 30*60
    } else {
      timerSetSeconds(30*60); // 30 mins 
    }
    changeState(STATE_OPEN);
  }

  if (isTimerEnded()){
    changeState(STATE_OPENING);
  }
}

void stateOpening(){
  if (!stateStarted){
    stateStarted = true;
    if (demoMode){
      timerSetSeconds(30); 
    } else {
      timerSetSeconds(30*60); // 30 mins 
    }
    timerStart();
    light(LED_RESET, true);
    light(LED_CLOSE, true);
    light(LED_PAUSE, false);
    light(LED_TIME, true);
    soundStop();
    soundPlay(SND_GATE_OPENING, false, 0);
    setGateAnimation(COMET, getColor(255,255, 255), 60);
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_OPEN)){
    if (demoMode){
      timerSetSeconds(10); 
    } else {
      timerSetSeconds(300);
    }
    changeState(STATE_OPEN);
  } else if (readButtonPress(BTN_CLOSE)){
    changeState(STATE_CLOSING_EMERGENCY);
  } else if (readButtonPress(BTN_ADD_MIN)){
    timerAdd(60);
  } else if (readButtonPress(BTN_SUB_MIN)){
    timerSubtract(60);
  }


  //Transistion out after 5 seconds of opening animation
  if ((millis() - stateTimer) > 10000){
    changeState(STATE_OPEN);
  }
}
