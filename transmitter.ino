/*
   Transmitter for 23-Track Robot Performance System
   Based on nRF24L01 communication template
   
   23 Dialogues from updated play script
   
   Hardware: Arduino with LCD shield and 5 buttons
   - SW1: Count Down (previous track)
   - SW2: Transmit current track
   - SW3: Count Up (next track)
   - SW4: Jump to beginning (track 1)
   - SW5: Jump to end (track 23)
*/

// Common code
//

// nRF24L01 uses SPI which is fixed
// on pins 11, 12, and 13 on the Uno
// and on pins 50, 51, and 52 on the Mega

// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)

// For the transmitter
const int NRF_CE_PIN = A4, NRF_CSN_PIN = A5;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);  // CE, CSN

// Channel and address allocation
const byte CUSTOM_ADDRESS_BYTE = 0x33;  // Linh and Luke
const int CUSTOM_CHANNEL_NUMBER = 90;

// Do not make changes here
const byte xmtrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { CUSTOM_ADDRESS_BYTE, CUSTOM_ADDRESS_BYTE, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t stateNumber;
};
DataStruct data;

void setupRF24Common() {
  // RF24 setup
  if (!radio.begin()) {
    Serial.println(F("radio initialization failed"));
    while (1);
  } else {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(CUSTOM_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

// Transmitter code

// Transmitter pin usage
const int LCD_RS_PIN = 3, LCD_EN_PIN = 2, LCD_D4_PIN = 4, LCD_D5_PIN = 5, LCD_D6_PIN = 6, LCD_D7_PIN = 7;
const int SW1_PIN = 8, SW2_PIN = 9, SW3_PIN = 10, SW4_PIN = A3, SW5_PIN = A2;

// LCD library code
#include <LiquidCrystal.h>

// initialize the library with the relevant pins
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

const int NUM_OF_STATES = 24;  // 0-23 (24 total states)

// Track labels with number and keyword
// STATE 0 = Initial/Ready (no dialogue)
// STATES 1-23 = Actual dialogues (track001.mp3 - track023.mp3)
char* theStates[] = {
  "0:Initial",        // Initial state - no dialogue
  "1:Playful",        // track001.mp3 - "You've been practicing..."
  "2:Defensive",      // track002.mp3 - "It was just harmless..."
  "3:Dismissive",     // track003.mp3 - "Honey, you're overreacting"
  "4:Accusatory",     // track004.mp3 - "Well, maybe if you..."
  "5:Angry",          // track005.mp3 - "GO TO BED!"
  "6:Sarcastic",      // track006.mp3 - "Wow, I've never heard..."
  "7:Weary",          // track007.mp3 - "I can't believe we're..."
  "8:Possessive",     // track008.mp3 - "I want the coffee machine"
  "9:Confused",       // track009.mp3 - "Visual superiority?"
  "10:Defeated",      // track010.mp3 - "Did I just lose custody..."
  "11:Irritated",     // track011.mp3 - "It's just stuff, kid..."
  "12:Authority",     // track012.mp3 - "Go put that phone down"
  "13:Panicked",      // track013.mp3 - "What? Give me that"
  "14:Desperate",     // track014.mp3 - "Stop! That's private..."
  "15:Defensive2",    // track015.mp3 - "You don't understand..."
  "16:Guilty",        // track016.mp3 - "Where did you even..."
  "17:Protesting",    // track017.mp3 - "Wait—I didn't actually—"
  "18:Frustrated",    // track018.mp3 - "You're not helping"
  "19:Suspicious",    // track019.mp3 - "Hold on. Why is the Judge..."
  "20:AngryConfused", // track020.mp3 - "Why do YOU have HER phone?"
  "21:Explosive",     // track021.mp3 - "IT LOOKS LIKE YOU WERE..."
  "22:Betrayed",      // track022.mp3 - "I cannot BELIEVE this..."
  "23:Resigned"       // track023.mp3 - "So what now?"
};

void updateLCD() {
  lcd.clear();
  lcd.print(theStates[data.stateNumber]);
  lcd.setCursor(0, 1);  // column, line (from 0)
  lcd.print("Ready to send");
}

void countDown() {
  data.stateNumber = (data.stateNumber > 0) ? (data.stateNumber - 1) : 0;
  updateLCD();
}

void countUp() {
  if (++data.stateNumber >= NUM_OF_STATES) {
    data.stateNumber = NUM_OF_STATES - 1;
  }
  updateLCD();
}

void jumpToStart() {
  data.stateNumber = 1;  // Jump to track 1 (first dialogue)
  updateLCD();
}

void jumpToEnd() {
  data.stateNumber = 23;  // Jump to track 23 (last dialogue)
  updateLCD();
}

void rf24SendData() {
  radio.stopListening();  // go into transmit mode
  
  // The write() function will block until the message is successfully 
  // acknowledged by the receiver or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));

  lcd.clear();
  lcd.setCursor(0, 0);  // column, line (from 0)
  lcd.print("Sending:");
  lcd.setCursor(9, 0);
  lcd.print(theStates[data.stateNumber]);

  Serial.print(F("Transmitting state "));
  Serial.print(data.stateNumber);
  Serial.print(F(" ("));
  Serial.print(theStates[data.stateNumber]);
  Serial.print(F(") ... "));
  
  if (retval) {
    Serial.println(F("SUCCESS"));
    lcd.setCursor(0, 1);  // column, line (from 0)
    lcd.print("SUCCESS!");
  } else {
    totalTransmitFailures++;
    Serial.print(F("FAILED, total failures = "));
    Serial.println(totalTransmitFailures);

    lcd.setCursor(0, 1);  // column, line (from 0)
    lcd.print("ERROR! Tot:");
    lcd.setCursor(12, 1);
    lcd.print(totalTransmitFailures);
  }
  
  delay(1000);  // Show result for 1 second
  updateLCD();  // Return to ready state
}

class Button {
  int pinNumber;
  bool previousState;
  void (*buttonFunction)();
  
public:
  // Constructor
  Button(int pn, void (*bf)()) {
    pinNumber = pn;
    buttonFunction = bf;
    previousState = HIGH;
  }

  // update the button
  void update() {
    bool currentState = digitalRead(pinNumber);
    if (currentState == LOW && previousState == HIGH) {
      Serial.print(F("Button on pin "));
      Serial.print(pinNumber);
      Serial.println(F(" pressed"));
      buttonFunction();
    }
    previousState = currentState;
  }
};

const int NUMBUTTONS = 5;
Button theButtons[] = {
  Button(SW1_PIN, countDown),      // Previous track
  Button(SW2_PIN, rf24SendData),   // Transmit
  Button(SW3_PIN, countUp),        // Next track
  Button(SW4_PIN, jumpToStart),    // Jump to track 1
  Button(SW5_PIN, jumpToEnd),      // Jump to track 23
};

void setupRF24() {
  setupRF24Common();

  // Set us as a transmitter
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);

  Serial.println(F("I am a transmitter"));
  data.stateNumber = 1;  // Start at track 1 (first dialogue)
}

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("========================================"));
  Serial.println(F("   23-TRACK ROBOT TRANSMITTER"));
  Serial.println(F("   Updated Script - Sequential Order"));
  Serial.println(F("========================================"));
  
  // Set up the LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Radio setup...");

  // Display the address in hex
  lcd.setCursor(0, 1);
  lcd.print("addr 0x");
  lcd.setCursor(7, 1);
  char s[5];
  sprintf(s, "%02x", CUSTOM_ADDRESS_BYTE);
  lcd.print(s);

  // Display the channel number
  lcd.setCursor(10, 1);
  lcd.print("ch");
  lcd.setCursor(13, 1);
  lcd.print(CUSTOM_CHANNEL_NUMBER);

  delay(2000);

  Serial.println(F("Setting up radio..."));
  setupRF24();

  // If setupRF24 returned then the radio is set up
  lcd.clear();
  lcd.print("Radio OK!");
  lcd.setCursor(0, 1);
  lcd.print("States 0-23");
  
  delay(1500);

  // Initialize the switches
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);
  pinMode(SW3_PIN, INPUT_PULLUP);
  pinMode(SW4_PIN, INPUT_PULLUP);
  pinMode(SW5_PIN, INPUT_PULLUP);

  // Show initial state
  updateLCD();
  
  Serial.println(F("\nButton Functions:"));
  Serial.println(F("SW1 (Pin 8):  Previous track"));
  Serial.println(F("SW2 (Pin 9):  TRANSMIT current track"));
  Serial.println(F("SW3 (Pin 10): Next track"));
  Serial.println(F("SW4 (Pin A3): Jump to track 1 (first dialogue)"));
  Serial.println(F("SW5 (Pin A2): Jump to track 23 (last dialogue)"));
  Serial.println(F("\nStates 0-23: 0=Initial, 1-23=Dialogues"));
  Serial.println(F("========================================\n"));
}

