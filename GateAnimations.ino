/* animations for the gate neopixel display */

void rainbow() {
  gateAnimationCycle = ++gateAnimationCycle % 255;
  
  for(int i=0; i<strip.numPixels(); i++) {
    if (gateClockwise){
      strip.setPixelColor(i, Wheel((i+gateAnimationCycle) & 255));
    } else {
      strip.setPixelColor((strip.numPixels() - 1) - i, Wheel((i+gateAnimationCycle) & 255));
    }
  }
  strip.show();
  
}

void colorWipe() {
  if(gatePixelIndex < strip.numPixels()){
    if (!gateClockwise){
      strip.setPixelColor(gatePixelIndex, gateActiveColor);
    } else {
      strip.setPixelColor((strip.numPixels() - 1) - gatePixelIndex, gateActiveColor);
    }
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

void wipeOff() {
  if(gatePixelIndex < strip.numPixels()){
    if (!gateClockwise){
      strip.setPixelColor(gatePixelIndex, 0);
    } else {
      strip.setPixelColor((strip.numPixels() - 1) - gatePixelIndex, 0);
    }
    strip.show();
    gatePixelIndex++;
  } else {
    gateAnimationDone = true;
  }
}



void spin(){
  gateAnimationCycle = ++gateAnimationCycle % (strip.numPixels()/gateElements);
  for(int i=0; i<strip.numPixels(); i++) {
    if (!gateClockwise){
      setGatePixel(i, GateColor(i, 255)); 
    } else {
      setGatePixel((strip.numPixels()-1) - i, GateColor(i, 255)); 
    }
  }
  strip.show();
}

void doubleSpin(){
  int chunkLength = strip.numPixels()/(gateElements/2);
  gateAnimationCycle = ++gateAnimationCycle % chunkLength;

  int offset = chunkLength-gateAnimationCycle;
  int halfChunk = chunkLength/2;
  int quarterChunk = chunkLength/4;
  int cycleIndex = gateAnimationCycle % (halfChunk);
  
  for(int i=0; i<strip.numPixels(); i++) {
    int colorIndex = (i +(offset))  % (chunkLength);
    int pulseIndex = (i+(quarterChunk)) % (halfChunk);
    
    int ledIndex = i;
    
    if (!gateClockwise){
      ledIndex = (strip.numPixels() -1) - i;
    }
    
    if (colorIndex  < halfChunk){
      setGatePixel(ledIndex, GateColor(pulseIndex, 255, cycleIndex, gateActiveColor));
    } else {
      setGatePixel(ledIndex, GateColor(pulseIndex, 255, cycleIndex, gateActiveColor2));
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
  long currentStep = now - gateTimer;
  long fader = currentStep*pulseMaxBrightness/pulseTime;
  
  byte brightness;
  if (gateLightsIncreasing){
    brightness = pulseMaxBrightness - fader; // fade out
  } else {
    brightness = fader; // fade in
  }
  
  for(int i=0; i<strip.numPixels(); i++) {
    setGatePixel(i, GateColor(i, brightness));
  }
  strip.show();
}

void comet(){
  gateAnimationCycle = ++gateAnimationCycle % (strip.numPixels()/gateElements);
  
  for(int i=0; i<strip.numPixels(); i++) {
    if (!gateClockwise){
      setGatePixel(i, CometColor(i, 255));
    } else {
      setGatePixel((strip.numPixels() - 1) - i, CometColor(i, 255));
    }
  }
  strip.show();
 
}

// Helper functions

RGB GateColor(int GatePos, byte brightness){
  return GateColor(GatePos, brightness, gateAnimationCycle, gateActiveColor);
}

RGB GateColor(int GatePos, byte brightness, uint32_t color){
  return GateColor(GatePos, brightness, gateAnimationCycle, color);
}

RGB GateColor(int GatePos, byte brightness, int cycle, uint32_t color){
  int chunkSize = strip.numPixels() / gateElements;
  int index = GatePos % chunkSize;
  int diffPos = cycle - index;
  int diffNeg = (chunkSize + cycle) - index;
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
    if(gateWhitePulse){
      red = 255;
      green = 255;
      blue = 255;
    } else {
      red = gateRed;
      green = gateGreen;
      blue = gateBlue;
    }
    
  } else if (diff < 5){
    int diffFade = (diff*3);
    red = gateRed/diffFade;
    green = gateGreen/diffFade;
    blue = gateBlue/diffFade;
    
  }  else {
      red = min(1, gateRed);
      green = min(1, gateGreen);
      blue = min(1, gateBlue);
  }
  
  if (brightness != 255){
    red = map(red, 0, 255, 0, brightness);
    green = map(green, 0, 255, 0, brightness);
    blue = map(blue, 0, 255, 0, brightness);
  }

  if (gateRed){
    red = max(pulseMinBrightness, red);
  }
  if (gateGreen){
    green = max(pulseMinBrightness, green);
  }
  if (gateBlue){
    blue = max(pulseMinBrightness, blue);
  }
  return {red, green, blue};
}

RGB CometColor(int GatePos, byte brightness){
  int chunkSize = strip.numPixels()/gateElements;
  int index = GatePos % chunkSize;
  int currentLitPixel = gateAnimationCycle;
  
  int diff = (currentLitPixel - index) % chunkSize;
  if (diff < 0){
    diff += chunkSize;
  }
  
  byte gateRed = getRed(gateActiveColor);
  byte gateGreen = getGreen(gateActiveColor);
  byte gateBlue = getBlue(gateActiveColor);
  
  byte red = 0;
  byte green = 0;
  byte blue = 0;
  
  if (index == gateAnimationCycle){
    red = gateRed;
    green = gateGreen;
    blue = gateBlue;
    
  } else if (diff < 15){
    int maxDim = diff*10;
    int minDim = diff*3;
    if (diff < random(15)){
      red = gateRed/random(minDim, maxDim);
      green = gateGreen/random(minDim, maxDim);
      blue = gateBlue/random(minDim, maxDim);
    }
  }  
  if (brightness != 255){
    red = map(red, 0, 255, 0, brightness);
    green = map(green, 0, 255, 0, brightness);
    blue = map(blue, 0, 255, 0, brightness);
  }
  return {red, green, blue};
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

