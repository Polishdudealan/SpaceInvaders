#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;

// global constant for the number of Invaders in the game
const int NUM_ENEMIES = 16;

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

//used to determine invader speed
const int INVADER_DELAY = 80;

// the following functions are for printing messages
void print_level(int level);
void print_lives(int lives);
void game_over();

class Color {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};

const Color BLACK(0, 0, 0);
const Color RED(4, 0, 0);
const Color ORANGE(6, 1, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 4, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(1, 0, 2);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 4, 4);

static const int LEVEL_DATA[4][2][8] = 
	{{{1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}},
	{{1, 2, 1, 2, 1, 2, 1, 2}, {2, 1, 2, 1, 2, 1, 2, 1}},
	{{1, 2, 3, 4, 5, 1, 2, 3}, {4, 5, 1, 2, 3, 4, 5, 1}},
	{{5, 4, 5, 4, 5, 4, 5, 4}, {2, 3, 2, 3, 2, 3, 2, 3}}};

class Invader {
  public:
    // Constructors
    Invader() {
      x = 0;
      y = 0;
      strength = 0;
    }
    // sets values for private date members x and y
    Invader(int x_arg, int y_arg): x(x_arg), y(y_arg) {}
    // sets values for private data members
    Invader(int x_arg, int y_arg, int strength_arg): x(x_arg), y(y_arg), strength(strength_arg){}
    // sets values for private data members
    void initialize(int x_arg, int y_arg, int strength_arg) {
    	x = x_arg;
	    y = y_arg;
	    strength = strength_arg;
    }
    
    // getters
    int get_x() const {
    	return x;
    }
    int get_y() const {
    	return y;
    }
    int get_strength() const {
    	return strength;
    }

    // Moves the Invader down the screen by one row
    // Modifies: y
    void move() {
    	y++;
    }
    
    // draws the Invader if its strength is greater than 0
    // calls: draw_with_rgb
    void draw() {
      if (strength != 0) {
        draw_with_rgb(num_to_color(strength % 7), num_to_color((strength / 7 + 5) % 7));      
      }
    }
    
    // draws black where the Invader used to be
    // calls: draw_with_rgb
    void erase() {
    	draw_with_rgb(BLACK, BLACK);
    }

    Color num_to_color(int x){
      switch (x) {
        case 0:
          return WHITE;
          break;
        case 1:
          return RED;
          break;
        case 2:
          return ORANGE;
          break;
        case 3:
          return YELLOW;
          break;
        case 4:
          return GREEN;
          break;
        case 5:
          return BLUE;
          break;
        default:
          return PURPLE;
      }
    }
    
    // Invader is hit by a Cannonball.
    // Modifies: strength
    // calls: draw, erase
    void hit() {
    	strength--;
	    if (!strength == 0){
		    draw();
	    } else{
		    erase();
	    }
    }

  private:
    int x;
    int y;
    int strength;
    
    // draws the Invader
    void draw_with_rgb(Color body_color, Color eye_color) {
 	uint16_t b_col = body_color.to_333();
	uint16_t e_col = eye_color.to_333();
	uint16_t blk = BLACK.to_333();
	matrix.fillRect(x, y, 4, 4, b_col);
	matrix.drawPixel(x, y, blk);
	matrix.drawPixel(x+3, y, blk);
	matrix.drawPixel(x+1, y+3, blk);
	matrix.drawPixel(x+2, y+3, blk);
	matrix.drawPixel(x+1,y+1,e_col);
	matrix.drawPixel(x+2,y+1,e_col);
    }
};

class Cannonball {
  public:
    Cannonball() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // resets private data members to initial values
    void reset() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // getters
    
    int get_x() const {
    	return x;
    }
    int get_y() const {
    	return y;
    }
    bool has_been_fired() const {
      return fired;
    }
    
    // sets private data members
    void fire(int x_arg, int y_arg) {
      x = x_arg;
      y = y_arg;
      fired = true;
    }
    
    // moves the Cannonball and detects if it goes off the screen
    // Modifies: y, fired
    void move() {
      if (y >= 0) {
        y--;
      }
       else {
        fired = false;
      }
    }
    
    // resets private data members to initial values
    void hit() {
      x = 0;
      y = 0;
      fired = false;
    }
    
    // draws the Cannonball, if it is fired
    void draw() {
      if(fired){
        matrix.drawPixel(x, y, RED.to_333());
        matrix.drawPixel(x, y - 1, RED.to_333()); 
      }
      else {
        erase();
      }
    }
    
