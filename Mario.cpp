#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Mario.h"

// default constructor
Mario::Mario() : SDL_Program()
{
  //Initialize animation variables
  status = MARIO_STAND;
  frame = 0;

  //Create the Mario surface
  marioSurface = loadImage( "Mario.bmp" );

  std::cout << "Debug Mairo.cpp Line:16" << std::endl;

  //Initialize movement variables
  marioRect = createRect(marioSurface, 0, SCREEN_HEIGHT - MARIO_HEIGHT);
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

  // define all other locations on sprite sheet

}


// clean up function for Mario
void Mario::cleanUp() {

  SDL_FreeSurface( marioSurface );

}
