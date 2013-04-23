#include "constants.h"
#include "SDL_Program.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class GameMaster;
class Mario;

class GameAnimation : public SDL_Program {
 public:

  GameAnimation();

  GameAnimation(GameMaster*);
  //player commands
  void step();
  void jump();
  void turn();
  void kick();

  void cleanUp();
  void updateScreen(SDL_Surface*);
  
 private:
  SDL_Surface *background;
  SDL_Rect backRect;
  Mario mario;
  GameMaster *gameMasterPointer;

};
