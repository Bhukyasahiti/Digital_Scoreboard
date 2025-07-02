#include <BluetoothSerial.h>
#include <LedControl.h>
#include <Preferences.h>

// Create BluetoothSerial instance
BluetoothSerial SerialBT;

// Create a LedControl instance (DIN, CLK, CS, number of MAX7219 chips)
LedControl lc = LedControl(23, 18, 5, 1);

// Preferences instance for persistent storage
Preferences preferences;

// Variables to hold scores
int player1Score = 0; // Player 1's score (0-9999)
int player2Score = 0; // Player 2's score (0-9999)

// Pin assignments
const int buzzerPin = 15;       // Buzzer pin
const int player1Button = 26;  // Pushbutton for Player 1
const int player2Button = 27;  // Pushbutton for Player 2
const int resetButton = 25;    // Reset button

// Function declarations
void displayScores();
void incrementPlayer1();
void incrementPlayer2();
void decrementPlayer1();
void decrementPlayer2();
void resetScores();
void loadScores();
void saveScores();
void soundBuzzer();

void setup() {
  // Initialize Bluetooth
  SerialBT.begin("ESP32_Scoreboard"); // Bluetooth device name
  Serial.begin(115200);              // Serial monitor for debugging
  Serial.println("Bluetooth initialized. Waiting for commands...");

  // Initialize the MAX7219
  lc.shutdown(0, false);         // Wake up the MAX7219
  lc.setIntensity(0, 8);         // Set brightness level (0-15)
  lc.clearDisplay(0);            // Clear display register

  // Initialize Preferences library and load stored scores
  preferences.begin("scoreboard", false);
  loadScores(); // Load scores from memory

  // Initialize buzzer and buttons
  pinMode(buzzerPin, OUTPUT);
  pinMode(player1Button, INPUT_PULLUP);
  pinMode(player2Button, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  // Display initial scores
  displayScores();
}

void loop() {
  // Check for Bluetooth commands
  if (SerialBT.available()) {
    String command = SerialBT.readString();
    command.trim(); // Remove any leading/trailing whitespace
    Serial.println("Received: " + command);

    if (command == "P1+") {
      incrementPlayer1();
    } else if (command == "P2+") {
      incrementPlayer2();
    } else if (command == "P1-") {
      decrementPlayer1();
    } else if (command == "P2-") {
      decrementPlayer2();
    } else if (command == "RESET") {
      resetScores();
    } else {
      Serial.println("Invalid command. Use P1+, P2+, P1-, P2-, or RESET.");
    }
  }

  // Check for pushbutton inputs
  if (digitalRead(player1Button) == LOW) {
    incrementPlayer1();
    delay(300); // Debounce delay
  }
  if (digitalRead(player2Button) == LOW) {
    incrementPlayer2();
    delay(300); // Debounce delay
  }

  // Check for reset button input
  if (digitalRead(resetButton) == LOW) {
    resetScores();
    delay(300); // Debounce delay
  }
}

// Function to display scores on the MAX7219
void displayScores() {
  lc.clearDisplay(0); // Clear the display before updating

  // Display Player 2's score on the first 4 segments
  int tempScore = player2Score;
  for (int i = 0; i < 4; i++) {
    int digit = tempScore % 10;
    lc.setDigit(0, i, digit, false);
    tempScore /= 10;
  }

  // Display Player 1's score on the last 4 segments
  tempScore = player1Score;
  for (int i = 4; i < 8; i++) {
    int digit = tempScore % 10;
    lc.setDigit(0, i, digit, false);
    tempScore /= 10;
  }
}

// Function to increment Player 1's score
void incrementPlayer1() {
  if (player1Score < 9999) {
    player1Score++;
    displayScores();
    saveScores(); // Save updated scores
    soundBuzzer(); // Sound buzzer
    Serial.println("Player 1 score incremented.");
  } else {
    Serial.println("Player 1's score is already at the maximum (9999).");
  }
}

// Function to increment Player 2's score
void incrementPlayer2() {
  if (player2Score < 9999) {
    player2Score++;
    displayScores();
    saveScores(); // Save updated scores
    soundBuzzer(); // Sound buzzer
    Serial.println("Player 2 score incremented.");
  } else {
    Serial.println("Player 2's score is already at the maximum (9999).");
  }
}

// Function to decrement Player 1's score
void decrementPlayer1() {
  if (player1Score > 0) {
    player1Score--;
    displayScores();
    saveScores(); // Save updated scores
    Serial.println("Player 1 score decremented.");
  } else {
    Serial.println("Player 1's score is already at the minimum (0).");
  }
}

// Function to decrement Player 2's score
void decrementPlayer2() {
  if (player2Score > 0) {
    player2Score--;
    displayScores();
    saveScores(); // Save updated scores
    Serial.println("Player 2 score decremented.");
  } else {
    Serial.println("Player 2's score is already at the minimum (0).");
  }
}

// Function to reset both scores to 0
void resetScores() {
  player1Score = 0;
  player2Score = 0;
  displayScores();
  saveScores(); // Save reset scores
  soundBuzzer(); // Sound buzzer
  Serial.println("Scores reset to 0.");
}

// Function to load scores from memory
void loadScores() {
  player1Score = preferences.getInt("player1Score", 0); // Default to 0 if not set
  player2Score = preferences.getInt("player2Score", 0); // Default to 0 if not set
  Serial.println("Scores loaded from memory.");
}

// Function to save scores to memory
void saveScores() {
  preferences.putInt("player1Score", player1Score);
  preferences.putInt("player2Score", player2Score);
  Serial.println("Scores saved to memory.");
}

// Function to sound the buzzer
void soundBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100); // Buzzer on for 100 ms
  digitalWrite(buzzerPin, LOW);
}