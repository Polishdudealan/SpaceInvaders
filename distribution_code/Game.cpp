#include "Game.h"

Game::Game() {
  level = 0;
  time = 0;
  numUpdates = 0;
  for (int i = 0; i < NUM_ENEMY_BALLS; i++){
    enemyBalls[i].setType(INVADER);
  }
}

void Game::setupGame() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  player1.powerup(NONE);
  reset_level();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  score_board(player1Score);
}

void Game::reset_level() {
  layers = 3;
  currentLayer = layers - 1;
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  level++;
  
  for (int i = 0; i < NUM_PLAYER_BALLS; i++) {
    player1.balls[i].reset();
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
  int timeout = 0;
  while (LEVEL_DATA[level][powerUpLocation/8][powerUpLocation % 8] == 0 && timeout < 100) {
    powerUpLocation = ((level % 3 == 0) ? random(0, NUM_ENEMIES) : NUM_ENEMIES + 1);
    timeout++;
  }
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
  }
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {
    updatableSprites[count++] = &enemyBalls[i];
  }
  for (int i = 0; i < NUM_ENEMIES; i++) {
    updatableSprites[count++] = &enemies[i];
  }
  updatableSprites[count++] = &player1;
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
  score_board(player1Score);
} 

void Game::inputUpdate(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed) {
  player1.reload();
  if (left_regular_pressed) {
    player1.fire();
  }
  if (left_special_pressed){
    player1.specialFire();
  }

  // this allows for the potentiometer to be more narrow, only using the middle two quarters of its range to control the player1
  int newX = (47 - left_potentiometer_value / 16) >= -1 ? ((47 - left_potentiometer_value / 16) < 31 ? (47 - left_potentiometer_value / 16) : 30 ): -1;
  
  // if position changed update
  if (newX != player1.getX()) {
    player1.setX(newX);
    player1.upd();
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
  }
}

void Game::checkCollisions(){
  //loops through all the enemies
  for (int i = 0; i < NUM_ENEMIES; i++){
    for (int j = 0; j < NUM_PLAYER_BALLS; j++) { 
      Cannonball* ball = &player1.balls[j];
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
        player1Score++;
        player2Score++;
        matrix.fillRect(0, 0, 32, 5, BLACK.to_333());
        score_board(player1Score);//TODO fix for 2 player1s     
      }
    }
  }

  if (powerup.check_active() && powerup.isColliding(player1)) {
    powerup.deactivate();
    powerup.upd();
    player1.powerup(powerup.getType());
    player1.upd();
  }

  // checks for enemies getting past player1
  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 29 || (player1.isColliding(enemies[i])) && enemies[i].getHP() > 0)) {
      player1.die();
      level--;
      if (player1.getLives() <= 0) {
        game_over();
        return;
      }
      reset_level();
      return;
    }
  }

  // checks for enemies getting past player1
  for (int i = 0; i < NUM_ENEMY_BALLS; i++) {           
    if (player1.isColliding(enemyBalls[i]) && enemyBalls[i].hasBeenFired()) {
      player1.die();
      level--;
      if (player1.getLives() <= 0) {
        game_over();
        return;
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
    if (enemies[i].getHP() > 0) return false;
  }
  return true;
}

void Game::update(int left_potentiometer_value, bool left_regular_pressed, bool left_special_pressed, int right_potentiometer_value, bool right_regular_pressed, bool right_special_pressed) { 
  Serial.println("Loop");
  time++;
  left_potentiometer_value = 1024-left_potentiometer_value;
  inputUpdate(left_potentiometer_value, left_regular_pressed, left_special_pressed, right_potentiometer_value, right_regular_pressed, right_special_pressed);
  moveUpdate();
  checkCollisions();

  if (level_cleared()){
    reset_level();
  }

  redrawSprites();  
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
  matrix.fillScreen(BLACK.to_333());
  int score1 = player1Score;

  //converts int score to array of place values
  int value1[4];
  for (int i = 3; i >= 0; i--) {
    value1[i] = score1 % 10;
    score1 /= 10;
  }
 
  for (int i = 0; i < 4; i++) {
    Font::printCharacter(value1[i], 8 + 4 * i, 22, DAMPWHITE.to_333(), matrix);
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

void Game::score_board(int score1){
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
    //value2[i] = score2 % 10;
    score1 /= 10;
    //score2 /= 10;
  }

  //prints numbers as characters 
  for (int i = 0; i < 4; i++) {
    Font::printCharacter(value1[i], 0 + 4 * i, 0, DAMPWHITE.to_333(), matrix);
    //Font::printCharacter(value2[i], 17 + 4 * i, 0, DAMPWHITE.to_333(), matrix);
  }
  
}

Cannonball* Game::getEnemyCannonball() {
  for (int i = 0; i < NUM_ENEMY_BALLS; i++){
    if (!enemyBalls[i].hasBeenFired()){
      return &enemyBalls[i];
    }
  }
  return NULL;
}
