#include "Player.h"
#include "Cannonball.h"
#include "Invader.h"
#include "Game.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;


// a global variable that represents the game Space Invaders
Game game;

// see https://www.arduino.cc/reference/en/language/structure/sketch/setup/
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1_PIN_NUMBER, INPUT);
  pinMode(BUTTON2_PIN_NUMBER, INPUT);
  pinMode(BUTTON3_PIN_NUMBER, INPUT);
  pinMode(BUTTON4_PIN_NUMBER, INPUT);
  game.setupGame();
}


// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int left_potentiometer = analogRead(POTENTIOMETER1_PIN_NUMBER);
  bool left_regular = (digitalRead(BUTTON1_PIN_NUMBER) == HIGH);
  bool left_special = (digitalRead(BUTTON2_PIN_NUMBER) == HIGH);
  int right_potentiometer = analogRead(POTENTIOMETER2_PIN_NUMBER);
  bool right_special = (digitalRead(BUTTON3_PIN_NUMBER) == HIGH);
  bool right_regular = (digitalRead(BUTTON4_PIN_NUMBER) == HIGH);

  //todo implement game select
  game.update(left_potentiometer, left_regular);
  delay(30);
}
