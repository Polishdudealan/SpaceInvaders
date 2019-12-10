#include "Player.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Player::Player(): powerupAbility(NONE), lives(3), ballDelay(8), specialDelay(100), Sprite(15, 30, 3, 2) {}

void Player::reload(){
  if (ballCycle < ballDelay){
    ballCycle++;
  }
  if (specialCycle < specialDelay) {
    specialCycle++;
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
  powerupAbility = power;
  specialType = STANDARD;

  if(power == LIFE){
    lives1up();
    return;
  }
  
  ballDelay = 8;
  if (power == RAPID_FIRE) {
    ballDelay = 4;
    ballCycle = 0;
  } else if (power = BOMB_SHOT) {
    specialType = BOMB;
    specialCycle = 0;
    specialDelay = 250;
  }
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
      ball->setType(STANDARD);
      ball->fire(x + 1, y - 1);
      ballCycle = 0;
      ball->upd();
    }
  }
}

void Player::specialFire(){
  if (powerupAbility == NONE || powerupAbility == LIFE) return;
  if (specialCycle == specialDelay) {
    Cannonball* ball = getPlayerBall();
    if (ball != NULL) {
      ball->setType(specialType);
      ball->fire(x + 1, y - 1);
      specialCycle = 0;
      ball->upd();
    }
  }
}
