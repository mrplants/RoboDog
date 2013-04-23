#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Mario
{
 public:
  //Initializes the variables                                                 
  Mario();

  //Shows Mario                                                              
  void show(SDL_Surface*);

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

  //Its animation status                                                      
  int status;

  SDL_Rect marioRect;

   private:

  //Its current frame                                                        
  int frame;

};
