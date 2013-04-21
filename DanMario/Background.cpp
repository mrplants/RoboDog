/* DANIEL TAMARU - CSE 20212 - LAB 10 - SCROLLING BACKGROUND
   
.cpp file containing the Mario and Timer classes and their implementations, necessary functions to setup SDL, and a main function

Based on Lazy Foo' Productions tutorials...
http://lazyfoo.net/SDL_tutorials/lesson16/index.php 
http://lazyfoo.net/SDL_tutorials/lesson20/index.php
http://lazyfoo.net/SDL_tutorials/lesson22/index.php

*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
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

//It's a me, Mario!
class Mario
{
private:
  //The offset
  int offSet;

  // x and y coordinates 
  int x;
  int y;

  //Its current frame
  int frame;

  //Its animation status
  int status;

public:
  //Initializes the variables
  Mario();

  //Handles input
  void handle_events();

  //Shows Mario
  void show();
};

//The background
class Background
{
private:

  //The offsets of the background                                                                                  
  int bgX; 
  int bgY;

public:
  //Initializes the variables
  Background();
  
  //Handles input
  void handle_events();
  
  //Shows the background
  void show();

};

//The timer
class Timer
{
private:
  //The clock time when the timer started
  int startTicks;

  //The ticks stored when the timer was paused
  int pausedTicks;

  //The timer status
  bool paused;
  bool started;

public:
  //Initializes variables
  Timer();

  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  //Gets the timer's time
  int get_ticks();

  //Checks the status of the timer
  bool is_started();
  bool is_paused();
};

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

// default constructor
Mario::Mario()
{
  //Initialize movement variables
  offSet = 0;
  x = 0;
  y = SCREEN_HEIGHT - MARIO_HEIGHT;

  //Initialize animation variables
  status = MARIO_STAND;
}

// handle key presses
void Mario::handle_events()
{
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
      //Set the status and move
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: status = MARIO_JUMP; y -= 50; scrolling = 1; break;
        }
    }
    
  //If a key was released
  else if( event.type == SDL_KEYUP )
    {
      //Set the status and move
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: status = MARIO_STAND; y += 50; scrolling = 0; break;
        }
    }
   
}

void Mario::show()
{
  //Show Mario
  if( status == MARIO_JUMP )
    {
      apply_surface( x, y, mario, screen, &clips[ 1 ] );
    }
   if( status == MARIO_STAND )
    {
      apply_surface( x, y, mario, screen, &clips[ 0 ] );
    }
}

//default constructor for Background
Background::Background()
{
  //Initialize the variables
  scrolling = 0;
  bgX = 0;
  bgY = 0;
}

// handle key presses                                                                                            
void Background::handle_events()
{
  //If a key was pressed                                                                                         
  if( event.type == SDL_KEYDOWN )
    {
      //Set the velocity                                                                                          
      switch( event.key.keysym.sym )
        {
        case SDLK_RIGHT: scrolling = 1; break;
        }
    }

  //If a key was released                                                                                         
  else if( event.type == SDL_KEYUP )
    {
      //Set the velocity                                                                                          
      switch( event.key.keysym.sym )
        {
        case SDLK_RIGHT: scrolling = 0; break;
        }
    }

}

void Background::show()
{
  //Show the Background                                                                                          
  if( scrolling == 1 )
    {
      bgX -= 50;
    }
  if( scrolling == 0 )
    {
      bgX = bgX;
    }
  //If the background has gone too far                                                                          
  if( bgX <= -background->w )
    {
      //Reset the offset                                                                                        
      bgX = 0;
    }

  //Show the background                                                                                         
  apply_surface( bgX, bgY, background, screen );
  apply_surface( bgX + background->w, bgY, background, screen );
}

//default constructor for Timer
Timer::Timer()
{
  //Initialize the variables
  startTicks = 0;
  pausedTicks = 0;
  paused = false;
  started = false;
}

void Timer::start()
{
  //Start the timer
  started = true;

  //Unpause the timer
  paused = false;

  //Get the current clock time
  startTicks = SDL_GetTicks();
}

void Timer::stop()
{
  //Stop the timer
  started = false;

  //Unpause the timer
  paused = false;
}

void Timer::pause()
{
  //If the timer is running and isn't already paused
  if( ( started == true ) && ( paused == false ) )
    {
      //Pause the timer
      paused = true;

      //Calculate the paused ticks
      pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
  //If the timer is paused
  if( paused == true )
    {
      //Unpause the timer
      paused = false;

      //Reset the starting ticks
      startTicks = SDL_GetTicks() - pausedTicks;

      //Reset the paused ticks
      pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
  //If the timer is running
  if( started == true )
    {
      //If the timer is paused
      if( paused == true )
        {
	  //Return the number of ticks when the timer was paused
	  return pausedTicks;
        }
      else
        {
	  //Return the current time minus the start time
	  return SDL_GetTicks() - startTicks;
        }
    }

  //If the timer isn't running
  return 0;
}

bool Timer::is_started()
{
  return started;
}

bool Timer::is_paused()
{
  return paused;
}

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
