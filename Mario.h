#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Mario
{
 private:
  SDL_Rect marioRect;

  //Its current frame                                                        
  int frame;

  //Its animation status                                                      
  int status;

 public:
  //Initializes the variables                                                 
  Mario();

  //Shows Mario                                                              
  void show();

  //Mario surface                                                                                                                                                 
  SDL_Surface *marioSurface;
};
