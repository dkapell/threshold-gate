/* Gate Display logic
 *  External
 *    void initGate() - initialize gate lights, call from setup()
 *    void displayGate() - run the current gate animation, call from loop()
 *    void setGateAnimation(animation) - set animation (RAINBOW, no delay)
 *    void setGateAnimation(animation, delay) - set animation 
 *    void setGateAnimation(animation, color) - set animation 
 *    void setGateAnimation(animation, color, time) - set animation 
 *    void setGateAnimation(animation, color1, color2, time) - set animation
 *    void gateOff() - turn gate animation off
 *  Internal
 *    boolean isAnimationDone() - check if animation (i.e. wipe, wipe_off, doublewipe) is complete
 *    byte getRed(packed), byte getGreen(packed), byte getBlue(packed) - get the r/g/b component from a packed value
 *    uint32_t getColor(red, green, blue) - calculate packed color value
 *  Animations
 *    RAINBOW - cycling rainbow (delay)
 *    WIPE - Wipes a color from 0 -> END (delay, color)
 *    DOUBLE_WIPE - Wipes a color from both ends to the middle (delay, color)
 *    WIPE_OFF - Wipes off from 0 -> end (delay)
 *    SPIN - Spins GATE_ELEMENTS bright spots around in a loop (delay, color)
 *    DOUBLE_SPIN - Spins GATE_ELEMENTS bright spots around in a loop of two colors (delay, color1, color2)
 *    COMET - Spins sparkling colors around in a loop (delay, color)
 */
int pixels = 192;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, PIN_GATE, NEO_GRB + NEO_KHZ800);

long gateTimer = millis();

long gateAnimationDelay = 40;
int gateAnimationCycle = 0;
int gatePixelIndex = 0;
byte gateAnimation = RAINBOW;
boolean gateAnimationDone = false;
long pulseTime = 1500;
byte pulseMaxBrightness = 255;
byte pulseMinBrightness = 8;

byte gateElements = 4;
boolean gateClockwise = true;

byte gateLightsIncreasing;

uint32_t gateActiveColor;
uint32_t gateActiveColor2;

boolean gateWhitePulse = false;

boolean animationTimer = false;

void initGate(){
  strip.begin();
  strip.show();
  gateOff();
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
        case WIPE_OFF: wipeOff(); break;
        case DOUBLE_WIPE: doubleWipe(); break;
        case SPIN: spin(); break;
        case DOUBLE_SPIN: doubleSpin(); break;
        case COMET: comet(); break;
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

void setGateAnimation(byte a, uint32_t c){
  setGateAnimation(a, c, 0, 0);
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

void setGatePixel(int pixel, RGB clr){
    strip.setPixelColor(pixel, clr.r, clr.g, clr.b);
}

void setGateElements(byte n){
  gateElements = n;
}

byte getGateElements(void){
  return gateElements;
}

void setGateClockwise(boolean b){
  gateClockwise = b;
} 

boolean getGateClockwise(void){
  return gateClockwise;
}

void setGateWhitePulse(boolean b){
  gateWhitePulse = b;
} 

boolean getGateWhitePulse(void){
  return gateWhitePulse;
}