void loop() {
  for (int i = 0; i < NUMBUTTONS; i++) {
    theButtons[i].update();
  }
  delay(50);
}

void clearData() {
  // set all fields to 0
  data.stateNumber = 0;
}

// Track reference for Serial Monitor
void printTrackReference() {
  Serial.println(F("\n========================================"));
  Serial.println(F("           TRACK REFERENCE"));
  Serial.println(F("========================================"));
  Serial.println(F("Scene 1 - Opening:"));
  Serial.println(F("  1: Playful - 'You've been practicing...'"));
  Serial.println(F("\nScene 2 - Confrontation:"));
  Serial.println(F("  2: Defensive - 'It was just harmless...'"));
  Serial.println(F("  3: Dismissive - 'Honey, you're overreacting'"));
  Serial.println(F("  4: Accusatory - 'Well, maybe if you...'"));
  Serial.println(F("  5: Angry - 'GO TO BED!'"));
  Serial.println(F("  6: Sarcastic - 'Wow, I've never heard...'"));
  Serial.println(F("\nScene 4 - Text Fight:"));
  Serial.println(F("  7: Weary - 'I can't believe we're...'"));
  Serial.println(F("  8: Possessive - 'I want the coffee machine'"));
  Serial.println(F("  9: Confused - 'Visual superiority?'"));
  Serial.println(F("  10: Defeated - 'Did I just lose custody...'"));
  Serial.println(F("\nScene 4.2 - Private:"));
  Serial.println(F("  11: Irritated - 'It's just stuff, kid...'"));
  Serial.println(F("  12: Authority - 'Go put that phone down'"));
  Serial.println(F("  13: Panicked - 'What? Give me that'"));
  Serial.println(F("  14: Desperate - 'Stop! That's private...'"));
  Serial.println(F("  15: Defensive2 - 'You don't understand...'"));
  Serial.println(F("  16: Guilty - 'Where did you even...'"));
  Serial.println(F("\nScene 5 - Courtroom:"));
  Serial.println(F("  17: Protesting - 'Wait—I didn't actually—'"));
  Serial.println(F("  18: Frustrated - 'You're not helping'"));
  Serial.println(F("  19: Suspicious - 'Hold on. Why is the Judge...'"));
  Serial.println(F("  20: AngryConfused - 'Why do YOU have HER phone?'"));
  Serial.println(F("  21: Explosive - 'IT LOOKS LIKE YOU WERE...'"));
  Serial.println(F("  22: Betrayed - 'I cannot BELIEVE this...'"));
  Serial.println(F("  23: Resigned - 'So what now?'"));
  Serial.println(F("========================================\n"));
}
