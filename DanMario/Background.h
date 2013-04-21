
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>


//The background
class Background
{
private:

  //The offsets of the background                                                                                  
  int bgX; 
  int bgY;

public:
  //Initializes the variables
  Background();
  
  //Handles input
  void handle_events();
  
  //Shows the background
  void show();

};
