/* Button debounce and read logic
 *  void initButtons() - Initialize all buttons, call from setup()
 *  void readButtons() - Read button state with debounce, call from loop()
 *  boolean readButtonPress(BTN_ID) - check if a buton has been pressed.  Will return true once per press
 *  byte checkButtonState(BTN_ID) - get the current debounced value of the input
 */

byte buttonPins[] = {PIN_RESET, PIN_ADD_MIN, PIN_SUB_MIN, PIN_PAUSE, PIN_OPEN, PIN_HQ_PAUSE, PIN_CLOSE};
byte lastButtonStates[7];
long lastButtonTimes[7];
long buttonDebounceDelay = 50;

// Current state of each button
byte buttonStates[7];

// Boolean if button is pressed or not, read value then set to false to only trigger once per press
boolean buttonPressed[7];

void initButtons(){
  for (byte i = 0;i < 7; i++){
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
    buttonPressed[i] = false;
  }
}

// Read all buttons
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
        if(reading == LOW){
          buttonPressed[i] = true;    
        } else {
          buttonPressed[i] = false;
        }
      }
    }
    // save value for next loop
    lastButtonStates[i] = reading;
  }
}

// Check if button is pressed.  Will only return true once per press
boolean readButtonPress(byte button){
  if (buttonPressed[button]){
    buttonPressed[button] = false;
    return true;
  } else {
    return false;
  }
}

// get the current state of a button
byte checkButtonState(byte button){
  return buttonStates[button];
}


