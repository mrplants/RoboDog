#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// default constructor
Mario::Mario()
{
  //Initialize movement variables
  marioRect.x = 0;
  marioRect.y = SCREEN_HEIGHT - MARIO_HEIGHT;

  //Initialize animation variables
  status = MARIO_STAND;
  frame = 0;

  //Create the Mario surface
  marioSurface = load_image( "Mario.bmp" );
}

// figure out how to pass in screen
void Mario::show(SDL_Surface *screen)
{
  //Show Mario
  if( status == MARIO_STAND )
    {
      SDL_BlitSurface( marioSurface, &standClip[ frame ], screen, &marioRect); 
    }

  if( status == MARIO_STEP ) 
    {
      SDL_BlitSurface( marioSurface, &stepClips[ frame ], screen, &marioRect);
      frame++;
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
void set_clips()
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
