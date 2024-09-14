#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define EEPROM_SIZE 512  // Size of EEPROM memory
#define EEPROM_ADDR_HIGH_SCORE 0  // Address where high score will be stored

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 14; // D5 (GPIO14)

int birdY = SCREEN_HEIGHT / 2;
const int birdX = 10;
float birdVelocity = 0;
const float gravity = 0.5f;
const float jumpStrength = -4.0f;
const float maxVelocity = 4.0f;

int pipeX = SCREEN_WIDTH;
int pipeGap = 40; // Starting with a large gap
int pipeHeight = 30;
float pipeSpeed = 1.0f; // Starting speed of the pipe

bool gameOver = false;
int score = 0;
int highScore = 0; // Variable to store the best record
unsigned long gameStartTime = 0;

// Difficulty parameters
const float maxPipeSpeed = 10.0f;  // Max pipe speed
const int minPipeGap = 15;  // Minimum pipe gap for higher difficulty
const float speedIncreaseFactor = 1.0f;  // Speed increase for pipes
const float gapDecreaseFactor = 1.5f;  // Reduction in pipe gap
const unsigned long difficultyIncreaseInterval = 3000; // Difficulty increase every 3 seconds

bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setupDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
	Serial.println(F("SSD1306 allocation failed"));
	while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, SCREEN_HEIGHT / 2 - 10);
  display.print("Press to Start");
  display.display();
 
  while (digitalRead(buttonPin) == HIGH);
  delay(200);  // Debounce
  display.clearDisplay(); // Clear the screen
}

void flipScreen() {
  //display.setRotation(2);  // Flip screen by 180 if u need
}

// EEPROM
void readHighScoreFromEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  highScore = EEPROM.read(EEPROM_ADDR_HIGH_SCORE);
 
  if (highScore == 255) {
	highScore = 0;  // 
  }
}

// EEPROM2
void saveHighScoreToEEPROM(int newHighScore) {
  EEPROM.write(EEPROM_ADDR_HIGH_SCORE, newHighScore);
  EEPROM.commit();
}

// Function dispay
void updateDisplay() {
  display.clearDisplay();
 
  display.fillCircle(birdX + 4, birdY + 4, 4, SSD1306_WHITE);
  display.drawRect(pipeX, 0, 10, pipeHeight, SSD1306_WHITE);
  display.fillRect(pipeX + 1, 0, 8, pipeHeight, SSD1306_WHITE);
  display.drawRect(pipeX, pipeHeight + pipeGap, 10, SCREEN_HEIGHT - pipeHeight - pipeGap, SSD1306_WHITE);
  display.fillRect(pipeX + 1, pipeHeight + pipeGap, 8, SCREEN_HEIGHT - pipeHeight - pipeGap, SSD1306_WHITE);
 
  display.setTextSize(1);
 
  // Show current score
  display.setCursor(0, 0);
  display.print("Score : ");
  display.print(score);
 
  // Show high score
  display.setCursor(0, 10);
  display.print("Best  : ");
  display.print(highScore);
 
  // If the game is over, show "Game Over" message
  if (gameOver) {
	display.setCursor(30, SCREEN_HEIGHT / 2 - 8);
	display.setTextSize(1);
	display.print("Game Over!");
    
	display.setCursor(20, SCREEN_HEIGHT / 2 + 10);
	display.setTextSize(1);
	display.print("Press to Restart");
  }
 
  display.display();
}

// Function to increase difficulty over time
void increaseDifficulty() {
  unsigned long gameTime = millis() - gameStartTime;
  float difficultyLevel = static_cast<float>(gameTime) / difficultyIncreaseInterval;
  pipeSpeed = min(maxPipeSpeed, 2.5f + difficultyLevel * speedIncreaseFactor);
  pipeGap = max(minPipeGap, static_cast<int>(40 - difficultyLevel * gapDecreaseFactor));
}

// Function Main
void gameLogic() {
  
  birdVelocity += gravity;
  if (birdVelocity > maxVelocity) birdVelocity = maxVelocity;
  birdY += static_cast<int>(birdVelocity);

  if (birdY <= 0) {
	birdY = 0;
  }
 
  if (birdY >= SCREEN_HEIGHT - 8) {
	birdY = SCREEN_HEIGHT - 8;
	gameOver = true;
  }

  pipeX -= static_cast<int>(pipeSpeed);

  if (pipeX < -10) {
	pipeX = SCREEN_WIDTH;
	pipeHeight = random(10, SCREEN_HEIGHT - pipeGap - 10);
	score++;
	increaseDifficulty();  // Increase difficulty
  }

  // Check for collision
  if ((birdX + 8 > pipeX && birdX < pipeX + 10) &&
  	(birdY < pipeHeight || birdY + 8 > pipeHeight + pipeGap)) {
	gameOver = true;

	if (score > highScore) {
  	highScore = score;
  	saveHighScoreToEEPROM(highScore);  // Save to EEPROM
	}
  }
}

void checkButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
	lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
	if (reading != currentButtonState) {
  	currentButtonState = reading;
  	if (currentButtonState == LOW) {
    	birdVelocity = jumpStrength;  // Jump when button is pressed
  	}
	}
  }

  lastButtonState = reading;
}

// Reset Stat
void resetGame() {
  birdY = SCREEN_HEIGHT / 2;
  birdVelocity = 0;
  pipeX = SCREEN_WIDTH;
  pipeSpeed = 1.0f;
  pipeGap = 40;
  score = 0;
  gameOver = false;
  gameStartTime = millis();
}

// Setup
void setup() {
  Serial.begin(115200);
  Wire.begin(0, 2);
  EEPROM.begin(EEPROM_SIZE); // Initialize EEPROM
  readHighScoreFromEEPROM(); // Load the saved high score from EEPROM
  setupDisplay();
  flipScreen(); // Flip the screen if needed
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Flappy Bird Setup Completed");
  gameStartTime = millis();
}

// Main game loop
void loop() {
  if (!gameOver) {
	checkButton();
	gameLogic();
	updateDisplay();
	delay(30);
  } else {
	// Wait for the restart
	if (digitalRead(buttonPin) == LOW) {
  	resetGame();
  	delay(200);  // Debounce 
	}
  }
}
