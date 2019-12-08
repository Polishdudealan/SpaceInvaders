#include "Game.h"

Game::Game() {
  level = 0;
  time = 0;
  numUpdates = 0;
}

void Game::setupGame() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(4000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  reset_level();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void Game::reset_level() {
  layers = 2;
  currentLayer = layers - 1;
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  level++;
  
  for (int i = 0; i < NUM_BALLS; i++) {
    player.balls[i].hit();
  }
  
  //defines the strength of invaders
  int minStrength = level/5 + 1;
  int maxStrength = 3*sqrt(level);
  maxStrength = (minStrength < maxStrength) ? maxStrength : level/3 - 30;
  randomSeed(random(0,100));
  int powerUpLocation = ((level % 3 == 0) ? random(0, NUM_ENEMIES) : NUM_ENEMIES + 1);
  Serial.println(powerUpLocation, DEC);
  for (int i = 0; i < layers; i++){
    for (int j = 0; j < 8; j++){
      if (i*8+j == powerUpLocation){
        enemies[i*8+j] = Invader(j * 4, i * 4 + 5, level < 5 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), true);
      } else {
        enemies[i*8+j] = Invader(j * 4, i * 4 + 5, level < 5 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), false);
      }
    }
  }

  int count = 0;
  for (int i = 0; i < NUM_BALLS; i++) {
    updatableSprites[count++] = &player.balls[i];
  }
  for (int i = 0; i < NUM_ENEMIES; i++) {
    updatableSprites[count++] = &enemies[i];
  }
  updatableSprites[count++] = &player;
  for (int i = 0; i < NUM_POWERUPS; i++) {
    updatableSprites[count++] = &powerups[i];
  }
  for (int i = 0; i < NUM_SPRITES; i++) {
    updatableSprites[i]->upd();
  }
    
  print_level(level);
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  print_lives(player.getLives());
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void Game::inputUpdate(int potentiometer_value, bool button_pressed) { 
  player.reload();

  if (button_pressed) {
    player.fire();
  }

  // this allows for the potentiometer to be more narrow, only using the middle two quarters of its range to control the player
  int newX = (47 - potentiometer_value / 16) >= -1 ? ((47 - potentiometer_value / 16) < 31 ? (47 - potentiometer_value / 16) : 30 ): -1;
  
  // if position changed update
  if (newX != player.getX()) {
    player.setX(newX);
    player.upd();
  }
}

void Game::moveUpdate() {
  if (layerCleared(currentLayer)){
    currentLayer--;
  }
  
  // moves all enemies down the screen             
  if (time % INVADER_DELAY == 0) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
      // i / 8 is current layer
      if (currentLayer == i/8) {
        enemies[i].move();
        enemies[i].upd();
      }
    }
  }

  if (time % POWERUP_DELAY == 0) {
    for (int i = 0; i < NUM_POWERUPS; i++){
      if (powerups[i].check_active()){
        powerups[i].move();
        powerups[i].upd();
      }
    }
  }
  
  //cannonball movements
  for (int i = 0; i < NUM_BALLS; i++){
    if (player.balls[i].hasBeenFired()){
      player.balls[i].move();
      player.balls[i].upd();
    }
  }
}


void Game::checkCollisions(){
  //loops through all the enemies
  for (int i = 0; i < NUM_ENEMIES; i++){
    for (int j = 0; j < NUM_BALLS; j++) { 
      Cannonball* ball = &player.balls[j];
      if (enemies[i].isColliding(*ball) && ball->hasBeenFired() && enemies[i].getStrength() != 0){
        enemies[i].hit();
        if (enemies[i].getStrength() == 0 && enemies[i].drops()){
           Powerups* p = getPowerup();
           if (!p == NULL){
             p->spawn(enemies[i].getX(), enemies[i].getY(), random(0, NONE));
             p->upd();
           }
        }
        ball->hit();
        enemies[i].upd();
        ball->upd();
        break;          
      }
    }
  }

  for (int i = 0; i < NUM_POWERUPS; i++){
    if (powerups[i].check_active() && powerups[i].isColliding(player)) {
      powerups[i].deactivate();
      player.powerup(powerups[i].getType());
    }
  }

  // checks for enemies getting past player
  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 29 || player.isColliding(enemies[i])) && enemies[i].getStrength() > 0) {
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

void Game::redrawSprites(){
  for (int i = 0; i < NUM_SPRITES; i++) {
    updatableSprites[i]->redraw(matrix);
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

void Game::update(int potentiometer_value, bool button_pressed) { 
  time++;
  inputUpdate(potentiometer_value, button_pressed);
  moveUpdate();
  checkCollisions();
  redrawSprites();  
  
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

Powerups* Game::getPowerup() {
  for (int i = 0; i < NUM_BALLS; i++){
    if (!powerups[i].check_active()){
      return &powerups[i];
    }
  }
  return NULL;
}

void Game::print_level(int level) {
  matrix.setCursor(1, 0);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('L');
  matrix.print('E');
  matrix.print('V');
  matrix.print('E');
  matrix.print('L');

  matrix.setCursor(11, 9); // next line
  matrix.print((level / 10) + '0');
  matrix.print((level % 10) + '0');
}

void Game::print_lives(int lives) {
  matrix.setCursor(1, 0);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('L');
  matrix.print('I');
  matrix.print('V');
  matrix.print('E');
  matrix.print('S');

  matrix.setCursor(11, 9); // next line 
  matrix.print((lives / 10) + '0');
  matrix.print((lives % 10) + '0');
}

void Game::game_over() {
  matrix.setCursor(5, 0);
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
