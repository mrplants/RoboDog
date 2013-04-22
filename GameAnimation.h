#include "constants.h"
#include "SDL_Program.h"
#include "Mario.h"

class GameAnimation : public SDL_Program {
 public:
  
  GameAnimation();
  //player commands
  void step();
  void jump();
  void turn();
  void kick();

  void cleanUp();
  
 private:
  SDL_Surface *background;
  Mario mario;

};
