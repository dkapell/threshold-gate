/* Initial state
 *  Three second delay to let all components power up
 */
void stateInitial(){
  if (!stateStarted){
    stateStarted = true;
  }
  
  //Transistion out after 3 seconds
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
  }
}

