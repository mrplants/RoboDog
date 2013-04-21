#ifndef CONSTANTS_H
#define CONSTANTS_H

 extern const int SCREEN_WIDTH = 640;
 extern const int SCREEN_HEIGHT = 480;
extern  const int SCREEN_BPP = 32;

//The frame rate
 extern const int FRAMES_PER_SECOND = 20;

//The dimensions of Mario
 extern const int MARIO_WIDTH = 184;
 extern const int MARIO_HEIGHT = 200;

//The action status of Mario
 extern const int MARIO_STAND = 0;
 const int MARIO_JUMP = 1;

//The surfaces
 extern SDL_Surface *mario = NULL;
 extern SDL_Surface *background = NULL;
 extern SDL_Surface *screen = NULL;

//The event structure
 extern SDL_Event event;

//The areas of the sprite sheet
 extern SDL_Rect clips[ 2 ];

// tells us if we are scrolling (1 if yes, 0 if no)                                                               
 extern int scrolling;


#endif