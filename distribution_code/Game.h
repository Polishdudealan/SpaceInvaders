
#include "Signal.h"
#include "Player.h"
//#include "Powerups.h"
#include "Cannonball.h"
#include "Invader.h"

#ifndef FONT
  #define FONT
  #include "Font.h"
#endif


#ifndef CONSTANTS
  #define CONSTANTS
  #include "Constants.h"
#endif

using namespace Constants;

class Game {
  public:
    Game();
      
    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    void setupGame();
      
    // advances the game simulation one step and renders the graphics
    // see spec for details of game
    // Modifies: global variable matrix
    void update(int potentiometer_value, bool button_pressed);

  private:
    // game constant for the number of Invaders in the game
    static const int NUM_ENEMIES = 16;
  
    // game constant for the number of cannonballs in the game
    static const int NUM_BALLS = 8;

    //game constant for the number of players in the game
    static const int NUM_PLAYERS = 1;

    //game constant for number of powerups
    static const int NUM_POWERUPS = 1;

    //total sprites
    static const int NUM_SPRITES = NUM_ENEMIES + NUM_BALLS + NUM_PLAYERS; //+ NUM_POWERUPS;
    
    // define the wiring of the LED screen
//    const uint8_t CLK  = 11;
//    const uint8_t LAT = A3;
//    const uint8_t OE = 10;
//    const uint8_t A = A0;
//    const uint8_t B = A1;
//    const uint8_t C = A2;
//    Signal matrix{A, B, C, CLK, LAT, OE, false};
    Signal matrix;

    
    int level;
    int ballCycle;
    unsigned long time;
    int numUpdates;
    int layers;
    int currentLayer;

    //****** Sprites ********
    Player player;
    Cannonball balls[NUM_BALLS];
    Invader enemies[NUM_ENEMIES];
    Sprite* updatableSprites[NUM_SPRITES];
    //Powerups powerup;


    //***** Helper Functions
    // check if Player defeated all Invaders in current level
    bool level_cleared();

    //checks if the first layer of invaders is clear
    bool layerCleared(int layer);

    // set up a level
    void reset_level();

    //returns the proper ball to use when fire is called
    Cannonball* getBall();    

    
    //********** update functions **********
    //moves all sprites in game
    void moveUpdate();

    //checks inputs from the user
    void inputUpdate(int pot, bool btn);

    //checks to see if there are any collisions which are important to gameplay
    void checkCollisions();

    //redraws all sprites that have been updated
    void redrawSprites();

  
    //********** printer functions **********
    // displays Level
    void print_level(int level);
    
    // displays number of lives
    void print_lives(int lives);
    
    // displays "game over"
    void game_over();

    // displays scoreboard
    void score_board(int scoreNumber);
};
