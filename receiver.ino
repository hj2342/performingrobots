// =====================================================================
//                    INTEGRATED ROBOT RECEIVER
//          Synchronized Servo, Audio, and NeoPixel Control
// =====================================================================

// -------------------- NRF24L01 SETUP --------------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int NRF_CE_PIN = A11, NRF_CSN_PIN = A15;

// -------------------- MUSIC MAKER SHIELD --------------------
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_RESET -1
#define SHIELD_CS 7
#define SHIELD_DCS 6
#define CARDCS 4
#define DREQ 3

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// -------------------- SERVO MOTORS --------------------
#include <Servo.h>

// Servo objects
Servo r_shoulder;  // M2 = Pin 20
Servo r_arm;       // M3 = Pin 21
Servo r_4arm;      // M1 = Pin 19

Servo l_shoulder;  // M6 = Pin 17
Servo l_arm;       // M5 = Pin 18
Servo l_4arm;      // M4 = Pin 16

Servo jaw;         // Optional jaw servo

// Servo pins
const int R_SHOULDER_PIN = 20;
const int R_ARM_PIN = 21;
const int R_4ARM_PIN = 19;
const int L_SHOULDER_PIN = 17;
const int L_ARM_PIN = 18;
const int L_4ARM_PIN = 16;

// -------------------- NEOPIXELS --------------------
#include <Adafruit_NeoPixel.h>

#define EYE1_PIN   2
#define EYE2_PIN   5
#define CROWN_PIN  8  // Note: May conflict with music shield, adjust if needed

#define NUM_EYES 2
#define NUM_CROWN 28

Adafruit_NeoPixel eye1(NUM_EYES, EYE1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eye2(NUM_EYES, EYE2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel crown(NUM_CROWN, CROWN_PIN, NEO_GRB + NEO_KHZ800);

int baseBrightness = 80;

// -------------------- RF24 SETUP --------------------
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);

const byte CUSTOM_ADDRESS_BYTE = 0x33;
const int CUSTOM_CHANNEL_NUMBER = 90;

const byte xmtrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t stateNumber;
};
DataStruct data;

// =====================================================================
//                      NEOPIXEL FUNCTIONS
// =====================================================================

void setEyesColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_EYES; i++) {
    eye1.setPixelColor(i, eye1.Color(r, g, b));
    eye2.setPixelColor(i, eye2.Color(r, g, b));
  }
  eye1.show();
  eye2.show();
}

void setCrownColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_CROWN; i++) {
    crown.setPixelColor(i, crown.Color(r, g, b));
  }
  crown.show();
}

void pulseEyes(uint8_t r, uint8_t g, uint8_t b, int duration = 1000) {
  int steps = 50;
  int delayTime = duration / (steps * 2);
  
  for (int i = 0; i <= steps; i++) {
    int br = map(i, 0, steps, 0, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);
    setEyesColor(r, g, b);
    delay(delayTime);
  }
  
  for (int i = steps; i >= 0; i--) {
    int br = map(i, 0, steps, 0, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);
    setEyesColor(r, g, b);
    delay(delayTime);
  }
}

void flickerEyes(uint8_t r, uint8_t g, uint8_t b, int duration = 1000) {
  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    int br = random(20, baseBrightness);
    eye1.setBrightness(br);
    eye2.setBrightness(br);
    setEyesColor(r, g, b);
    delay(random(20, 80));
  }
}