    // draws black where the Cannonball used to be
    void erase() {
      matrix.drawPixel(x, y, BLACK.to_333());
      matrix.drawPixel(x, y - 1, BLACK.to_333());
    }

  private:
    int x;
    int y;
    bool fired;
};

class Player {
  public:
    Player() {
      x = 15;
      y = 15;
      lives = 3;
    }
    
    // getters
    int get_x() const {
      return x;
    }
    int get_y() const {
      return y;
    }
    int get_lives() const {
      return lives;
    }
    
    // setter
    void set_x(int x_arg) {
      x = x_arg;
    }

    //reset lives upon restarting gamme
    void reset_lives() {
      lives = 3;
    }
    
    // Modifies: lives
    void die() {
      lives--; 
    }
    
    // draws the Player
    // calls: draw_with_rgb
    void draw() {
      draw_with_rgb(GREEN);
    }
    
    // draws black where the Player used to be
    // calls: draw_with_rgb
    void erase() {
      draw_with_rgb(BLACK);
    }

  private:
    int x;
    int y;
    int lives;

    // sets private data members x and y to initial values
    void initialize(int x_arg, int y_arg) {
      x = x_arg;
      y = y_arg;
    }
    
    // draws the player
    void draw_with_rgb(Color color) {
      matrix.drawPixel(x, y, color.to_333());
      matrix.drawPixel(x - 1, y, color.to_333());
      matrix.drawPixel(x + 1, y, color.to_333());
      matrix.drawPixel(x, y - 1, color.to_333());
    }
};

class Game {
  public:
    Game() {
      level = 13;
      time = 0;
    }
    
    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    void setupGame() {

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
        player.erase();
        ball.erase();
        
        if (button_pressed && ball.has_been_fired() == false) {
          ball.fire(player.get_x(), player.get_y());  
        }
        ball.move();

        player.set_x((47 - potentiometer_value / 16) >= 0 ? ((47 - potentiometer_value / 16) < 32 ? (47 - potentiometer_value / 16) : 31 ): 0);
        // moves all enemies down the screen             
        if (time % INVADER_DELAY == 0) {
          for(int i = NUM_ENEMIES; i >= 0 ; i--){
            enemies[i].erase();
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
          if (i % 8 * 4 <= ball.get_x() && i % 8 * 4 + 3 >= ball.get_x() && ball.get_y() - 1 == enemies[i].get_y() && enemies[i].get_strength() != 0){

            enemies[i].hit(); 
            ball.hit();
            break;          
          }

        }
        // checks for enemies getting past player
        for (int i = 0; i < NUM_ENEMIES; i++){
                  
          if (enemies[i].get_y() == 13 && enemies[i].get_strength() > 0) {
            player.die();
            level--;
            reset_level();
            }
        }
        if (player.get_lives() < 1) {

          matrix.fillScreen(matrix.Color333(0, 0, 0));
          player.reset_lives();
          level = 0;
          game_over();
          delay(4000);
          setupGame();  
        }
        // checks if level is cleared
       if(level_cleared()){
         reset_level();     
       }

       player.draw();
       ball.draw();
    }

  private:
    int level;
    unsigned long time;
    Player player;
    Cannonball ball;
    Invader enemies[NUM_ENEMIES];
    
    // check if Player defeated all Invaders in current level
    bool level_cleared() {
      int count = 0;
      for (int i = 0; i < NUM_ENEMIES; i++) {
        count += enemies[i].get_strength();
      }
      return count == 0;
    }

    bool firstLayerCleared(){
      for (int i = NUM_ENEMIES/2; i < NUM_ENEMIES; i++) {
        if (enemies[i].get_strength() > 0) return false;
      }
      return true;
    }

    void drawAllEnemies(){
        for(int i = NUM_ENEMIES-1; i >= 0 ; i--){
          enemies[i].draw();
        }    
    }

    // set up a level
    void reset_level() {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      level++;
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
      print_lives(player.get_lives());
      delay(1000);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      drawAllEnemies();
    }
};


// a global variable that represents the game Space Invaders
Game game;

// see https://www.arduino.cc/reference/en/language/structure/sketch/setup/
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(4000);
  game.setupGame();}

// see https://www.arduino.cc/reference/en/language/structure/sketch/loop/
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);

  game.update(potentiometer_value, button_pressed);

  delay(30);
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
