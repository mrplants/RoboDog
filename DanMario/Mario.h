#ifndef MARIO_H
#define MARIO_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>


#include <iostream>

class Mario
{
private:
  //The offset
  int offSet;

  // x and y coordinates 
  int x;
  int y;

  //Its current frame
  int frame;

  //Its animation status
  int status;

public:
  //Initializes the variables
  Mario();

  //Handles input
  void handle_events();

  //Shows Mario
  void show();
};

#endif