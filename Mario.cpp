/*
  Mario.cpp
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  The character that animates through the level
  */

#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Mario.h"

// default constructor
Mario::Mario() {}

Mario::~Mario() {}

Mario::Mario(std::string imageURL) : SDL_Program()
{
  //Initialize animation variables
  status = MARIO_STAND;
  frame = 0;
  
  //Create the Mario surface
  marioSurface = loadImage("tokenImages/RobodogPositions.bmp");

  //Initialize movement variables
    marioRect = createRect(marioSurface, SCREEN_WIDTH - TOKEN_LIB_W, SCREEN_HEIGHT - TOKEN_LIB_H - RUN_BUTTON_H - MARIO_HEIGHT);
}

//show Mario
void Mario::show(SDL_Surface *screen)
{

  if( status == MARIO_STAND )
    {
      SDL_BlitSurface( marioSurface, &standClip[ frame ], screen, &marioRect); 
    }

  if( status == MARIO_STEP ) 
    {
      SDL_Delay(100);
      //increment the frame
      frame++;
      //loop the animation
      if( frame >= 2 )
	{
          frame = 0;
        }
      SDL_BlitSurface( marioSurface, &stepClips[ frame ], screen, &marioRect);
    }

  if( status == MARIO_JUMP ) 
    {
      SDL_BlitSurface( marioSurface, &jumpClip[ frame ], screen, &marioRect);
    }

  if( status == MARIO_TURN )
    {
      SDL_BlitSurface( marioSurface, &turnClip[ frame ], screen, &marioRect);
    }

  if( status == MARIO_KICK )
    {
      SDL_BlitSurface( marioSurface, &kickClip[ frame ], screen, &marioRect);
    }
  
}

// define clip locations
void Mario::set_clips()
{
  //Clip the sprites
  standClip[ 0 ].x = 0;
  standClip[ 0 ].y = 0;
  standClip[ 0 ].w = MARIO_WIDTH;
  standClip[ 0 ].h = MARIO_HEIGHT;
  
  stepClips[ 0 ].x = 0;
  stepClips[ 0 ].y = MARIO_HEIGHT;
  stepClips[ 0 ].w = MARIO_WIDTH;
  stepClips[ 0 ].h = MARIO_HEIGHT;

  stepClips[ 1 ].x = MARIO_WIDTH;
  stepClips[ 1 ].y = MARIO_HEIGHT;
  stepClips[ 1 ].w = MARIO_WIDTH;
  stepClips[ 1 ].h = MARIO_HEIGHT;

  jumpClip[ 0 ].x = 0;
  jumpClip[ 0 ].y = MARIO_HEIGHT * 2;
  jumpClip[ 0 ].w = MARIO_WIDTH;
  jumpClip[ 0 ].h = MARIO_HEIGHT;

  turnClip[ 0 ].x = 0;
  turnClip[ 0 ].y = MARIO_HEIGHT * 3;
  turnClip[ 0 ].w = MARIO_WIDTH;
  turnClip[ 0 ].h = MARIO_HEIGHT;

  kickClip[ 0 ].x = 0;
  kickClip[ 0 ].y = MARIO_HEIGHT * 4;
  kickClip[ 0 ].w = MARIO_WIDTH;
  kickClip[ 0 ].h = MARIO_HEIGHT;

}


// clean up function for Mario
void Mario::cleanUp()
{
  SDL_FreeSurface( marioSurface );

}
