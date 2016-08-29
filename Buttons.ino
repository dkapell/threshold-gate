byte buttonPins[] = {PIN_RESET, PIN_ADD_MIN, PIN_SUB_MIN, PIN_PAUSE, PIN_OPEN, PIN_HQ_PAUSE, PIN_CLOSE};
byte buttonStates[7];
byte lastButtonStates[7];
long lastButtonTimes[7];
long buttonDebounceDelay = 50;

// Initalize a single input
void setInput(byte pin){
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

// Read all buttons, can check state in buttonStats(BTN_X)
void readButtons(){
  for (byte i = 0;i < 7; i++){
    int reading = digitalRead(buttonPins[i]);
    // if value has changed, reset timer
    if (reading != lastButtonStates[i]){
      lastButtonTimes[i] = millis();
    }
    
    // if we've been stable for more than the debounce, save the value
    if ((millis() - lastButtonTimes[i])  > buttonDebounceDelay){
      if (reading != buttonStates[i]){
        buttonStates[i] = reading;    
      }
    }
    // save value for next loop
    lastButtonStates[i] = reading;
  }
}

