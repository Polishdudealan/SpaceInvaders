#include "Player.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Player::Player(Color bodyColor = BLUE): bodyColor(bodyColor), powerupAbility(NONE), lives(3), ballDelay(8), specialDelay(100), Sprite(15, 30, 3, 2) {}

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
  if (powerupAbility == JUGGERNAUGHT) {
    lives = 0;
  }
}

void Player::powerup(PowerupType power){
  for (int i = 0; i < 50; i++){
    tone(PIEZOPIN, 500 + i, 10);
    delay(2);
  }
  if(power == LIFE){
    lives1up();
    return;
  }
  
  ballDelay = 8;
  ballCycle = 8;
  
  if (power == RAPID_FIRE) {
    ballDelay = 4;
    ballCycle = 0;
  } else if (power == BOMB_SHOT) {
    specialType = BOMB;
    specialDelay = 250;
    specialCycle = specialDelay;
  } else if (power == SNIPER) {
    specialType = SNIPE;
    specialDelay = 100;
    specialCycle = specialDelay;
  } else if (power == SCATTER_SHOT){
    specialType = STANDARD;
    ballDelay = 16;
    ballCycle = ballDelay;
  } else if (power == JUGGERNAUGHT) {
    specialType = STANDARD;
    ballDelay = 4;
    ballCycle = ballDelay;
  } else {
    specialDelay = 50;
    specialCycle = specialDelay;
    specialType = STRONG;
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
  if (!enabled) return;
  Color blasterCol = p_color(powerupAbility);
  
  matrix.drawPixel(x, y + 1, bodyColor.to_333());
  matrix.drawPixel(x + 1, y, blasterCol.to_333());
  matrix.drawPixel(x + 1, y + 1, bodyColor.to_333());
  matrix.drawPixel(x + 2, y + 1, bodyColor.to_333());
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
      ball->setType(powerupAbility == JUGGERNAUGHT ? JUGG : STANDARD);
      ball->fire(x + 1, y - 1);
      ballCycle = 0;
      ball->upd();
      // piezo sound effect
      for(int i = 0; i < 1000; i += 100){
      tone(PIEZOPIN, 4000 + i, 10);
      }
    }
    if (powerupAbility == SCATTER_SHOT) {
      for (int i = 0; i < 2; i++){
        Cannonball* ball = getPlayerBall();
        if (ball != NULL){
          ball->setType(STANDARD);
          ball->fire(x + 1, y - 1, !i, i);
          ballCycle = 0;
          ball->upd();      
        }
      }
    }
  }
}

void Player::specialFire(){
  if (specialCycle == specialDelay) {
    for(int i = 0; i < 1000; i += 100){
      tone(PIEZOPIN, 1000 + i, 10);
    }
    Cannonball* ball = getPlayerBall();
    if (ball != NULL) {
      ball->setType(specialType);
      ball->fire(x + 1, y - 1);
      specialCycle = 0;
      ball->upd();
    }
  }
  tone(PIEZOPIN, 700, 5);
}

PowerupType Player::getPowerup() {
  return powerupAbility;
}
