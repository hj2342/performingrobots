#include <Adafruit_NeoPixel.h>

// -------------------- PIN DEFINITIONS --------------------
#define EYE1_PIN   2
#define EYE2_PIN   5
#define CROWN_PIN  8

// -------------------- LED COUNTS -------------------------
#define NUM_EYES 2       // Eye 1 + Eye 2 = 2 pixels total
#define NUM_CROWN 28

// -------------------- OBJECTS -----------------------------
Adafruit_NeoPixel eye1(NUM_EYES, EYE1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eye2(NUM_EYES, EYE2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel crown(NUM_CROWN, CROWN_PIN, NEO_GRB + NEO_KHZ800);

// -------------------- SETTINGS ----------------------------
int baseBrightness = 80;

// ==========================================================
//                SYNCHRONIZED EYE FUNCTIONS
// ==========================================================

// Fill both eyes
void setEyesColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_EYES; i++) {
    eye1.setPixelColor(i, eye1.Color(r, g, b));
    eye2.setPixelColor(i, eye2.Color(r, g, b));
  }
  eye1.show();
  eye2.show();
}

// Synced pulse in & out
void pulseEyes(uint8_t r, uint8_t g, uint8_t b,
               int steps = 50, int delayTime = 20) {

  for (int i = 0; i <= steps; i++) {
    int br = map(i, 0, steps, 0, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);
    setEyesColor(r,g,b);
    delay(delayTime);
  }

  for (int i = steps; i >= 0; i--) {
    int br = map(i, 0, steps, 0, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);
    setEyesColor(r,g,b);
    delay(delayTime);
  }
}

// Synced flickering (tense mode)
void flickerEyes(uint8_t r, uint8_t g, uint8_t b,
                 int iterations = 20, int maxDelay = 80) {

  for (int i = 0; i < iterations; i++) {
    int br = random(20, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);

    setEyesColor(r,g,b);

    delay(random(20, maxDelay));
  }
}

// ==========================================================
//                     CROWN FUNCTIONS
// ==========================================================

// Fill all LEDs with color
void setCrownColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_CROWN; i++) {
    crown.setPixelColor(i, crown.Color(r, g, b));
  }
  crown.show();
}

// Pulse crown like eyes
void pulseCrown(uint8_t r, uint8_t g, uint8_t b,
                int steps = 50, int delayTime = 20) {

  for (int i = 0; i <= steps; i++) {
    int br = map(i, 0, steps, 0, baseBrightness);
    crown.setBrightness(br);
    setCrownColor(r,g,b);
    delay(delayTime);
  }

  for (int i = steps; i >= 0; i--) {
    int br = map(i, 0, steps, 0, baseBrightness);
    crown.setBrightness(br);
    setCrownColor(r,g,b);
    delay(delayTime);
  }
}

// Flowing crown effect
void flowCrown(uint8_t r, uint8_t g, uint8_t b, int delayTime = 40) {
  for (int i = 0; i < NUM_CROWN; i++) {
    crown.clear();
    crown.setPixelColor(i, crown.Color(r, g, b));
    crown.show();
    delay(delayTime);
  }
}

// Flicker for crown
void flickerCrown(uint8_t r, uint8_t g, uint8_t b,
                  int iterations = 20, int maxDelay = 100) {

  for (int i = 0; i < iterations; i++) {
    int br = random(20, baseBrightness);
    crown.setBrightness(br);
    setCrownColor(r,g,b);
    delay(random(20, maxDelay));
  }
}

// ==========================================================
//                        SETUP
// ==========================================================

void setup() {
  eye1.begin();
  eye2.begin();
  crown.begin();

  eye1.setBrightness(baseBrightness);
  eye2.setBrightness(baseBrightness);
  crown.setBrightness(baseBrightness);

  eye1.show();
  eye2.show();
  crown.show();
}

// ==========================================================
//                          LOOP
// ==========================================================

void loop() {
  unsigned long t = millis();
  unsigned long modTime = t % 40000; // 40-sec mood cycle

  if (modTime < 5000) {
    pulseEyes(0,0,255);
    pulseCrown(0,0,255);
  }
  else if (modTime < 10000) {
    pulseEyes(0,255,0);
    flowCrown(0,255,0);
  }
  else if (modTime < 15000) {
    pulseEyes(255,0,0);
    pulseCrown(255,0,0);
  }
  else if (modTime < 20000) {
    pulseEyes(150,0,255);
    pulseCrown(150,0,255);
  }
  else if (modTime < 25000) {
    pulseEyes(255,255,0);
    flowCrown(255,255,0);
  }
  else if (modTime < 30000) {
    pulseEyes(255,100,0);
    pulseCrown(255,100,0);
  }
  else if (modTime < 35000) {
    flickerEyes(255,255,255);
    flickerCrown(255,255,255);
  }
  else {
    pulseEyes(255,255,255);
    pulseCrown(255,255,255);
  }
}
