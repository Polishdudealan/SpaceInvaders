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
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  pinMode(
  game.setupGame();
}


// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  game.update(potentiometer_value, button_pressed);
  delay(30);
}
