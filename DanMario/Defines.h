#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Screen attributes
#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
#define SCREEN_BPP = 32;

//The frame rate                                                                                                   
#define FRAMES_PER_SECOND 20;

//The dimensions of Mario                                                                                          
#define MARIO_WIDTH 184;
#define MARIO_HEIGHT 200;

//The action status of Mario                                                                                       
#define MARIO_STAND 0;
#define MARIO_JUMP 1;
