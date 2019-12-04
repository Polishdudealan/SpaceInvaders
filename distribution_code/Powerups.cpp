#inclue "Powerups.h"

Powerups::Powerups(       )


void Powerup:: draw(RGBmatrixPanel& matrix) {
  draw__pup_with_rgb(RED, matrix)
}


void Powerup :: draw__pup_with_rgb(Color color, RGBmatrixPanel& matrix) {
  matrix.drawPixel(x, y + 1, color.to_333());

}
