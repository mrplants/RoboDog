
#include "GameAnimationMario.h"
#include "Mario.h"
#include "Timer.h"
#include "Background.h"
#include "Constants.h"

//prototypes
SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
void set_clips();
bool init();
bool load_files();
void clean_up();

//main function
int main( int argc, char* args[] )
{
  //Quit flag
  bool quit = false;

  //The frame rate regulator
  Timer fps;

  //Initialize
  if( init() == false )
    {
      return 1;
    }

  //Load the files
  if( load_files() == false )
    {
      return 1;
    }

  //Clip the sprite sheet                                                    
  set_clips();

  //instantiate Mario                                                         
  Mario action;

  //instantiate Background
  Background back;

  //While the user hasn't quit
  while( quit == false )
    {
      //Start the frame timer
      fps.start();

      //While there's events to handle
      while( SDL_PollEvent( &event ) )
        {

    //Handle events for Mario and the Background
    action.handle_events();
    back.handle_events();
   
    
    //If the user has Xed out the window
    if( event.type == SDL_QUIT )
            {
        //Quit the program
        quit = true;
            }
        }
      
      back.show();
      action.show();

      //Update the screen
      if( SDL_Flip( screen ) == -1 ) {
  return 1;
      }
      
      if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND) 
  {
    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
  }
    }    
  
  //Clean up
  clean_up();
  
  return 0;
}


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
  mario = load_image( "characterTest.png" );

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


