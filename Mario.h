/*
  Mario.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  The character that animates through the level
  */

#ifndef MARIO_H
#define MARIO_H

#include "constants.h"
#include "SDL_Program.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Mario : public SDL_Program
{
 public:

  // initializes the variables                                                 
  Mario();
  ~Mario();

  Mario(std::string);

  // shows Mario                                                              
  void show(SDL_Surface*);

  // define clip locations
  void set_clips(); 

  // clean up function for Mario
  virtual void cleanUp();

  // Mario surface
  SDL_Surface *marioSurface;

  // areas of the sprite sheet
  SDL_Rect standClip[ 1 ];
  SDL_Rect stepClips[ 2 ];
  SDL_Rect jumpClip[ 1 ];
  SDL_Rect turnClip[ 1 ];
  SDL_Rect kickClip[ 1 ];

  // animation status                                                      
  int status;

  SDL_Rect marioRect;

 private:
  
  // current frame of Mario animation being shown
  int frame;
  
};

#endif //defined MARIO_H 