void pulseCrown(uint8_t r, uint8_t g, uint8_t b, int duration = 1000) {
  int steps = 50;
  int delayTime = duration / (steps * 2);
  
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

void setMood(String mood) {
  if (mood == "angry") {
    setEyesColor(255, 0, 0);
    setCrownColor(255, 0, 0);
  } else if (mood == "sad") {
    setEyesColor(0, 0, 255);
    setCrownColor(0, 0, 255);
  } else if (mood == "happy") {
    setEyesColor(0, 255, 0);
    setCrownColor(0, 255, 0);
  } else if (mood == "confused") {
    setEyesColor(150, 0, 255);
    setCrownColor(150, 0, 255);
  } else if (mood == "neutral") {
    setEyesColor(255, 255, 255);
    setCrownColor(255, 255, 255);
  } else if (mood == "excited") {
    setEyesColor(255, 255, 0);
    setCrownColor(255, 255, 0);
  }
}

// =====================================================================
//                      SERVO FUNCTIONS
// =====================================================================

void attachAllServos() {
  r_shoulder.attach(R_SHOULDER_PIN);
  r_arm.attach(R_ARM_PIN);
  r_4arm.attach(R_4ARM_PIN);
  l_shoulder.attach(L_SHOULDER_PIN);
  l_arm.attach(L_ARM_PIN);
  l_4arm.attach(L_4ARM_PIN);
}

void detachAllServos() {
  r_shoulder.detach();
  r_arm.detach();
  r_4arm.detach();
  l_shoulder.detach();
  l_arm.detach();
  l_4arm.detach();
}

void initialPose() {
  attachAllServos();
  r_shoulder.write(60);
  r_arm.write(180);
  r_4arm.write(20);
  l_shoulder.write(60);
  l_arm.write(0);
  l_4arm.write(0);
  delay(500);
}

void shoulderFlap() {
  r_shoulder.write(60);
  l_shoulder.write(60);
  delay(500);
  
  r_shoulder.write(80);
  l_shoulder.write(40);
  delay(500);
  
  r_shoulder.write(60);
  l_shoulder.write(60);
  delay(500);
}

void dab() {
  l_arm.write(180);
  delay(1000);
  
  l_shoulder.write(10);
  r_shoulder.write(180);
  r_4arm.write(0);
  delay(3000);
  
  l_shoulder.write(60);
  r_shoulder.write(60);
  r_4arm.write(90);
  delay(500);
}

void armWave() {
  for (int i = 0; i < 3; i++) {
    r_4arm.write(0);
    l_4arm.write(0);
    delay(300);
    
    r_4arm.write(20);
    l_4arm.write(20);
    delay(300);
  }
}

void shoulderGroove() {
  for (int i = 0; i < 3; i++) {
    r_shoulder.write(50);
    l_shoulder.write(50);
    delay(500);
    
    r_shoulder.write(60);
    l_shoulder.write(60);
    delay(500);
  }
}

void angryGesture() {
  // Clenched fists, aggressive posture
  r_4arm.write(0);
  l_4arm.write(0);
  r_shoulder.write(80);
  l_shoulder.write(40);
  delay(1000);
}

void defensiveGesture() {
  // Arms up, defensive
  r_arm.write(90);
  l_arm.write(90);
  r_shoulder.write(70);
  l_shoulder.write(50);
  delay(1000);
}

void pointingGesture() {
  // Point with right arm
  r_arm.write(0);
  r_4arm.write(0);
  r_shoulder.write(90);
  delay(1500);
}

// =====================================================================
//                   SYNCHRONIZED PERFORMANCE FUNCTIONS
// =====================================================================

// Track 001: "You've been practicing. That spin almost looked graceful."
void performTrack001() {
  Serial.println(F("Track 001: Playful/Flirtatious"));
  
  // Setup
  initialPose();
  setMood("happy");
  
  // Play audio
  musicPlayer.startPlayingFile("track001.mp3");
  
  // Synchronized actions
  delay(500);
  pulseEyes(0, 255, 0, 1000);  // Happy green eyes
  
  delay(1000);
  shoulderFlap();  // Playful gesture
  
  delay(1000);
  armWave();  // Wave gesture
  
  // Wait for audio to finish
  while (musicPlayer.playingMusic) {
    setEyesColor(0, 255, 0);
    delay(100);
  }
  
  initialPose();
}

// Track 002: "It was just harmless dancing..."
void performTrack002() {
  Serial.println(F("Track 002: Defensive/Casual"));
  
  initialPose();
  setMood("confused");
  
  musicPlayer.startPlayingFile("track002.mp3");
  
  delay(1000);
  dab();  // Casual gesture
  
  delay(2000);
  shoulderGroove();  // Defensive body language
  
  while (musicPlayer.playingMusic) {
    pulseEyes(150, 0, 255, 2000);
    delay(100);
  }
  
  initialPose();
}

// Track 003: "Honey, you're overreacting."
void performTrack003() {
  Serial.println(F("Track 003: Dismissive"));
  
  initialPose();
  setMood("neutral");
  
  musicPlayer.startPlayingFile("track003.mp3");
  
  delay(500);
  armWave();  // Dismissive hand wave
  
  while (musicPlayer.playingMusic) {
    setEyesColor(255, 255, 255);
    delay(100);
  }
  
  initialPose();
}

// Track 005: "GO TO BED!"
void performTrack005() {
  Serial.println(F("Track 005: Angry"));
  
  initialPose();
  setMood("angry");
  
  musicPlayer.startPlayingFile("track005.mp3");
  
  delay(200);
  angryGesture();
  
  flickerEyes(255, 0, 0, 2000);  // Angry red flicker
  
  delay(500);
  pointingGesture();  // Pointing aggressively
  
  while (musicPlayer.playingMusic) {
    setEyesColor(255, 0, 0);
    delay(100);
  }
  
  initialPose();
}

// Track 006: Long angry monologue
void performTrack006() {
  Serial.println(F("Track 006: Sarcastic then Aggressive"));
  
  initialPose();
  setMood("angry");
  
  musicPlayer.startPlayingFile("track006.mp3");
  
  // Sarcastic phase (first 3 seconds)
  delay(1000);
  armWave();
  delay(2000);
  
  // Aggressive phase
  angryGesture();
  delay(2000);
  
  pointingGesture();
  
  while (musicPlayer.playingMusic) {
    flickerEyes(255, 0, 0, 500);
    delay(100);
  }
  
  initialPose();
}

// Generic performance for other tracks
void performGenericTrack(int trackNum, String mood) {
  Serial.print(F("Track "));
  Serial.print(trackNum);
  Serial.print(F(": "));
  Serial.println(mood);
  
  initialPose();
  setMood(mood);
  
  char filename[20];
  sprintf(filename, "track%03d.mp3", trackNum);
  
  musicPlayer.startPlayingFile(filename);
  
  // Generic gesture
  delay(1000);
  if (mood == "angry") {
    angryGesture();
  } else if (mood == "sad") {
    shoulderFlap();
  } else {
    armWave();
  }
  
  while (musicPlayer.playingMusic) {
    delay(100);
  }
  
  initialPose();
}

// =====================================================================
//                         SETUP FUNCTIONS
// =====================================================================

void setupRF24Common() {
  if (!radio.begin()) {
    Serial.println(F("Radio initialization failed"));
    while (1);
  } else {
    Serial.println(F("Radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(CUSTOM_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

void setupRF24() {
  setupRF24Common();
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);
  Serial.println(F("I am a receiver"));
}

void setupMusicMakerShield() {
  if (!musicPlayer.begin()) {
    Serial.println(F("Couldn't find VS1053"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD card failed or not present"));
    while (1);
  }
  Serial.println(F("SD card OK"));

  musicPlayer.setVolume(20, 20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
}

void setupNeoPixels() {
  eye1.begin();
  eye2.begin();
  crown.begin();

  eye1.setBrightness(baseBrightness);
  eye2.setBrightness(baseBrightness);
  crown.setBrightness(baseBrightness);

  eye1.show();
  eye2.show();
  crown.show();
  
  Serial.println(F("NeoPixels initialized"));
}

void setupServoMotors() {
  initialPose();
  Serial.println(F("Servos initialized"));
}

// =====================================================================
//                            SETUP
// =====================================================================

void setup() {
  Serial.begin(9600);
  Serial.println(F("========================================"));
  Serial.println(F("   INTEGRATED ROBOT RECEIVER"));
  Serial.println(F("========================================"));

  setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();
  setupRF24();

  // Flash to indicate ready
  setEyesColor(0, 255, 0);
  setCrownColor(0, 255, 0);
  delay(500);
  setEyesColor(0, 0, 0);
  setCrownColor(0, 0, 0);
  
  Serial.println(F("Setup complete. Waiting for commands..."));
}

// =====================================================================
//                            MAIN LOOP
// =====================================================================

void loop() {
  radio.startListening();
  
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    
    Serial.print(F("Received command: "));
    Serial.println(data.stateNumber);

    // Execute synchronized performance based on track number
    switch (data.stateNumber) {
      case 1:
        performTrack001();
        break;
        
      case 2:
        performTrack002();
        break;
        
      case 3:
        performTrack003();
        break;
        
      case 5:
        performTrack005();
        break;
        
      case 6:
        performTrack006();
        break;
        
      // Add more cases for tracks 4, 7-28
      case 7:
        performGenericTrack(7, "angry");
        break;
        
      case 8:
        performGenericTrack(8, "angry");
        break;
        
      case 9:
        performGenericTrack(9, "angry");
        break;
        
      case 10:
        performGenericTrack(10, "confused");
        break;
      
      case 11:
        performGenericTrack(11, "neutral");   // Playful sarcasm
        break;

      case 12:
        performGenericTrack(12, "sad");       // Concerned
        break;

      case 13:
        performGenericTrack(13, "sad");       // Apologetic
        break;

      case 14:
        performGenericTrack(14, "confused");  // Nervous rambling
        break;

      case 15:
        performGenericTrack(15, "happy");     // Hyper / silly
        break;

      case 16:
        performGenericTrack(16, "neutral");   // Confident / cool
        break;

      case 17:
        performGenericTrack(17, "excited");   // Heroic / dramatic
        break;

      case 18:
        performGenericTrack(18, "confused");  // Sneaky whisper
        break;

      case 19:
        performGenericTrack(19, "excited");   // Super excited
        break;

      case 20:
        performGenericTrack(20, "neutral");   // Mock offended
        break;

      case 21:
        performGenericTrack(21, "sad");       // Tired / exhausted
        break;

      case 22:
        performGenericTrack(22, "sad");       // Dramatically sad
        break;

      case 23:
        performGenericTrack(23, "happy");     // Mischievous
        break;

      case 24:
        performGenericTrack(24, "angry");     // Serious / cold
        break;

      case 25:
        performGenericTrack(25, "confused");  // Shocked
        break;

      case 26:
        performGenericTrack(26, "happy");     // Gentle / supportive
        break;

      case 27:
        performGenericTrack(27, "excited");   // Mock dramatic
        break;

      case 28:
        performGenericTrack(28, "neutral");   // Calm resolution
        break;
      
      
        
      // Continue pattern for all 28 tracks...
      
      default:
        Serial.println(F("Invalid track number"));
        setMood("confused");
        delay(1000);
        setEyesColor(0, 0, 0);
        setCrownColor(0, 0, 0);
    }
    
    Serial.println(F("Performance complete. Ready for next command."));
  }
}
