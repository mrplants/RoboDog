/*
  GameMaster.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Contains the entire program's functionality
  Initializes SDL, setting up the game screen and background
  Runs a loop that loops for the entirety of the game, checking for events and calling the appropriate
    methods of its composed classes based on what events are detected
  
  Composed classes:
    Interpreter - parses a vector of vectors containing information about the user's program
    TokenQueue - instantiates tokens and keeps track of all instantiated tokens in a deque
    GameWorld - animates the game portion of the window based on calls from the interpreter
 
 */

#ifndef GAME_MASTER
#define GAME_MASTER

#include <iostream>
#include <vector>
#include <string>

//SDL Libraries
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

//library for C POSIX multithreading NOT IMPLEMENTED
//#include "pthread.h"

//Base class for GameMaster.h
#include "SDL_Program.h"
//contains program-wide constants like screen size
#include "constants.h"

#include "TokenQueue.h"
#include "Interpreter.h"
#include "GameWorld.h"

class GameWorld;

class GameMaster : public SDL_Program {
    
public:
	GameMaster();
	~GameMaster();
    
	void play(); //this starts the game
    
	//sets up the screen, background, and all SDL subsystems, the last parameter is for the title of the window
	bool initializeSDL(int = SCREEN_WIDTH, int = SCREEN_HEIGHT, int = SCREEN_BPP, std::string = "Robodog");

	void updateScreen(); //blits the background images and calls the update screen method of composed classes
    
private:
	//NOT IMPLEMENTED
	//show welcome screen
	//show high scores
    Mix_Music *mus;
	SDL_Surface *screen; //screen or canvas all images are blit onto
	SDL_Surface *background; //whatever fills the whole screen's background
	SDL_Rect tokenPane; //area that user will drop tokens in to "write" their code
	
	bool checkMousePositionOnPress(int, int);
	bool mouseInTokenPane(int, int);
    
	virtual void cleanUp(); //implemented in this class
	void compileUserCode(); //called when user presses play, gets tokenQueue and gives it to the interpreter
    
	Interpreter interpreter; //parses a vector of vectors containing information about the user's program
	TokenQueue queueOfTokens; //instantiates tokens and keeps track of all instantiated tokens in a deque
	GameWorld gameWorld; //animates the game portion of the window based on calls from the interpreter
    
};

#endif // defined GAME_MASTER
