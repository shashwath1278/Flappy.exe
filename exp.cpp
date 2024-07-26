#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Define OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Reset pin (not used for I2C)
#define OLED_RESET -1

// Create an instance of the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Game variables
int birdY = SCREEN_HEIGHT / 2;
int birdVelocity = 0;
int gravity = 1;
int flapStrength = -6;
bool gameStarted = false;
bool gameOver = false;
int score = 0;

// Pipe variables
int pipeX = SCREEN_WIDTH;
int pipeGap = 24;
int pipeWidth = 10;
int pipeHeight = 30;

// Button pins
const int flapButton = 2;
const int resetButton = 3;

void setup() {
  pinMode(flapButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  // Initialize display
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  if (digitalRead(resetButton) == LOW) {
    resetGame();
  }

  if (gameOver) {
    displayGameOver();
    return;
  }

  if (digitalRead(flapButton) == LOW) {
    birdVelocity = flapStrength;
    gameStarted = true;
  }

  if (gameStarted) {
    birdVelocity += gravity;
    birdY += birdVelocity;

    if (birdY < 
