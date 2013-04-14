/*
 GameMaster.cpp
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 Master Game Controller - links together all the game classes via composition

 */

#include "GameMaster.h"

GameMaster::GameMaster(){}
GameMaster::~GameMaster(){}

//this starts the master game
void GameMaster::play() {}

//sets up the screen and the background
bool GameMaster::SDL_init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP, string caption) {
    
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        std::cout << "ERR: SDL_INIT_EVERYTHING was not successful" << std::endl;
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL ) {
        std::cout << "ERR: Screen could not be initialized" << std::endl;
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( caption, NULL );
    
    //If everything initialized fine
    return true;
}

//SDL_Surface * screen; //screen or canvas all images are blit onto
//SDL_Surface * background; //whatever fills the whole screen's background

//##### Snap Region Data Members/Methods #######//
//SDL_Rect snapRegion; //rectangle that defines the area an image will snap to
//SDL_Surface *snapImage; //visual representation of the snap region (probably not needed for final project)

//adds a rect to the screen that will  be used to snap tokens into place
void GameMaster::setUpSnapRegion(int, int, SDL_Surface *) {}

//adds a visual representation of the snap region to the screen
void GameMaster::applySnapRegion(SDL_Surface *) {}

//creates the blank surface applied to the screen by applySnapRegion
SDL_Surface* GameMaster::createBlankSurface(Uint32 flags, int width, int height, const SDL_Surface* screen) {}
