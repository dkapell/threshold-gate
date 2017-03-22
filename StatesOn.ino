void stateOpen(){
  if (!stateStarted){
    stateStarted = true;
    timerStart();
    light(LED_RESET, true);
    light(LED_CLOSE, true);
    light(LED_PAUSE, true);
    light(LED_TIME, true);
    soundPlay(SND_GATE_OPEN, true, 5000);
    switch(gateType){
      case GATE_MISSION:
        setGateElements(2);
        setGateClockwise(true);
        setGateAnimation(SPIN, getColor(0,255,0), 50);
        break;
          
      case GATE_BATTLE:
        setGateElements(4);
        setGateClockwise(false);
        setGateAnimation(SPIN, getColor(0,0,255), 50);
        break;
      
      case GATE_TRANSIT:
        setGateElements(8);
        setGateClockwise(true);
        setGateAnimation(DOUBLE_SPIN, getColor(128,128,255), getColor(128,255, 128), 50);
        break;
    }
        
    hideTimeSelect();
  }
  
  if (readButtonPress(BTN_RESET)){
    soundStop();
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_CLOSE)){
    changeState(STATE_CLOSING_EMERGENCY);
  } else if (readButtonPress(BTN_ADD_MIN)){
    timerAdd(60);
  } else if (readButtonPress(BTN_SUB_MIN)){
    timerSubtract(60);
  } else if (readButtonPress(BTN_PAUSE)){
    changeState(STATE_PAUSED);
  } else if (readButtonPress(BTN_HQ_PAUSE)){
    changeState(STATE_PAUSED);
  }
  
  if (isTimerEnded()){
    changeState(STATE_CLOSING);
  }
}

void statePaused(){
  if (!stateStarted){
    stateStarted = true;
    timerStop();
    light(LED_RESET, true);
    light(LED_CLOSE, true);
    light(LED_PAUSE, true);
    light(LED_TIME, true);
  }
  
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_GATE_OFF);
  } else if (readButtonPress(BTN_CLOSE)){
    changeState(STATE_CLOSING_EMERGENCY);
  } else if (readButtonPress(BTN_ADD_MIN)){
    timerAdd(60);
  } else if (readButtonPress(BTN_SUB_MIN)){
    timerSubtract(60);
  } else if (readButtonPress(BTN_PAUSE)){
    changeState(STATE_OPEN);
  } else if (readButtonPress(BTN_HQ_PAUSE)){
    changeState(STATE_OPEN);
  }
}
