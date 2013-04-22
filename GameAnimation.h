#include "constants.h"
#include "SDL_Program.h"
#inlcude "Mario.h"

class GameAnimation : public SDL_Program {
 public:
  
  GameAnimation();
  //player commands
  void step();
  void jump();
  void turn();
  void kick();
  
 private:
  SDL_Surface *background;
  Mario mario;

};
