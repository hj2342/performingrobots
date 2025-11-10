#include <Adafruit_NeoPixel.h>

#define CROWN_PIN 8
#define NUM_CROWN 28

Adafruit_NeoPixel crown(NUM_CROWN, CROWN_PIN, NEO_GRB + NEO_KHZ800);

int baseBrightness = 80;

void setup() {
  crown.begin();
  crown.setBrightness(baseBrightness);
  crown.show();
}

// ----------------- Patterns -----------------

// Fill entire strip with color
void setCrownColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_CROWN; i++) {
    crown.setPixelColor(i, crown.Color(r, g, b));
  }
  crown.show();
}

// Flow one pixel along the strip
void flowPattern(uint8_t r, uint8_t g, uint8_t b, int delayTime = 50) {
  for (int i = 0; i < NUM_CROWN; i++) {
    crown.clear();
    crown.setPixelColor(i, crown.Color(r, g, b));
    crown.show();
    delay(delayTime);
  }
}

// Pulse entire strip
void pulsePattern(uint8_t r, uint8_t g, uint8_t b, int steps = 50, int delayTime = 20) {
  for (int i = 0; i <= steps; i++) {
    int br = map(i, 0, steps, 0, baseBrightness);
    crown.setBrightness(br);
    setCrownColor(r, g, b);
    delay(delayTime);
  }
  for (int i = steps; i >= 0; i--) {
    int br = map(i, 0, steps, 0, baseBrightness);
    crown.setBrightness(br);
    setCrownColor(r, g, b);
    delay(delayTime);
  }
}

// Flicker pattern for tense / nervous
void flickerPattern(uint8_t r, uint8_t g, uint8_t b, int iterations = 20, int maxDelay = 100) {
  for (int i = 0; i < iterations; i++) {
    int br = random(20, baseBrightness); 
    crown.setBrightness(br);
    setCrownColor(r, g, b);
    delay(random(20, maxDelay));
  }
}

// ----------------- Main Loop -----------------

void loop() {
  unsigned long t = millis();
  unsigned long modTime = t % 40000; // loop through a 40s scenario
}
// | Emotion / Mood       | Color / Pattern Idea      | Notes                        |
// | -------------------- | ------------------------- | ---------------------------- |
// | Calm / Thinking      | Soft blue glow            | Intellectual, plotting       |
// | Happy / Lighthearted | Green flow/wave           | Rare moments, positive vibes |
// | Angry / Frustrated   | Red pulse                 | Intense and dangerous        |
// | Sad / Reflective     | Purple slow fade          | Emotional turmoil            |
// | Suspicious / Cunning | Yellow chase              | Calculating, scheming        |
// | Evil / Heisenberg    | Orange-red gradient pulse | Dark, menacing aura          |
// | Tense / Nervous      | Flickering white          | Anxiety, high stakes moments |
// | Neutral / Default    | White soft glow           | Calm baseline state          |
  // Map emotions to time slots
  if (modTime < 5000) {           // Calm / Thinking
    pulsePattern(0, 0, 255, 80, 30);
  } else if (modTime < 10000) {   // Happy / Lighthearted
    flowPattern(0, 255, 0, 40);
  } else if (modTime < 15000) {   // Angry / Frustrated
    pulsePattern(255, 0, 0, 80, 20);
  } else if (modTime < 20000) {   // Sad / Reflective
    pulsePattern(150, 0, 255, 100, 40);
  } else if (modTime < 25000) {   // Suspicious / Cunning
    flowPattern(255, 255, 0, 30);
  } else if (modTime < 30000) {   // Evil / Heisenberg
    pulsePattern(255, 100, 0, 80, 25);
  } else if (modTime < 35000) {   // Tense / Nervous
    flickerPattern(255, 255, 255, 30, 80);
  } else {                         // Neutral / Default
    pulsePattern(255, 255, 255, 50, 40);
  }


