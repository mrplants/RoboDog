#ifndef EXTERNS_H
#define EXTERNS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//The surfaces                                                                                                     
extern SDL_Surface *mario;
extern SDL_Surface *background ;
extern SDL_Surface *screen ;

//The event structure                                                                                              
extern SDL_Event event;

//The areas of the sprite sheet                                                                                    
extern SDL_Rect clips[ 2 ];

//Tells us if we are scrolling (1 if yes, 0 if no)                                                                 
extern int scrolling;

#endif
