#include "Player.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Player::Player(): lives(3), ballCycle(0), Sprite(15, 30, 3, 2) {}

int Player::getLives() const {
	return lives;
}
    
void Player::setX(int xArg) {
	x = xArg;
}

void Player::resetLives() {
	lives = 3;
}
    
void Player::die() {
	lives--; 
}

void Player::reload(){
  if (ballCycle < BALL_DELAY) {
    ballCycle++;
  }
}

void Player::powerup(PowerupType power){
  switch(power){
    case LIFE:
      lives1up();
      break;
  }
}

void Player::lives1up() {
  lives++; 
}

void Player::fire(){
  if (ballCycle == BALL_DELAY){
    Cannonball* ball = getBall();
    if (ball != NULL) {
      ball->fire(x + 1, y - 1);
      ballCycle = 0;
      ball->upd();
    }
  }
}
   
void Player::initialize(int x_arg, int y_arg) {
	x = x_arg;
	y = y_arg;
}

void Player::draw(Signal& matrix) {
  draw_with_rgb(GREEN, matrix);
}

Cannonball* Player::getBall() {
  for (int i = 0; i < NUM_BALLS; i++){
    if (!balls[i].hasBeenFired()){
      return &balls[i];
    }
  }
  return NULL;
}

void Player::draw_with_rgb(Color color, Signal& matrix) {
  matrix.drawPixel(x, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y, color.to_333());
  matrix.drawPixel(x + 1, y + 1, color.to_333());
  matrix.drawPixel(x + 2, y + 1, color.to_333());
}
