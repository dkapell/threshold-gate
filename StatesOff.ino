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
  }

  if (isAnimationDone()){
    setGateAnimation(WIPE_OFF, 3); 
  }
  //Transistion out after 2 seconds
  if ((millis() - stateTimer) > 3000){
    changeState(STATE_GATE_OFF);  
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
    setGateAnimation(PULSE, getColor(255,0,0));
  }
 
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_COUNTDOWN);
  } else if (readButtonPress(BTN_OPEN)){
   if (demoMode){
      timerSetSeconds(30); // 30*60
    } else {
      timerSetSeconds(30*60); // 30 mins 
    }
    changeState(STATE_OPEN);
  }

  //Transistion out after 10 seconds in demo mode
  if (demoMode && (millis() - stateTimer) > 5000){
    changeState(STATE_COUNTDOWN);  
  }
}

