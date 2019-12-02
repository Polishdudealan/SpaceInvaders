#include "Player.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

Player::Player(): lives(3), Sprite(15, 14, 2, 2) {}

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
   
void Player::initialize(int x_arg, int y_arg) {
	x = x_arg;
	y = y_arg;
}

void Player::draw(RGBmatrixPanel& matrix) {
  draw_with_rgb(GREEN, matrix);
}

void Player::erase(RGBmatrixPanel& matrix) {
  draw_with_rgb(BLACK, matrix);
}

void Player::draw_with_rgb(Color color, RGBmatrixPanel& matrix) {
  matrix.drawPixel(x, y + 1, color.to_333());
  matrix.drawPixel(x + 1, y, color.to_333());
  matrix.drawPixel(x + 1, y + 1, color.to_333());
  matrix.drawPixel(x + 2, y + 1, color.to_333());
}
