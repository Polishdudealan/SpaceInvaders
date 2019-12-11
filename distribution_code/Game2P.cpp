#include "Game2P.h"

Game2P::Game2P() {
  level = 0;
  time = 0;
  numUpdates = 0;
  for (int i = 0; i < NUM_ENEMY_BALLS; i++){
    enemyBalls[i].setType(INVADER);
  }
}

void Game2P::setupGame() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  player1.powerup(NONE);
  player2.powerup(NONE);
  delay(4000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  reset_level();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  score_board(player1Score, player2Score);
}

void Game2P::reset_level() {
  layers = 3;
  currentLayer = layers - 1;
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  level++;
  
  for (int i = 0; i < NUM_PLAYER_BALLS; i++) {
    player1.balls[i].reset();
    player2.balls[i].reset();
  }
  powerup.deactivate();
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {
    enemyBalls[i].reset();
  }
  
  //defines the strength of invaders
  int minStrength = level/5 + 1;
  int maxStrength = 3*sqrt(level);
  maxStrength = (minStrength < maxStrength) ? maxStrength : level/3 - 30;
  randomSeed(time % 100);
  int powerUpLocation = ((level % 3 == 0) ? random(0, NUM_ENEMIES) : NUM_ENEMIES + 1);
  for (int i = 0; i < layers; i++){
    for (int j = 0; j < 8; j++){
      if (i*8+j == powerUpLocation){
        enemies[i*8+j] = Invader(j * 4, i * 4 + 6, level < NUM_SCRIPTED_LEVELS + 1 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), true);
      } else {
        enemies[i*8+j] = Invader(j * 4, i * 4 + 6, level < NUM_SCRIPTED_LEVELS + 1 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), false);
      }
    }
  }

  int count = 0;
  for (int i = 0; i < NUM_PLAYER_BALLS; i++) {
    updatableSprites[count++] = &player1.balls[i];
    updatableSprites[count++] = &player2.balls[i];
  }
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {
    updatableSprites[count++] = &enemyBalls[i];
  }
  for (int i = 0; i < NUM_ENEMIES; i++) {
    updatableSprites[count++] = &enemies[i];
  }
  updatableSprites[count++] = &player1;
  updatableSprites[count++] = &player2;
  updatableSprites[count++] = &powerup;

  for (int i = 0; i < NUM_SPRITES; i++) {
    updatableSprites[i]->upd();
  }
    
  print_level(level);
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  print_lives(player1.getLives());
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  score_board(player1Score, player2Score);
} 

void Game2P::inputUpdate(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed) {
  player1.reload();
  player2.reload();
  if (left_regular_pressed) {
    player1.fire();
  }
  if (left_special_pressed){
    player1.specialFire();
  }
  if (right_regular_pressed) {
    player2.fire();
  }
  if (right_special_pressed){
    player2.specialFire();
  }
  
  // this allows for the potentiometer to be more narrow, only using the middle two quarters of its range to control the player1
  int newX1 = (47 - left_potentiometer_value / 16) >= -1 ? ((47 - left_potentiometer_value / 16) < 31 ? (47 - left_potentiometer_value / 16) : 30 ): -1;
  
  // if position changed update
  if (newX1 != player1.getX()) {
    player1.setX(newX1);
    player1.upd();
  }

  int newX2 = (47 - right_potentiometer_value / 16) >= -1 ? ((47 - right_potentiometer_value / 16) < 31 ? (47 - right_potentiometer_value / 16) : 30 ): -1;
  
  // if position changed update
  if (newX2 != player2.getX()) {
    player2.setX(newX2);
    player2.upd();
  }
}

void Game2P::moveUpdate() {
  if (layerCleared(currentLayer)){
    currentLayer--;
  }
  
  // moves all enemies down the screen             
  if (time % INVADER_DELAY == 0) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
      // i / 8 is current layer
      if (currentLayer == i/8 && enemies[i].getHP() > 0) {
        enemies[i].move();
        enemies[i].upd();
      }
    }
  }
  
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {
    enemyBalls[i].tick();
    enemyBalls[i].upd();
  }
  

  int invaderShootSeed = random(0, INVADER_SHOOT_PROBABILITY);
  for (int i = 0; i < NUM_ENEMIES; i++){
    if (enemies[i].getHP() > 0 && enemies[i].fire(invaderShootSeed)){
      Cannonball* ball = getEnemyCannonball();
      if (ball != NULL){
        ball->fire(enemies[i].getX() + 1, enemies[i].getY() + 3);
        ball->upd();
      }
    }
  }

  if (time % POWERUP_DELAY == 0) {
    if (powerup.check_active()){
      powerup.move();
      powerup.upd();
    }
  }
  
  //cannonball movements
  for (int i = 0; i < NUM_PLAYER_BALLS; i++){
    if (player1.balls[i].hasBeenFired()){
      player1.balls[i].tick();
      player1.balls[i].upd();
    }
    if (player2.balls[i].hasBeenFired()){
      player2.balls[i].tick();
      player2.balls[i].upd();
    } 
  }
}

