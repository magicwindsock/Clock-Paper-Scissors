#include <LiquidCrystal.h> // Include LiquidCrystal library

#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define DIAL_PIN A0  // Replace with the analog pin connected to the dial

const int numMatches = 10;
int currentMatch = 0;
int rewindCount = 0;  // Tracks how many times user rewinds

int playerChoice, arduinoChoice, winner;
int choiceSequence[numMatches];  // Stores the pre-generated sequence

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // LCD pin connections (modify based on your setup)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialize pins for player interaction (modify based on your setup)
  // ...

  lcd.begin(16, 2);  // Initialize LCD with 16 columns and 2 rows
  lcd.clear();       // Clear LCD display

  // Generate a random sequence of choices for the game
  for (int i = 0; i < numMatches; i++) {
    choiceSequence[i] = random(1, 4);
  }
}

void loop() {
  // Read player choice from external interaction (modify based on your setup)
  // playerChoice = readPlayerChoice();

  // Check if user wants to rewind (dial value below a threshold)
  int dialValue = analogRead(DIAL_PIN);
  if (dialValue < 100) {
    if (rewindCount < 3 && currentMatch > 0) {
      currentMatch = 0;
      rewindCount++;
    }
  } else {
    // Reset rewind counter if user stops rewinding
    rewindCount = 0;

    if (currentMatch < numMatches) {
      // Use pre-generated sequence for current match
      arduinoChoice = choiceSequence[currentMatch];

      // Display Arduino choice on LCD
      lcd.clear();
      switch (arduinoChoice) {
        case ROCK:
          lcd.print("Rock");
          break;
        case PAPER:
          lcd.print("Paper");
          break;
        case SCISSORS:
          lcd.print("Scissors");
          break;
      }
      delay(1000);  // Show Arduino choice for 1 second

      // Game logic (modify based on your interaction setup)
      // ...

      // Display winner (modify based on your interaction setup)
      // ...

      currentMatch++;
    } else {
      // All matches played, restart game with new sequence
      currentMatch = 0;
      for (int i = 0; i < numMatches; i++) {
        choiceSequence[i] = random(1, 4);
      }
    }
  }

  // Display score on LCD (modify based on your scoring logic)
  lcd.setCursor(0, 1);  // Set cursor to second row, first column
  lcd.print("Score: ");
  // Add your code to display player and computer score here

  delay(100); // Adjust delay based on your interaction and display needs
}
