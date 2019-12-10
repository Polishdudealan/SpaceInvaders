#include "Game.h"

Game::Game() {
  level = 0;
  time = 0;
  numUpdates = 0;
}

void Game::setupGame() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  player.powerup(NONE);
  delay(4000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  reset_level();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  score_board(player1Score, player2Score);

}

void Game::reset_level() {
  layers = 2;
  currentLayer = layers - 1;
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  level++;
  
  for (int i = 0; i < NUM_PLAYER_BALLS; i++) {
    player.balls[i].hit();
  }
  powerup.deactivate();
  
  //defines the strength of invaders
  int minStrength = level/5 + 1;
  int maxStrength = 3*sqrt(level);
  maxStrength = (minStrength < maxStrength) ? maxStrength : level/3 - 30;
  randomSeed(time % 100);
  int powerUpLocation = ((level % 3 == 0) ? random(0, NUM_ENEMIES) : NUM_ENEMIES + 1);
  for (int i = 0; i < layers; i++){
    for (int j = 0; j < 8; j++){
      if (i*8+j == powerUpLocation){
        enemies[i*8+j] = Invader(j * 4, i * 4 + 6, level < 5 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), true);
      } else {
        enemies[i*8+j] = Invader(j * 4, i * 4 + 6, level < 5 ? LEVEL_DATA[level-1][i][j] : random(minStrength, maxStrength), false);
      }
    }
  }


  int count = 0;
  for (int i = 0; i < NUM_PLAYER_BALLS; i++) {
    updatableSprites[count++] = &player.balls[i];
  }
  for (int i = 0; i < NUM_ENEMIES; i++) {
    updatableSprites[count++] = &enemies[i];
  }
  updatableSprites[count++] = &player;
  updatableSprites[count++] = &powerup;

  for (int i = 0; i < NUM_SPRITES; i++) {
    updatableSprites[i]->upd();
  }
    
  print_level(level);
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  print_lives(player.getLives());
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  score_board(player1Score, player2Score);
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
    if (powerup.check_active()){
      powerup.move();
      powerup.upd();
    }
  }
  
  //cannonball movements
  for (int i = 0; i < NUM_PLAYER_BALLS; i++){
    if (player.balls[i].hasBeenFired()){
      player.balls[i].move();
      player.balls[i].upd();
    }
  }
}

void Game::checkCollisions(){
  //loops through all the enemies
  for (int i = 0; i < NUM_ENEMIES; i++){
    for (int j = 0; j < NUM_PLAYER_BALLS; j++) { 
      Cannonball* ball = &player.balls[j];
      if (enemies[i].isColliding(*ball) && ball->hasBeenFired() && enemies[i].getStrength() != 0){
        enemies[i].hit();
        if (enemies[i].getStrength() == 0 && enemies[i].drops()){
           powerup.spawn(enemies[i].getX() + 1, enemies[i].getY(), random(0, NUM_P_TYPES));
           powerup.upd();
        }
        ball->hit();
        enemies[i].upd();
        ball->upd();
        //updates playerscore and refreshes scoreboard
        player1Score++;
        player2Score++;
        matrix.fillRect(0, 0, 32, 5, BLACK.to_333());
        score_board(player1Score, player2Score);//TODO fix for 2 players     
      }
    }
  }

  if (powerup.check_active() && powerup.isColliding(player)) {
    powerup.deactivate();
    powerup.upd();
    player.powerup(powerup.getType());
    player.upd();
  }

  // checks for enemies getting past player
  for (int i = 0; i < NUM_ENEMIES; i++) {           
    if ((enemies[i].getY() == 29 || player.isColliding(enemies[i])) && enemies[i].getStrength() > 0) {
      player.die();
      level--;
      if (player.getLives() <= 0) {
        player1Score = 0;
        player2Score = 0;
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
  potentiometer_value = 1024-potentiometer_value;
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
}

void Game::score_board(int score1, int score2){
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