void Game2P::checkCollisions(){
  //loops through all the enemies
  for (int i = 0; i < NUM_ENEMIES; i++){
    for (int j = 0; j < NUM_PLAYER_BALLS; j++) {
      for (int k = 0; k < NUM_PLAYERS; k++) {
        Cannonball* ball;
        if (k == 0) {
          ball = &player1.balls[j];
        } else {
          ball = &player2.balls[j];
        }
        if (enemies[i].isColliding(*ball) && ball->hasBeenFired() && enemies[i].getHP() != 0){
          enemies[i].hit();
          if (enemies[i].getHP() == 0 && enemies[i].drops()){
             powerup.spawn(enemies[i].getX() + 1, enemies[i].getY(), random(0, NUM_P_TYPES));
             powerup.upd();
          }
          ball->hit();
          enemies[i].upd();
          ball->upd();
          //updates player1score and refreshes scoreboard
          if (k == 0) {
            player1Score++;
          } else {
            player2Score++;            
          }
          matrix.fillRect(0, 0, 32, 5, BLACK.to_333());
          score_board(player1Score, player2Score);//TODO fix for 2 player1s   
        }
      }
    }
  }

  if (powerup.check_active() && powerup.isColliding(player1)) {
    powerup.deactivate();
    powerup.upd();
    player1.powerup(powerup.getType());
    player1.upd();
  }

  if (powerup.check_active() && powerup.isColliding(player2)) {
    powerup.deactivate();
    powerup.upd();
    player2.powerup(powerup.getType());
    player2.upd();
  }

  // checks for enemies getting past player1
  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 29 || (player1.isColliding(enemies[i])) && enemies[i].getHP() > 0)) {
      player1.die();
      level--;
      if (player1.getLives() <= 0) {
        game_over();
      }
      reset_level();
      return;
    }
  }

  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 29 || (player2.isColliding(enemies[i])) && enemies[i].getHP() > 0)) {
      player2.die();
      level--;
      if (player2.getLives() <= 0) {
        game_over();
      }
      reset_level();
      return;
    }
  }

  // checks for enemies shooting players
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {           
    if (player1.isColliding(enemyBalls[i]) && enemyBalls[i].hasBeenFired()) {
      player1.die();
      level--;
      if (player1.getLives() <= 0) {
        game_over();
      }
      reset_level();
      return;
    }
  }
}

void Game2P::redrawSprites(){
  for (int i = 0; i < NUM_SPRITES; i++) {
    updatableSprites[i]->redraw(matrix);
  }
}

bool Game2P::level_cleared() {
  for (int i = 0; i < layers; i++){
    if (!layerCleared(i)){
      return false;
    }
  }
  return true;
}

bool Game2P::layerCleared(int layer){
  for (int i = layer * NUM_ENEMIES / layers; i < (layer + 1) * NUM_ENEMIES / layers; i++) {
    if (enemies[i].getHP() > 0) return false;
  }
  return true;
}

void Game2P::update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed) { 
  time++;
  left_potentiometer_value = 1024-left_potentiometer_value;
  inputUpdate(left_potentiometer_value, left_regular_pressed, left_special_pressed, right_potentiometer_value, right_regular_pressed, right_special_pressed);
  moveUpdate();
  checkCollisions();
  
  if (player1.getLives() < 1) {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    player1.resetLives();
    level = 0;
    game_over();
    delay(4000);
    setupGame();  
  }   

  if (level_cleared()){
    reset_level();
  }

  redrawSprites();  
}  
  

void Game2P::print_level(int level) {
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

void Game2P::print_lives(int lives) {
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

void Game2P::game_over() {
  //draws scoreboard line
  int score1 = player1Score;
  int score2 = player2Score;

  //converts int score to array of place values
  int value1[4];
  int value2[4];
  for (int i = 3; i >= 0; i--) {
    value1[i] = score1 % 10;
    value2[i] = score2 % 10;
    score1 /= 10;
    score2 /= 10;
  }

  //prints numbers as characters 
  Font::printCharacter('P', 0, 16, AQUA.to_333(), matrix);
  Font::printCharacter(1, 4, 16, AQUA.to_333(), matrix);
  Font::printCharacter('P', 23, 16, AQUA.to_333(), matrix);
  Font::printCharacter(2, 27, 16, AQUA.to_333(), matrix);
  for (int i = 0; i < 4; i++) {
    Font::printCharacter(value1[i], 0 + 4 * i, 22, DAMPWHITE.to_333(), matrix);
    Font::printCharacter(value2[i], 17 + 4 * i, 22, DAMPWHITE.to_333(), matrix);
  }
  
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

  //resets easter egg game speed
  boardComputationDelay = 30;
  gameOver = true;
  delay(5000);
}

void Game2P::score_board(int score1, int score2){
  //draws scoreboard line
  matrix.fillRect(0, 5, 16, 1, DAMPBLUE.to_333());
  matrix.fillRect(15, 0, 1, 5, DAMPBLUE.to_333());
  matrix.fillRect(16, 5, 16, 1, DAMPRED.to_333());
  matrix.fillRect(16, 0, 1, 5, DAMPRED.to_333());

  //converts int score to array of place values
  int value1[4];
  int value2[4];
  for (int i = 3; i >= 0; i--) {
    value1[i] = score1 % 10;
    value2[i] = score2 % 10;
    score1 /= 10;
    score2 /= 10;
  }

  //prints numbers as characters 
  for (int i = 0; i < 4; i++) {
    Font::printCharacter(value1[i], 0 + 4 * i, 0, DAMPWHITE.to_333(), matrix);
    Font::printCharacter(value2[i], 17 + 4 * i, 0, DAMPWHITE.to_333(), matrix);
  }
  
}

Cannonball* Game2P::getEnemyCannonball() {
  for (int i = 0; i < NUM_ENEMY_BALLS; i++){
    if (!enemyBalls[i].hasBeenFired()){
      return &enemyBalls[i];
    }
  }
  return NULL;
}
