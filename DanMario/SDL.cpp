#include <string>

//Screen attributes
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
const int MARIO_KICK = 2;
const int MARIO_ATTACK = 3;

//The surfaces
SDL_Surface *mario = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The areas of the sprite sheet
SDL_Rect clips[ 2 ];

//loads the image
SDL_Surface *load_image( std::string filename )
{
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;

  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load( filename.c_str() );

  //If the image loaded
  if( loadedImage != NULL )
    {
      //Create an optimized surface
      optimizedImage = SDL_DisplayFormat( loadedImage );

      //Free the old surface
      SDL_FreeSurface( loadedImage );

      //If the surface was optimized
      if( optimizedImage != NULL )
        {
	  //Color key surface
	  SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

  //Return the optimized surface
  return optimizedImage;
}

// applies the surface
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
  //Holds offsets
  SDL_Rect offset;

  //Get offsets
  offset.x = x;
  offset.y = y;

  //Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}

// define clip locations
void set_clips()
{
  //Clip the sprites
  clips[ 0 ].x = 0;
  clips[ 0 ].y = 0;
  clips[ 0 ].w = MARIO_WIDTH;
  clips[ 0 ].h = MARIO_HEIGHT;

  clips[ 1 ].x = MARIO_WIDTH;
  clips[ 1 ].y = 0;
  clips[ 1 ].w = MARIO_WIDTH;
  clips[ 1 ].h = MARIO_HEIGHT;

}

//initialize function for SDL
bool init()
{
  //Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }

  //Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

  //If there was an error in setting up the screen
  if( screen == NULL )
    {
      return false;
    }

  //Set the window caption
  SDL_WM_SetCaption( "Jumping Mario on Scrolling Background", NULL );

  //If everything initialized fine
  return true;
}

//load the files
bool load_files()
{
  //Load Mario image
  mario = load_image( "Mario.bmp" );

  //Load the background
  background = load_image( "NYC.jpg" );

  //If there was a problem in loading Mario
  if( mario == NULL )
    {
      return false;
    }

  //If there was a problem in loading the background
  if( background == NULL )
    {
      return false;
    }

  //If everything loaded fine
  return true;
}

//perform a clean up for SDL
void clean_up()
{
  //Free the surfaces
  SDL_FreeSurface( mario );
  SDL_FreeSurface( background );

  //Quit SDL
  SDL_Quit();
}
