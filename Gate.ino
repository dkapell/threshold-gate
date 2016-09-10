int pixels = 150;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, PIN_GATE, NEO_GRB + NEO_KHZ800);

long gateTimer = millis();
long gateTimer2;

long gateAnimationDelay = 40;
int gateAnimationCycle = 30;
int gatePixelIndex = 0;
byte gateAnimation = RAINBOW;
boolean gateAnimationDone = false;
long pulseTime = 1500;
byte pulseMaxBrightness = 255;
byte pulseMinBrightness = 8;

byte gateLightsIncreasing;

uint32_t gateActiveColor;
uint32_t gateActiveColor2;

boolean animationTimer = false;

void gateInit(){
  strip.begin();
  strip.show();
  gateOff();
  //setGateAnimation(DOUBLE_SPIN, getColor(255,0,0), getColor(255,0, 255), 50);
  //setGateAnimation(SPIN, getColor(255,0,255), 50);
  setGateAnimation(WIPE, getColor(255, 128, 128), 10);
}

uint32_t getColor(int r, int g, int b){
  return strip.Color(r,g,b);
}

void displayGate(){
  if (animationTimer){  // Animation uses the timer for calculation
    switch(gateAnimation){
      case PULSE: pulse(); break;
      default:
        gateAnimation = RAINBOW;
        animationTimer = false;
    }
  } else {  // Animation uses timer for delay
    long now = millis();
    if ((now - gateTimer) >= gateAnimationDelay){
      gateTimer = now;
      switch(gateAnimation){
        case RAINBOW: rainbow(); break;
        case WIPE: colorWipe(); break;
        case DOUBLE_WIPE: doubleWipe(); break;
        case SPIN: spin(); break;
        case DOUBLE_SPIN: doubleSpin(); break;
        default:
          gateAnimation = RAINBOW;
          
      }
    }
  }
}

void setGateAnimation(byte a){
  setGateAnimation(a, 0, 0, 0);
}

void setGateAnimation(byte a, int t){
  setGateAnimation(a, 0, 0, t);
}

void setGateAnimation(byte a, uint32_t c, int t){
  setGateAnimation(a, c, 0, t);
}

void setGateAnimation(byte a, uint32_t c, uint32_t c2, int t){
  gateAnimationDelay = t;
  gateActiveColor = c;
  gateActiveColor2 = c2;
  gateAnimation = a;
  gatePixelIndex = 0;
  gateAnimationDone = false;
  if (a == PULSE){
    animationTimer = true;
  } else {
    animationTimer = false;
  }
}


void rainbow() {
  gateAnimationCycle = ++gateAnimationCycle % 255;
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i+gateAnimationCycle) & 255));
  }
  strip.show();
  
}

void colorWipe() {
  if(gatePixelIndex < strip.numPixels()){
    strip.setPixelColor(gatePixelIndex, gateActiveColor);
    strip.show();
    gatePixelIndex++;
  } else {
    gateAnimationDone = true;
  }
}

void doubleWipe(){
  if(gatePixelIndex*2 <= strip.numPixels()){
    strip.setPixelColor(gatePixelIndex, gateActiveColor);
    strip.setPixelColor(strip.numPixels() - gatePixelIndex, gateActiveColor);
    strip.show();
    gatePixelIndex++;
  } else {
    gateAnimationDone = true;
  }
}





void spin(){
  gateAnimationCycle = ++gateAnimationCycle % (strip.numPixels()/GATE_ELEMENTS);
  
  for(int i=0; i<strip.numPixels(); i++) {
    
    strip.setPixelColor(i, Gate(i, 255));
    
  }
  strip.show();
  
}

