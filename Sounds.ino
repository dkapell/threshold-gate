Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial, NULL, PIN_SOUND_RST);

boolean soundEnabled = false;

void initSound(){
  Serial.begin(9600); 
  if (!sfx.reset()) {
    Serial.println("No SFX found");
    soundEnabled = false;
  }
  soundEnabled = true;
}

void playSound(int track){
  if (soundEnabled){
    sfx.stop();
    sfx.playTrack(track); 
  } else {
    Serial.print("Would play track ");
    Serial.println(track);
  }
}

