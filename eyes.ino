#include <Adafruit_NeoPixel.h>

#define LEFT_EYE_PIN 7
#define RIGHT_EYE_PIN 8
#define NUMPIXELS 1

Adafruit_NeoPixel leftEye(NUMPIXELS, LEFT_EYE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightEye(NUMPIXELS, RIGHT_EYE_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
int baseBrightness = 80;   // Normal brightness
bool isBlinking = false;

void setup() {
  leftEye.begin();
  rightEye.begin();
  leftEye.setBrightness(baseBrightness);
  rightEye.setBrightness(baseBrightness);
}

// Set both eyes to same color
void setEyes(uint8_t r, uint8_t g, uint8_t b) {
  leftEye.setPixelColor(0, leftEye.Color(r, g, b));
  rightEye.setPixelColor(0, rightEye.Color(r, g, b));
  leftEye.show();
  rightEye.show();
}

// Smooth blink effect
void slowBlink(int holdTime = 100) {
  // Fade eyes closed
  for (int b = baseBrightness; b >= 0; b -= 2) {
    leftEye.setBrightness(b);
    rightEye.setBrightness(b);
    leftEye.show();
    rightEye.show();
    delay(10);
  }
  delay(holdTime); // Eyes closed for a short time
  // Fade eyes open
  for (int b = 0; b <= baseBrightness; b += 2) {
    leftEye.setBrightness(b);
    rightEye.setBrightness(b);
    leftEye.show();
    rightEye.show();
    delay(10);
  }
}

void loop() {
  unsigned long t = millis();

  // Emotion timeline (edit time ranges and colors)
  if (t < 5000) {            // Happy
    setEyes(0, 255, 0);
  } else if (t < 10000) {    // Curious
    setEyes(0, 0, 255);
  } else if (t < 15000) {    // Angry
    setEyes(255, 0, 0);
  } else if (t < 20000) {    // Sad
    setEyes(150, 0, 255);
  } else {
    setEyes(150, 150, 150);  // Neutral
  }

  // Blink every 5 seconds
  if (t - previousMillis > 5000) {
    slowBlink(250); // hold eyes closed ¼ second
    previousMillis = t;
  }
}
