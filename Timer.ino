boolean timerRunning = false;
boolean timerDisplay = false;
long timerLast = 0;
long oldSeconds;

int timerDelta = 0;
int timerDeltaMax = 5 * 60;
int timerDeltaMin = -5 * 60;

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
    }
    timerLast = now;
  }
  long seconds = countdownTimer / 1000;
  if (oldSeconds != seconds) {
    displayTime(seconds);
    //printTime(seconds);
  } 
  oldSeconds = seconds;
  
 }


void printTime(long seconds){
  byte highMins = countdownTimer / 1000 / 60 / 10;
  byte lowMins = countdownTimer / 1000 / 60 % 10;
  byte highSecs = (countdownTimer / 1000) % 60 / 10;
  byte lowSecs = (countdownTimer / 1000) % 60 % 10;
  Serial.print(highMins);
  Serial.print(lowMins);
  Serial.print(":");
  Serial.print(highSecs);
  Serial.println(lowSecs);
}
void displayTime(long seconds){
  if(timerDisplay){
    byte highMins = countdownTimer / 1000 / 60 / 10;
    byte lowMins = countdownTimer / 1000 / 60 % 10;
    byte highSecs = (countdownTimer / 1000) % 60 / 10;
    byte lowSecs = (countdownTimer / 1000) % 60 % 10;
    matrix.writeDigitNum(0,highMins, false);
    matrix.writeDigitNum(1,lowMins, false);
    matrix.drawColon(true);
    matrix.writeDigitNum(3,highSecs, false);
    matrix.writeDigitNum(4,lowSecs, false);
    matrix.writeDisplay();
  }
}

