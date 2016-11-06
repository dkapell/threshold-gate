/* Countdown timer and display logic
 *  void initTimer() - Initialize timer, call from setup()
 *  void countdown() - run countdown, call from loop()
 *  void timerSetSeconds(long) - set the timer to a specific number of seconds
 *  void timerAdd(seconds) - add a number of seconds to the timer, up to timerDeltaMax
 *  void timerSubtract(seconds) - subtract a number of seconds from the timer, down to timerDeltaMin
 *  void timerStart() - start the countdown, turn on display
 *  void timerStop() - pause the countdown
 *  void timerOff() - turn off the display, set timer to 0
 *  boolean isTimerEnded() - determine if the countdown has reached zero.  Will only return true once
 *  void blinkColon() - internal function to blink the colon 2x second
 *  void displayTime(seconds) - internal function to display the timer
 *  void printTime(seconds) - internal function to print the timer on Serial
 */
 
// 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();

int timerDeltaMax = 5 * 60;
int timerDeltaMin = -5 * 60;

boolean timerRunning = false;
boolean timerDisplay = false;
boolean timerEnded = false;
long countdownTimer = 0;
long timerLast = 0;
long oldSeconds;
int timerDelta = 0;

void initTimer(void){
   matrix.begin(0x70);
   //Wire.setClock(1000);
}

// Explicitly set a timer
void timerSetSeconds(long seconds){
  countdownTimer = seconds * 1000;
  oldSeconds = seconds;
  displayTime(seconds);
  timerDelta = 0;
}

// Add a number of seconds to the timer
void timerAdd(long seconds){
  if (timerDelta + seconds <= timerDeltaMax){ 
    countdownTimer += (seconds * 1000);
    timerDelta += seconds;
  }
}

//Subtract a number of seconds from the timer
void timerSubtract(long seconds){
  if (timerDelta - seconds >= timerDeltaMin){ 
    countdownTimer -= (seconds * 1000);
    timerDelta -= seconds;
  }
}

// Start/resume the timer
void timerStart(void){
  timerRunning = true;
  timerLast = millis();
  timerEnded = false;
  timerDisplay = true;
}

//Pause the timer
void timerStop(void){
  timerRunning = false;
  if(timerDisplay && countdownTimer > 0){
    blinkColon();
  }
}

void timerOff(void){
  timerRunning = false;
  timerSetSeconds(0);
  timerDisplay = false;
  matrix.clear();
  matrix.writeDisplay();
}

// Run the timer
void countdown(void){
  if (timerRunning){
    
    long now = millis();
    countdownTimer -= (now - timerLast);
    if (countdownTimer <= 0){
      timerRunning = false;
      timerEnded = true;
      countdownTimer = 0;
    }
    timerLast = now;
  }
  long seconds = (countdownTimer + 999) / 1000 ;
  if (oldSeconds != seconds) {
    displayTime(seconds);
    //printTime(seconds);
  } 
  oldSeconds = seconds;
  if(timerDisplay && !timerRunning && countdownTimer > 0){
    blinkColon();
  }
}

void blinkColon(){
  if (millis()/500 % 2 == 0){
    matrix.drawColon(true); 
  } else {
    matrix.drawColon(false);
  }
  matrix.writeDisplay();
}

void showColon(){
  matrix.drawColon(true);
  matrix.writeDisplay();
}

void printTime(long seconds){
  byte highMins = seconds / 60 / 10;
  byte lowMins = seconds / 60 % 10;
  byte highSecs = seconds % 60 / 10;
  byte lowSecs = seconds % 60 % 10;
  Serial.print(highMins);
  Serial.print(lowMins);
  Serial.print(":");
  Serial.print(highSecs);
  Serial.println(lowSecs);
}

void displayTime(long seconds){
  if(timerDisplay){
    byte highMins = seconds / 60 / 10;
    byte lowMins = seconds / 60 % 10;
    byte highSecs = seconds % 60 / 10;
    byte lowSecs = seconds % 60 % 10;
    matrix.writeDigitNum(0,highMins, false);
    matrix.writeDigitNum(1,lowMins, false);
    matrix.drawColon(true); 
    matrix.writeDigitNum(3,highSecs, false);
    matrix.writeDigitNum(4,lowSecs, false);
    matrix.writeDisplay();
  }
}

boolean isTimerEnded(void){
  if (timerEnded){
    timerEnded = false;
    return true;
  } else {
    return false;
  }
}

