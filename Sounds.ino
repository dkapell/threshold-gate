Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial, NULL, PIN_SOUND_RST);

boolean soundEnabled = false;

boolean trackLooping = false;
int currentTrack;
long trackStarted;
long currentTrackLength;

void initSound(){
  Serial.begin(9600);
  if (DEBUG){
   soundEnabled = false;
  } else if (sfx.reset()) {
    soundEnabled = true;
  } else {
    Serial.println("No SFX found");
    soundEnabled = false;
    
  }
}

void soundPlay(int track, boolean loopSound, long loopLength ){
  if (soundEnabled){
    trackStarted = millis();
    //sfx.stop();
    sfx.playTrack(track);
    trackLooping = loopSound;
    currentTrack = track;
    currentTrackLength = loopLength;
    
  } else {
    Serial.print("Would ");
    if (loopSound){
      Serial.print("loop ");
    } else {
      Serial.print("play ");
    }
    Serial.print("track ");
    Serial.println(track);
  }
}

void soundStop(void){
  trackLooping = false;
  sfx.stop();
  delay(100);
}

void loopSound(void){
  if(soundEnabled && trackLooping){
    if (millis() -trackStarted >= currentTrackLength){
      sfx.playTrack(currentTrack);
      trackStarted = millis();
    }  
  }
}
  


