#include "Game.h"

Game::Game() {
  level = 0;
  time = 0;
  ballCycle = 0;
  numUpdates = 0;
}

void Game::setupGame() {
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(4000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  reset_level();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void Game::update(int potentiometer_value, bool button_pressed) {
  time++;
  inputUpdate(potentiometer_value, button_pressed);
  moveUpdate();
  checkCollisions();
  
  if (player.getLives() < 1) {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    player.resetLives();
    level = 0;
    game_over();
    delay(4000);
    setupGame();  
  }
   
  // checks if level is cleared
  if(level_cleared()){
    reset_level();     
  }
}

void Game::inputUpdate(int potentiometer_value, bool button_pressed) { 
  if (ballCycle < BALL_DELAY) {
    ballCycle++;
  }

  if (button_pressed && ballCycle == BALL_DELAY) {
    Cannonball* ball = getBall();
    if (ball != NULL) {
      ball->fire(player.getX(), player.getY());
      ballCycle = 0;
      ball->draw(matrix);
    }
  }

  // this allows for the potentiometer to be more narrow, only using the middle two quarters of its range to control the player
  int newX = (47 - potentiometer_value / 16) >= -1 ? ((47 - potentiometer_value / 16) < 31 ? (47 - potentiometer_value / 16) : 30 ): -1;
  
  // if position changed update
  if (newX != player.getX()) {
    player.erase(matrix);
    player.setX(newX);
    player.draw(matrix);
  }
}

void Game::moveUpdate() {
  // moves all enemies down the screen             
  if (time % INVADER_DELAY == 0) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
      // i / 8 is current layer
      if (currentLayer == i/8) {
        enemies[i].erase(matrix);
        enemies[i].move();
        enemies[i].draw(matrix);
      }
    }
  }
  
  //cannonball movements
  for (int i = 0; i < NUM_BALLS; i++){
    if (balls[i].hasBeenFired()){
      balls[i].erase(matrix);
      balls[i].move();
      balls[i].draw(matrix);
    }
  }
}


void Game::checkCollisions(){
  //loops through all the enemies
  for (int i = 0; i < NUM_ENEMIES; i++){
    for (int j = 0; j < NUM_BALLS; j++) { 
      Cannonball* ball = &balls[j];
      if (enemies[i].isColliding(*ball) && ball->hasBeenFired() && enemies[i].getStrength() != 0){
        enemies[i].hit(); 
        ball->hit();
        break;          
      }
    }
  }

  // checks for enemies getting past player
  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 13 || player.isColliding(enemies[i])) && enemies[i].getStrength() > 0) {
      player.die();
      level--;
      if (player.getLives() <= 0) {
        level = 0;
        game_over();
      }
      reset_level();
      return;
    }
  }
}

bool Game::level_cleared() {
  for (int i = 0; i < layers; i++){
    if (!layerCleared(i)){
      return false;
    }
  }
  return true;
}

bool Game::layerCleared(int layer){
  for (int i = layer * NUM_ENEMIES / layers; i < (layer + 1) * NUM_ENEMIES / layers; i++) {
    if (enemies[i].getStrength() > 0) return false;
  }
  return true;
}

void Game::reset_level() {
  layers = currentLayer = 2;
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  level++;
  ballCycle = BALL_DELAY;
  int minStrength = level/5 + 1;
  int maxStrength = 3*sqrt(level);
  maxStrength = (minStrength < maxStrength) ? maxStrength : level/3 - 30;
  for (int i = 0; i < layers; i++){
    for (int j = 0; j < 8; j++){
      enemies[i*8+j] = Invader(j * 4, i * 4, level < 5 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength));
    }
  }
  print_level(level);
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  print_lives(player.getLives());
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

Cannonball* Game::getBall() {
  for (int i = 0; i < NUM_BALLS; i++){
    if (!balls[i].hasBeenFired()){
      return &balls[i];
    }
  }
  return NULL;
}

void Game::print_level(int level) {
  matrix.setCursor(1, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('L');
  matrix.print('E');
  matrix.print('V');
  matrix.print('E');
  matrix.print('L');

  matrix.setCursor(13, 9); // next line
  matrix.print(level);
}

void Game::print_lives(int lives) {
  matrix.setCursor(1, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('L');
  matrix.print('I');
  matrix.print('V');
  matrix.print('E');
  matrix.print('S');

  matrix.setCursor(14, 9); // next line
  matrix.print(lives);
}

void Game::game_over() {
  matrix.setCursor(5, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  
  matrix.setCursor(5, 9); // next line
  matrix.print('O');
  matrix.print('V');
  matrix.print('E');
  matrix.print('R');
}