void doubleSpin(){
  int chunkLength = strip.numPixels()/(GATE_ELEMENTS/2);
  gateAnimationCycle = ++gateAnimationCycle % chunkLength;
  
  for(int i=0; i<strip.numPixels(); i++) {
    int colorIndex = (i +(chunkLength-gateAnimationCycle))  % (chunkLength);
    int pulseIndex = (i+(chunkLength/4)) % (chunkLength/2);
    int cycleIndex = gateAnimationCycle % (chunkLength/2);
    /*
    Serial.println("-----");
    Serial.println(i);
    Serial.println(chunkLength);
    Serial.println(gateAnimationCycle);
    Serial.println(colorIndex);
    Serial.println(pulseIndex);
    Serial.println(cycleIndex);
    */

    if (colorIndex  < chunkLength/2){
      //strip.setPixelColor(i, gateActiveColor);
      
      strip.setPixelColor(i, Gate(pulseIndex, 255, gateAnimationCycle % (chunkLength/2), gateActiveColor));
    } else {
      //strip.setPixelColor(i, gateActiveColor2);
      strip.setPixelColor(i, Gate(pulseIndex, 255, gateAnimationCycle % (chunkLength/2), gateActiveColor2));
    }
  }
  strip.show();
  
}

void pulse(){
  long now = millis();
  if ((now - gateTimer) >= pulseTime){
    ++gateLightsIncreasing %= 2;
    gateTimer = now;
  }
  long currentStep = now - gateTimer2;
  
  for(int i=0; i<strip.numPixels(); i++) {
    byte brightness;
    if (gateLightsIncreasing){
      brightness = pulseMaxBrightness - (currentStep*(pulseMaxBrightness - pulseMinBrightness)/pulseTime); // fade out
    } else {
      brightness = pulseMinBrightness + currentStep*(pulseMaxBrightness - pulseMinBrightness)/pulseTime; // fade in
    }
    strip.setPixelColor(i, Gate(i, brightness));
  }
  strip.show();
}

void gateOff(){
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,0);
  }
  strip.show();
}

boolean isAnimationDone() {
  return gateAnimationDone;
}

byte getRed(uint32_t color){
  return (color >> 16);
}
byte getGreen(uint32_t color){
  return (color >> 8);
}
byte getBlue(uint32_t color){
  return (color & 0x000000ff);
}

uint32_t Gate(int GatePos, byte brightness){
  return Gate(GatePos, brightness, gateAnimationCycle, gateActiveColor);
}

uint32_t Gate(int GatePos, byte brightness, uint32_t color){
  return Gate(GatePos, brightness, gateAnimationCycle, color);
}


uint32_t Gate(int GatePos, byte brightness, int cycle, uint32_t color){
  int index = GatePos % ( strip.numPixels()/GATE_ELEMENTS);
  int diffPos = cycle - index;
  int diffNeg = (strip.numPixels()/GATE_ELEMENTS + cycle) - index;
  int absPos = abs(diffPos);
  int absNeg = abs(diffNeg);
  int diff = min(absPos, absNeg);
  
  byte gateRed = getRed(color);
  byte gateGreen = getGreen(color);
  byte gateBlue = getBlue(color);
  
  byte red = 0;
  byte green = 0;
  byte blue = 0;
  
  if (index == cycle){
    red = gateRed;
    green = gateGreen;
    blue = gateBlue;
    
  } else if (diff < 5){
    red = gateRed/(diff*3);
    green = gateGreen/(diff*3);
    blue = gateBlue/(diff*3);
  }  else {
      red = map(2, 0, 100, 0, gateRed);
      green = map(2, 0, 100, 0, gateGreen);
      blue = map(2, 0, 100, 0, gateBlue);
    
  }

  red = map(red, 0, 255, 0, brightness);
  green = map(green, 0, 255, 0, brightness);
  blue = map(blue, 0, 255, 0, brightness);
  if (gateRed){
    red = max(pulseMinBrightness, red);
  }
  if (gateGreen){
    green = max(pulseMinBrightness, green);
  }
  if (gateBlue){
    blue = max(pulseMinBrightness, blue);
  }
  return strip.Color(red, green, blue);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
