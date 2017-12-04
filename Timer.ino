/* Countdown timer and display logic
 *  void initTimer() - Initialize timer, call from setup()
 *  void timerLoop() - run countdown, call from loop()
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
Adafruit_7segment mainTimer = Adafruit_7segment();
Adafruit_7segment inputTimer = Adafruit_7segment();

int timerDeltaMax = 5 * 60;
int timerDeltaMin = -5 * 60;

boolean timerRunning = false;
boolean timerDisplay = false;
boolean timerEnded = false;
long millisRemaining = 0;
long timerLast = 0;
long oldSeconds;
int timerDelta = 0;

long timeSelected = 1800000;
byte lastDialState = 0;
long lastDialTime = 0;
boolean selectDisplay = true;
boolean enableSelect = false;

void initTimer(void){
   mainTimer.begin(0x70);
   inputTimer.begin(0x71);
   inputTimer.setBrightness(7);
}

// Explicitly set a timer
void timerSetSeconds(long seconds){
  if (seconds == -1){
    millisRemaining = -1;
  } else {
    millisRemaining = seconds * 1000;
  }
  oldSeconds = seconds;
  displayTime(millisRemaining);
  timerDelta = 0;
}

void timerSetMillis(long ms){
  millisRemaining = ms;
  if (ms > 0){
    oldSeconds = floor(ms/1000);
  }
  displayTime(millisRemaining);
  timerDelta = 0;
}


// Add a number of seconds to the timer
void timerAdd(long seconds){
  if (timerDelta + seconds <= timerDeltaMax){ 
    millisRemaining += (seconds * 1000);
    timerDelta += seconds;
  }
}

//Subtract a number of seconds from the timer
void timerSubtract(long seconds){
  if (timerDelta - seconds >= timerDeltaMin){ 
    millisRemaining -= (seconds * 1000);
    timerDelta -= seconds;
  }
}

// Start/resume the timer
void timerStart(void){
  timerEnded = false;
  timerDisplay = true;
  
  if (millisRemaining == -1){
    displayTime(millisRemaining);
    //printTime(millisRemaining);
    timerRunning = false;
  } else {
    timerRunning = true;
    timerLast = millis();
  }  
}

//Pause the timer
void timerStop(void){
  timerRunning = false;
  if(timerDisplay && millisRemaining > 0){
    blinkColon();
  }
}

void timerOff(void){
  timerRunning = false;
  timerSetSeconds(0);
  timerDisplay = false;
  mainTimer.clear();
  mainTimer.writeDisplay();
}

void showTimeSelect(void){
  selectDisplay = true;
  displayTime(inputTimer, timeSelected);
}

void hideTimeSelect(void){
  selectDisplay = false;
  inputTimer.clear();
  inputTimer.writeDisplay();
}

void enableTimeSelect(void){
  enableSelect = true;
}

void disableTimeSelect(void){
  enableSelect = false;
}
// Run the timer
void timerLoop(void){
  if (enableSelect){
    readTime();
    
  } else if (selectDisplay){
    displayTime(inputTimer, timeSelected, true);
  }
  
  if (millisRemaining >= 0){
    if (timerRunning){
      long now = millis();
      millisRemaining -= (now - timerLast);
      if (millisRemaining <= 0){
        timerRunning = false;
        timerEnded = true;
        millisRemaining = 0;
      }
      timerLast = now;
    }

    long seconds = (millisRemaining) / 1000 ;
    if (seconds < 60){
      seconds = millisRemaining / 10;
    }  
    if (oldSeconds != seconds && timerDisplay) {
      displayTime(millisRemaining);
      //printTime(millisRemaining);
    } 
    oldSeconds = seconds;
    
    if(timerDisplay && !timerRunning && millisRemaining > 0){
      blinkColon();
    }
  }
}

void readTime(void){
  long timeInputRaw = analogRead(PIN_TIME_SELECT);
  long timeBucket = map(timeInputRaw,0,1023,0,13);
  long newTimeSelected;
  
    // if value has changed, reset timer
    if (timeBucket != lastDialState){
      lastDialTime = millis();
    }
    
    // if we've been stable for more than the debounce, save the value
    if ((millis() - lastDialTime)  > 30){
        long newTimeSelected;
        if (timeBucket >= 12){
          newTimeSelected = -1;
        } else {
          newTimeSelected = (300 + (300 * timeBucket)) * 1000;
        }
        if (newTimeSelected != timeSelected && selectDisplay){
          displayTime(inputTimer, newTimeSelected);
        }
       
        timeSelected = newTimeSelected;
    }
    lastDialState = timeBucket;
} 

void blinkColon(void){
  return blinkColon(mainTimer);
}

void blinkColon(Adafruit_7segment matrix){
  if (millis()/500 % 2 == 0){
    matrix.drawColon(true); 
  } else {
    matrix.drawColon(false);
  }
  matrix.writeDisplay();
}

void showColon(void){
  return showColon(mainTimer);
}

void showColon(Adafruit_7segment matrix){
  matrix.drawColon(true);
  matrix.writeDisplay();
}

void printTime(long time){
  if (time == -1){
    Serial.println("Infinity");
  } else {
    byte highMins, lowMins, highSecs, lowSecs;
      long seconds;
      if (time > 60000){
        seconds = (time + 999) / 1000 ; 
        highMins = seconds / 60 / 10;
        lowMins = seconds / 60 % 10;
        highSecs = seconds % 60 / 10;
        lowSecs = seconds % 60 % 10;
      } else {
        seconds = (time + 9) / 10;
        highMins = seconds / 100 / 10;
        lowMins = seconds / 100 % 10;
        highSecs = seconds % 100 / 10;
        lowSecs = seconds % 100 % 10;
      }
    Serial.print(highMins);
    Serial.print(lowMins);
    Serial.print(":");
    Serial.print(highSecs);
    Serial.println(lowSecs);
  }
}

void displayTime(long time){
  return displayTime(mainTimer, time, false);
}

void displayTime(Adafruit_7segment matrix, long time){
  return displayTime(matrix, time, false);
}

void displayTime(Adafruit_7segment matrix, long time, boolean blink){
  if (time == -1){
    matrix.clear();
    matrix.drawColon(false);
    matrix.writeDigitRaw(1, B00000110);
    matrix.writeDigitRaw(3, B01010100);
    matrix.writeDigitRaw(4, B01110001);
  } else {
    byte highMins, lowMins, highSecs, lowSecs;
    long seconds;
    
    if (time > 60000){
      seconds = (time + 999) / 1000 ; 
      highMins = seconds / 60 / 10;
      lowMins = seconds / 60 % 10;
      highSecs = seconds % 60 / 10;
      lowSecs = seconds % 60 % 10;
    } else {
      seconds = (time ) / 10;
      highMins = seconds / 100 / 10;
      lowMins = seconds / 100 % 10;
      highSecs = seconds % 100 / 10;
      lowSecs = seconds % 100 % 10;
    }
    matrix.writeDigitNum(0,highMins, false);
    matrix.writeDigitNum(1,lowMins, false);
    matrix.writeDigitNum(3,highSecs, false);
    matrix.writeDigitNum(4,lowSecs, false);
    if (blink){
      if (millis()/500 % 2 == 0){
        matrix.drawColon(true); 
      } else {
        matrix.drawColon(false);
      }
    } else {  
      matrix.drawColon(true); 
    }
  }
  matrix.writeDisplay();
}

boolean isTimerEnded(void){
  if (timerEnded){
    timerEnded = false;
    return true;
  } else {
    return false;
  }
}

long getTimeSelected(void){
  return timeSelected;
}


