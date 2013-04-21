#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define SCREEN_WIDTH 640;
#define SCREEN_HEIGHT 480;
#define SCREEN_BPP 32;

//The frame rate
 #define FRAMES_PER_SECOND 20;

//The dimensions of Mario
 #define MARIO_WIDTH 184;
 #define MARIO_HEIGHT 200;

//The action status of Mario
 #define MARIO_STAND 0;
 #define MARIO_JUMP 1;

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
