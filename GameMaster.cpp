/*
  GameMaster.cpp
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Implements the entire program's functionality
  Initializes SDL, setting up the game screen and background
  Runs a loop that loops for the entirety of the game, checking for events and calling the appropriate
    methods of its composed classes based on what events are detected
  
  Composed classes:
    Interpreter - parses a vector of vectors containing information about the user's program
    TokenQueue - instantiates tokens and keeps track of all instantiated tokens in a deque
    GameWorld - animates the game portion of the window based on calls from the interpreter
 
 */

#include "GameMaster.h"
#include <unistd.h> //to use usleep

GameMaster::GameMaster() : SDL_Program()
{	
	SDL_Init(SDL_INIT_AUDIO);
	// Setup audio mode
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
	mus = Mix_LoadMUS("robodogSong1.wav");
	Mix_PlayMusic(mus,-1); //Music loop=-1 in order to repeat
	
	initializeSDL(); //sets up SDL subsystems, screen, and background

	GameWorld tempGameWorld(this);

	gameWorld = tempGameWorld;

	//area where tokens will be dropped
	tokenPane.x = 0;
	tokenPane.y = 0;
	tokenPane.h = SCREEN_HEIGHT * TOKEN_PANE_PERCENT_H;
	tokenPane.w = SCREEN_WIDTH * TOKEN_PANE_PERCENT_W;
}

GameMaster::~GameMaster()
{
    //cleanUp(); //cannot use this because of the way the classes have to be initialized
}


//****************************************************************************
//This starts the master game
void GameMaster::play() 
{
	SDL_Event event;
	bool quit = false;
	int dx, dy;
	bool mousePressedOnImage = false;
    
	while (!quit) {

		// Processes any events that are in an event queue
		while (SDL_PollEvent( &event )) {
			if (event.type == SDL_QUIT) { // If user clicks 'x' in top left corner
				quit = true;
				break;
				
			} else if (event.type == SDL_MOUSEBUTTONDOWN) { // If mouse was pressed down
	      
				mousePressedOnImage = checkMousePositionOnPress(event.motion.x, event.motion.y);
				//Because this method gets the change in the mouse's position since the last time it was called,
				//	calling it here removes the big jump
				SDL_GetRelativeMouseState(&dx, &dy);
                
			} else if (event.type == SDL_MOUSEBUTTONUP) { // If the mouse button was released

				if (mouseInTokenPane(event.motion.x, event.motion.y) && mousePressedOnImage) {
					//tells TokenQueue to drop token, TQ will snap it and release it
					queueOfTokens.snapActiveToken();
				} else {
					//tells TQ to delete the last token in the queue (the active token)
					queueOfTokens.releaseActiveToken();
				}
				mousePressedOnImage = false;
                
			} else if (event.type == SDL_MOUSEMOTION && mousePressedOnImage) { // If the user clicks and drags
	      
				SDL_GetRelativeMouseState(&dx, &dy); //gets mouse's change in position since last time this was called
				queueOfTokens.translateActiveToken(dx, dy); //re-applies the token, moving it however much the mouse moved
		
			}
			updateScreen();
		}
	}
	Mix_HaltMusic();
	Mix_FreeMusic(mus);
	return;
}
//****************************************************************************


//Calls the appropriate functions depending on where the mouse clicked
bool GameMaster::checkMousePositionOnPress(int x, int y)
{
	//TokenQueue will check if the mouse is over a token stack or an already-instantiated token and act appropriately
	if ( queueOfTokens.mouseOverToken(x, y) ) {
		//the token that the mouse was over is now the active token and can be dragged
		return true;
		  
	} else if (x > 171 && x < 255 && y > 287 && y < 327) { //user presses the play button
		// This is where it goes down...
		compileUserCode();
	}
	return false;
}


//-----------------------------------------------------------------------------
//      CompileUserCode() Function. 
//-----------------------------------------------------------------------------

//Gets the tokens from the TokenQueue class in the form of a vector of vectors and passes it into the interpreter
//	along with a pointer to GameWorld so that the interpreter can call GameWorld's methods
void GameMaster::compileUserCode() 
{
    interpreter.parse(queueOfTokens.getInterpreterVector(), &gameWorld);

}


//-----------------------------------------------------------------------------
//      Basic SDL Methods (init, clean up, update screen)
//-----------------------------------------------------------------------------

//Sets up the screen surface and physical window
bool GameMaster::initializeSDL(int width, int height, int bpp, std::string caption) 
{
    //Initialize all SDL subsystems
    //UPDATE 4/28/13 - STF put this in the constructor for SDL_Program
    // if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
    //     std::cout << "ERR: SDL_INIT_EVERYTHING was not successful" << std::endl;
    //     return false;
    // }

	//Set up the screen
	screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE );
    
	//If there was an error in setting up the screen
	if( screen == NULL ) {
		std::cout << "ERR: Screen could not be initialized" << std::endl;
		return false;
	}
    
	//Set the window caption
	SDL_WM_SetCaption( caption.c_str(), NULL );
    
	//load background image
	background = loadImage("tokenImages/RoboDogNewUI.bmp"); //method inherited from SDL_Program
	if (background == NULL) std::cout << "ERR: Background could not be loaded\n" << std::endl;
    
	//Initialize SDL_ttf 
	if( TTF_Init() == -1 ) {
		std::cout << "ERR: SDL_ttf could not be initialized" << std::endl;
		return false; 
	}
    
	//If everything initialized fine
	return true;
}

//Checks if mouse is in the lefthand pane that tokens can be dropped in 
bool GameMaster::mouseInTokenPane(int x, int y) 
{
	if (x > tokenPane.x && y > tokenPane.y && x <= (tokenPane.x + tokenPane.w) && y <= (tokenPane.y + tokenPane.h)) {
		return true;
	} else {
		return false;
	}
}

//Blits all the visual elements in this order: GameAnimation's background, Mario, the UI, any tokens that have been dragged out
void GameMaster::updateScreen() 
{
	//Re-applies the game world's background and Mario
	gameWorld.updateScreen(screen);
    
	//Re-applies the UI that overlays the game world background (i.e. the token bin and pane)
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	SDL_BlitSurface(background, NULL, screen, &offset);
    
	//Re-applies the tokens that have been dropped in the pane
	queueOfTokens.updateScreen(screen);
    
	//SDL_Flip must be called for images that have been applied to the screen to show up
	if (SDL_Flip(screen) == -1) std::cout << "ERR: Updating screen failed" << std::endl;
	return;
}

//Frees all of GameMaster's surfaces, and calls the clean up method of its composed classes
void GameMaster::cleanUp()
{
	//Call other class' cleanUp methods
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
    
	//Quit SDL
	SDL_Quit();
    
	//Quit SDL_ttf (deals with font)
	TTF_Quit();
    
	return;
}
