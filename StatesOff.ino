/* Initial state
 *  Three second delay to let all components power up
 */
 
void stateInitial(){
  if (!stateStarted){
    stateStarted = true;
    timerStop();
    light(LED_RESET, true);
    light(LED_CLOSE, true);
    light(LED_PAUSE, true);
    light(LED_TIME, true);
    setGateAnimation(WIPE, getColor(128, 128, 128), 3); 
    hideTimeSelect(); 
  }

  if (isAnimationDone()){
    setGateAnimation(WIPE_OFF, 3); 
  }
  
  if ((millis() - stateTimer) > 3000){
    if (checkButtonState(BTN_CLOSE) == LOW){
      changeState(STATE_DEMO);
    } else if (checkButtonState(BTN_PAUSE) == LOW){
      demoMode = true;
    } else {
      changeState(STATE_GATE_OFF);  
    }
  }
}
/* Gate Off
 *  Resting state for the gate
 */
void stateGateOff(){
  if (!stateStarted){
    stateStarted = true;
    timerOff();
    light(LED_RESET, true);
    light(LED_CLOSE, false);
    light(LED_PAUSE, false);
    light(LED_TIME, false);
    soundPlay(SND_GATE_OFF, true, 14100);
    setGateElements(8);
    setGateAnimation(PULSE, getColor(255,0,0));
    showTimeSelect();
    enableTimeSelect();
  }
 
  if (readButtonPress(BTN_RESET)){
    gateType = GATE_MISSION;
    changeState(STATE_COUNTDOWN);
  } else if (readButtonPress(BTN_PAUSE)){
    gateType = GATE_BATTLE;
    changeState(STATE_COUNTDOWN);
  } else if (readButtonPress(BTN_OPEN)){
    timerSetMillis(getTimeSelected()); 
    soundStop();
    changeState(STATE_OPENING);
  }
}

/* Demo State */
byte demoState = 0;
boolean demoCycle = false;

void stateDemo(){
  if (!stateStarted){
    stateStarted = true;
    timerOff();
    light(LED_RESET, false);
    light(LED_CLOSE, false);
    light(LED_PAUSE, true);
    light(LED_TIME, true);
    setGateAnimation(RAINBOW, 20);
    demoCycle = false;
  }
  
  if (readButtonPress(BTN_ADD_MIN)){
    demoState = 0;
    demoCycle = true;
    setGateAnimation(WIPE, getColor(255, 0, 0), 5);
    
  } else if (readButtonPress(BTN_SUB_MIN)){
    demoCycle = false;
    setGateAnimation(COMET, getColor(255, 32, 255), 50);
    
  } else if (readButtonPress(BTN_HQ_PAUSE)){
    demoCycle = false;
    setGateAnimation(RAINBOW, 20);
  }
  
  if (demoCycle && isAnimationDone()){
    demoState = ++demoState % 6;
    switch (demoState){
      case 0: setGateAnimation(WIPE, getColor(255, 0, 0), 5); break;
      case 1: setGateAnimation(WIPE_OFF, 5); break;
      case 2: setGateAnimation(WIPE, getColor(0, 255, 0), 5); break;
      case 3: setGateAnimation(WIPE_OFF, 5); break;
      case 4: setGateAnimation(WIPE, getColor(0, 0, 255), 5); break;
      case 5: setGateAnimation(WIPE_OFF, 5); break;
    }
  }
}
