/* Main State Machine
 *  void changeState(state) - changes state to the specified
 *  void runstate() - runs the current state, call from loop();
 */

byte state = STATE_INITIAL;
boolean stateStarted = false;
long stateTimer = 0;
byte oldState = 0;

void changeState(byte newState){
  Serial.print("Changing state from ");
  Serial.print(state);
  Serial.print(" to ");
  Serial.println(newState);
  oldState = state;
  state = newState;
  stateStarted = false;
  stateTimer = millis();
  
}

void runState(){
  switch(state){
    case STATE_INITIAL:           stateInitial();           break;
    case STATE_GATE_OFF:          stateGateOff();           break;
    case STATE_COUNTDOWN:         stateCountdown();         break;
    case STATE_OPENING:           stateOpening();           break;
    case STATE_OPEN:              stateOpen();              break;
    case STATE_PAUSED:            statePaused();            break;
    case STATE_CLOSING:           stateClosing();           break;
    case STATE_CLOSING_EMERGENCY: stateClosingEmergency();  break;
    default:
      state = STATE_GATE_OFF;
  }
}

