#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Mario.h"

// default constructor
Mario::Mario() : SDL_Program()
{
    std::cout << "Debug Mario.cpp Line: 9 - Mario Constructor start\n" << std::endl;


  //Initialize animation variables
  status = MARIO_STAND;
  frame = 0;

  std::cout << "Debug Mairo.cpp Line:16 - before loadImage(\"Mario.bmp\")\n" << std::endl;

  //Create the Mario surface
  marioSurface = loadImage( "Mario.bmp" );

  std::cout << "Debug Mairo.cpp Line:22 - after loadImage(\"Mario.bmp\")\n" << std::endl;

  //Initialize movement variables
  marioRect = createRect(marioSurface, 0, SCREEN_HEIGHT - MARIO_HEIGHT);

      std::cout << "Debug Mario.cpp Line: 27 - Interpreter Mario end\n" << std::endl;

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
  stepClips[ 0 ].y = 0;
  stepClips[ 0 ].w = MARIO_WIDTH;
  stepClips[ 0 ].h = MARIO_HEIGHT;

  stepClips[ 1 ].x = 0;
  stepClips[ 1 ].y = 0;
  stepClips[ 1 ].w = MARIO_WIDTH;
  stepClips[ 1 ].h = MARIO_HEIGHT;

  jumpClip[ 0 ].x = 0;
  jumpClip[ 0 ].y = 0;
  jumpClip[ 0 ].w = MARIO_WIDTH;
  jumpClip[ 0 ].h = MARIO_HEIGHT;

  turnClip[ 0 ].x = 0;
  turnClip[ 0 ].y = 0;
  turnClip[ 0 ].w = MARIO_WIDTH;
  turnClip[ 0 ].h = MARIO_HEIGHT;

  kickClip[ 0 ].x = 0;
  kickClip[ 0 ].y = 0;
  kickClip[ 0 ].w = MARIO_WIDTH;
  kickClip[ 0 ].h = MARIO_HEIGHT;

}


// clean up function for Mario
void Mario::cleanUp() {

  SDL_FreeSurface( marioSurface );

}
