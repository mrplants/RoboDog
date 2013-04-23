#include "constants.h"
#include "SDL_Program.h"
#include "Mario.h"
// #include "GameMaster.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class GameMaster;

class GameAnimation : public SDL_Program {
 public:

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
  Mario mario;
  void *gameMaster;

};
