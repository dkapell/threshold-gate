/* Initial state
 *  Three second delay to let all components power up
 */
void stateInitial(){
  if (!stateStarted){
    stateStarted = true;
    timerStop();
    controlLights[LED_RESET] = false;
    controlLights[LED_CLOSE] = false;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = false;
  }
  
  //Transistion out after 1 seconds
  if ((millis() - stateTimer) > 1000){
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
    controlLights[LED_RESET] = true;
    controlLights[LED_CLOSE] = false;
    controlLights[LED_PAUSE] = false;
    controlLights[LED_TIME] = false;
    
  }
 
  if (readButtonPress(BTN_RESET)){
    changeState(STATE_COUNTDOWN);
  } else if (readButtonPress(BTN_OPEN)){
    changeState(STATE_OPEN);
  }

  //Transistion out after 5 seconds  REMOVE THIS
  if ((millis() - stateTimer) > 5000){
    changeState(STATE_COUNTDOWN);  
  }
}

