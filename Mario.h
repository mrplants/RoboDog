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

  //define clip locations
  void set_clips(); 

  //clean up function for Mario
  void cleanUp();

  //Mario surface
  SDL_Surface *marioSurface;

  //Areas of the sprite sheet
  SDL_Rect standClip[ 1 ];
  SDL_Rect stepClips[ 2 ];
  SDL_Rect jumpClip[ 1 ];
  SDL_Rect turnClip[ 1 ];
  SDL_Rect kickClip[ 1 ];

};
