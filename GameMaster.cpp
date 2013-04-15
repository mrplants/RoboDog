/*
 GameMaster.cpp
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 Master Game Controller - links together all the game classes via composition
 
 */

#include "GameMaster.h"

GameMaster::GameMaster() : SDL_Program() {
    //init SDL stuff here? Or in play?
}

GameMaster::~GameMaster() {
    cleanUp();
}

//this starts the master game
void GameMaster::play() {
    SDL_Init(); //maybe quit program if this returns false?
    
    
    
    
    return;
}

//-----------------------------------------------------------------------------
//      Basic SDL Methods (init, clean up, update screen)
//-----------------------------------------------------------------------------

//sets up the screen and the background
bool GameMaster::SDL_Init(int width, int height, int bpp, std::string caption) {
    
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        std::cout << "ERR: SDL_INIT_EVERYTHING was not successful" << std::endl;
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL ) {
        std::cout << "ERR: Screen could not be initialized" << std::endl;
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( caption.c_str(), NULL );
    
    //If everything initialized fine
    return true;
}


void GameMaster::updateScreen() {
    //SDL method to update the screen
    //must be called for images that have been applied to the screen to show up
    if (SDL_Flip(screen) == -1) std::cout << "ERR: Updating screen failed" << std::endl;
    return;
}

//Frees all of GameMaster's surfaces, and calls the clean up method of its composed classes
void GameMaster::cleanUp() {
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    
    //**Call other class' cleanUp method here**
    
    //Quit SDL
    SDL_Quit();
    
    //Close a font that was used
    //TTF_CloseFont( font );
    
    //Quit SDL_ttf (deals with font)
    TTF_Quit();
    
    return;
}

//-----------------------------------------------------------------------------
//      Snap Region Methods
//-----------------------------------------------------------------------------

//adds a rect to the screen that will  be used to snap tokens into place
void GameMaster::setUpSnapRegion(int x, int y, int width, int height) {
    snapImage = createBlankSurface(NULL, width, height);
    
    snapRegion.x = x;
    snapRegion.y = y;
    // next two not necessarily needed
    snapRegion.w = snapImage->w;
    snapRegion.h = snapImage->h;
    
    SDL_FillRect( snapImage, NULL, SDL_MapRGB( snapImage->format, 0xCC, 0xCC, 0xCC ) );
    applySurface(x, y, snapImage, snapRegion, screen, NULL);
    return;
}

//adds a visual representation of the snap region to the screen
void GameMaster::applySnapRegion(SDL_Surface *) {
    applySurface(snapRegion.x, snapRegion.y, snapImage, snapRegion, screen, NULL);
    return;
}

//creates the blank surface applied to the screen by applySnapRegion
// credit: http://www.cplusplus.com/forum/general/9063/
SDL_Surface* GameMaster::createBlankSurface(Uint32 flags, int width, int height) {
    // 'display' is the surface whose format you want to match
    //  if this is really the display format, then use the surface returned from SDL_SetVideoMode
    
    const SDL_PixelFormat& fmt = *(screen->format);
    return SDL_CreateRGBSurface(flags, width, height,
                                fmt.BitsPerPixel,
                                fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

//-----------------------------------------------------------------------------
