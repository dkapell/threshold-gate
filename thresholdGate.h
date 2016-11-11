// Debug Mode
#define DEBUG 0

//Colors
#define RED 0
#define GREEN 1
#define BLUE 2

//state machine
#define STATE_INITIAL 0
#define STATE_GATE_OFF 1
#define STATE_COUNTDOWN 2
#define STATE_OPENING 3
#define STATE_OPEN 4
#define STATE_PAUSED 5
#define STATE_CLOSING 6
#define STATE_CLOSING_EMERGENCY 7
#define STATE_DEMO 8

//Pins
#define PIN_RX 0
#define PIN_TX 1
#define PIN_RESET 2
#define PIN_RESET_LED 3
#define PIN_GATE 4
#define PIN_CLOSE_LED 5
#define PIN_PAUSE_LED 6
#define PIN_ADD_MIN 7
#define PIN_SUB_MIN 8
#define PIN_TIME_LED 9
#define PIN_PAUSE 10
#define PIN_OPEN 11
#define PIN_HQ_PAUSE 12
#define PIN_CLOSE 13
#define PIN_SOUND_RST 15

// Buttons
#define BTN_RESET 0
#define BTN_ADD_MIN 1
#define BTN_SUB_MIN 2
#define BTN_PAUSE 3
#define BTN_OPEN 4
#define BTN_HQ_PAUSE 5
#define BTN_CLOSE 6

// LEDs
#define LED_RESET 0
#define LED_CLOSE 1
#define LED_PAUSE 2
#define LED_TIME 3

// Sounds // These need to be pulled from the drive in order
#define SND_GATE_OFF 1
#define SND_COUNTDOWN_START 2
#define SND_GATE_OPENING 3
#define SND_GATE_OPEN 4
#define SND_GATE_CLOSING 5
#define SND_GATE_CLOSING_EMERGENCY 6

// Gate Lights
#define RAINBOW 0  // Cycle between colors
#define WIPE 1 // Wipe a color from one end to the other - does not clear first
#define WIPE_OFF 2 // turn off from one end to the other
#define DOUBLE_WIPE 3 // Wipe a color in from both ends - does not clear first
#define SPIN 4 // spin bright spot of a color around the strip
#define DOUBLE_SPIN 5 // spin ght spots of two colors around the strip
#define PULSE 6 // pulse bright spots of a color in place
#define COMET 7 // Spin a bright spot with random tail

#define GATE_ELEMENTS 8

struct RGB {
  byte r;
  byte g;
  byte b;
};

RGB GateColor(int GatePos, byte brightness);
RGB GateColor(int GatePos, byte brightness, uint32_t color);
RGB GateColor(int GatePos, byte brightness, int cycle, uint32_t color);
RGB CometColor(int GatePos, byte brightness);
