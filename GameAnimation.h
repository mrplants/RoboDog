#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H

#include "constants.h"
#include "SDL_Program.h"
#include "Mario.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class GameMaster;

class GameAnimation : public SDL_Program {
 public:

  // GameAnimation();

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


#endif // defined GAMEANIMATION_H
