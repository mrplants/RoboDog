#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H

#include "constants.h"
#include "SDL_Program.h"
#include "Mario.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>

class GameMaster;

class GameAnimation : public SDL_Program {
 public:

  GameAnimation();
  ~GameAnimation();

  GameAnimation(GameMaster*);

  // define clip locations for the background image                          
  void clip_background();
  
  //player commands
  void step();
  void jump();
  void turn();
  void kick();

  // clean up function
  virtual void cleanUp();
  
  // update the screen
  void updateScreen(SDL_Surface*);

 private:

  // background surface
  SDL_Surface *background;
  
  // rectangle where background is blitted
  SDL_Rect backRect;

  // current scene of background being shown
  int scene;
  int maxNumberOfScenes;

  // areas of background sheet
  std::vector< SDL_Rect > backClips; 

  // instance of Mario
  Mario mario;

  // pointer to game master
  GameMaster *gameMasterPointer;

};

#endif // defined GAMEANIMATION_H
