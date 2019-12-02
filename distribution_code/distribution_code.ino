#ifndef LIBRARIES
  #define LIBRARIES
  #include <gamma.h>
  #include <RGBmatrixPanel.h>
  #include <Adafruit_GFX.h>
#endif

#include "Player.h"
#include "Cannonball.h"
#include "Invader.h"

#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Game {
  public:
    Game() {
      level = 0;
      time = 0;
      ballCycle = 0;
    }
      
    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    void setupGame() {
      matrix.begin();
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(4000);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      reset_level();
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      drawAllEnemies();
    }
      
    // advances the game simulation one step and renders the graphics
    // see spec for details of game
    // Modifies: global variable matrix
    void update(int potentiometer_value, bool button_pressed) {
      time++;
      player.erase(matrix);
      updateBalls();
          
    	if (ballCycle < BALL_DELAY) {
    		ballCycle++;
    	}
    	
    	if (button_pressed && ballCycle == BALL_DELAY) {
    	  Cannonball* ball = getBall();
        if (ball != NULL) {
          ball->fire(player.getX(), player.getY());
      	  ballCycle = 0;
        }
      }

      //this allows for the potentiometer to be more narrow, only using the middle two quarters of its range to control the player
      player.setX((47 - potentiometer_value / 16) >= -1 ? ((47 - potentiometer_value / 16) < 31 ? (47 - potentiometer_value / 16) : 30 ): -1);
      
      // moves all enemies down the screen             
      if (time % INVADER_DELAY == 0) {
        for(int i = NUM_ENEMIES; i >= 0 ; i--){
            enemies[i].erase(matrix);
            if (firstLayerCleared()) {
             enemies[i].move();
            } else if (i > 7) { 
             enemies[i].move();
            }
        }
        drawAllEnemies(); 
      }
      
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
    
       player.draw(matrix);
    }

  private:
    int level;
    int ballCycle;
    unsigned long time;
    Player player;
    Cannonball balls[NUM_BALLS];
    Invader enemies[NUM_ENEMIES];

    // define the wiring of the LED screen
    const uint8_t CLK  = 11;
    const uint8_t LAT = A3;
    const uint8_t OE = 10;
    const uint8_t A = A0;
    const uint8_t B = A1;
    const uint8_t C = A2;
    RGBmatrixPanel matrix{A, B, C, CLK, LAT, OE, false};

    // check if Player defeated all Invaders in current level
    bool level_cleared() {
      int count = 0;
      for (int i = 0; i < NUM_ENEMIES; i++) {
        count += enemies[i].getStrength();
      }
      return count == 0;
    }

    bool firstLayerCleared(){
      for (int i = NUM_ENEMIES/2; i < NUM_ENEMIES; i++) {
        if (enemies[i].getStrength() > 0) return false;
      }
      return true;
    }

    void drawAllEnemies(){
        for(int i = NUM_ENEMIES-1; i >= 0 ; i--){
          enemies[i].draw(matrix);
        }    
    }

    // set up a level
    void reset_level() {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      level++;
      ballCycle = BALL_DELAY;
      int minStrength = level/5 + 1;
      int maxStrength = 3*sqrt(level);
      maxStrength = (minStrength < maxStrength) ? maxStrength : level/3 - 30;
      for (int i = 0; i < 2; i++){
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
      drawAllEnemies();
    }

    //returns the proper ball to use when fire is called
    Cannonball* getBall() {
	    for (int i = 0; i < NUM_BALLS; i++){
		    if (!balls[i].hasBeenFired()){
		  	  return &balls[i];
		    }
	    }
	    return NULL;
    }

    void updateBalls(){
	    for (int i = 0; i < NUM_BALLS; i++){
		    balls[i].erase(matrix);
		    balls[i].move();
		    balls[i].draw(matrix);
	    }
    }

    // displays Level
    void print_level(int level) {
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
    
    // displays number of lives
    void print_lives(int lives) {
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
    
    // displays "game over"
    void game_over() {
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
};


// a global variable that represents the game Space Invaders
Game game;

// see https://www.arduino.cc/reference/en/language/structure/sketch/setup/
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  game.setupGame();
}

// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  game.update(potentiometer_value, button_pressed);
  delay(30);
}
