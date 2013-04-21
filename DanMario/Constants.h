#ifndef CONSTANTS_H
#define CONSTANTS_H

 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 const int SCREEN_BPP = 32;

//The frame rate
 const int FRAMES_PER_SECOND = 20;

//The dimensions of Mario
 const int MARIO_WIDTH = 184;
 const int MARIO_HEIGHT = 200;

//The action status of Mario
 const int MARIO_STAND = 0;
 const int MARIO_JUMP = 1;

//The surfaces
 SDL_Surface *mario = NULL;
 SDL_Surface *background = NULL;
 SDL_Surface *screen = NULL;

//The event structure
 SDL_Event event;

//The areas of the sprite sheet
 SDL_Rect clips[ 2 ];

// tells us if we are scrolling (1 if yes, 0 if no)                                                               
 int scrolling;

#endif