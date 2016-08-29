boolean timerRunning = false;
boolean timerEnded = false;
long timerLast = 0;
long oldSeconds;

// Explicitly set a timer
void timerSetMins(long mins){
  countdownTimer = mins * 60 * 1000;
  oldSeconds = mins * 60;
}

// Add a number of seconds to the timer
void timerAdd(long seconds){
  countdownTimer += (seconds * 1000);
}

//Subtract a number of seconds from the timer
void timerSubtract(long seconds){
  countdownTimer -= (seconds * 1000);
}

// Start/resume the timer
void timerStart(void){
  timerRunning = true;
  timerLast = millis();
  timerEnded = false;
}

//Pause the timer
void timerStop(void){
  timerRunning = false;
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
    byte highMins = countdownTimer / 1000 / 60 / 10;
    byte lowMins = countdownTimer / 1000 / 60 % 10;
    byte highSecs = (countdownTimer / 1000) % 60 / 10;
    byte lowSecs = (countdownTimer / 1000) % 60 % 10;
    Serial.print(highMins);
    Serial.print(lowMins);
    Serial.print(":");
    Serial.print(highSecs);
    Serial.println(lowSecs);
    
   // TODO Display current time on the i2c backpack

  } 
  oldSeconds = seconds;
  
 }

