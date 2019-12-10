#include "Player.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Player::Player(): powerupAbility(NONE), lives(3), ballDelay(8), Sprite(15, 30, 3, 2) {}

void Player::reload(){
  if (ballCycle < ballDelay){
    ballCycle++;
  }
}

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

void Player::powerup(PowerupType power){
  if(power == LIFE){
    lives1up();
    return;
  }
  
  ballDelay = 8;
  if (power == RAPID_FIRE) {
    ballDelay = 4;
    ballCycle = 0;
  }
  powerupAbility = power;
  
}

void Player::lives1up() {
  lives++; 
}

void Player::initialize(int x_arg, int y_arg) {
	x = x_arg;
	y = y_arg;
}

void Player::draw(Signal& matrix) {
  Color bodyCol = GREEN;
  Color blasterCol = p_color(powerupAbility);
  
  matrix.drawPixel(x, y + 1, bodyCol.to_333());
  matrix.drawPixel(x + 1, y, blasterCol.to_333());
  matrix.drawPixel(x + 1, y + 1, bodyCol.to_333());
  matrix.drawPixel(x + 2, y + 1, bodyCol.to_333());
}

Cannonball* Player::getPlayerBall() {
  for (int i = 0; i < NUM_PLAYER_BALLS; i++){
    if (!balls[i].hasBeenFired()){
      return &balls[i];
    }
  }
  return NULL;
}

void Player::fire(){
  if (ballCycle == ballDelay) {
    Cannonball* ball = getPlayerBall();
    if (ball != NULL) {
      ball->fire(x + 1, y - 1);
      ballCycle = 0;
      ball->upd();
    }
  }
}
