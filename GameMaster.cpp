/*
 GameMaster.cpp
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 Master Game Controller - links together all the game classes via composition
 
 */

#include "GameMaster.h"

GameMaster::GameMaster() : SDL_Program() {
    //init SDL stuff here? Or in play?
    
    //area where tokens will be dropped
    tokenPane.x = 0;
    tokenPane.y = 0;
    tokenPane.h = SCREEN_HEIGHT * TOKEN_PANE_PERCENT_H;
    tokenPane.w = SCREEN_WIDTH * TOKEN_PANE_PERCENT_W;
}

GameMaster::~GameMaster() {
    cleanUp();
}

//****************************************************************************
//This starts the master game
void GameMaster::play() {
    SDL_Init(); //maybe quit program if this returns false?
    
    SDL_Event event;
    bool quit = false;
    int dx, dy;
    bool mousePressedOnImage = false;
    
    while (!quit) {

        // Processes events while events are in the queue
        while (SDL_PollEvent( &event )) {
            
            if (event.type == SDL_QUIT) {   // If user clicks 'x' in top left corner
                quit = true;
                
            }else if (event.type == SDL_MOUSEBUTTONDOWN) { // If mouse was pressed down
                mousePressedOnImage = true;//in TQ mouseOverImage(imageRect, event.motion.x, event.motion.y);
                SDL_GetRelativeMouseState(&dx, &dy); 
		//std::cout << dx << ", " << dy << std::endl;
                
            }else if (event.type == SDL_MOUSEBUTTONUP) {
                mousePressedOnImage = false;
		//NOTE: may be incorrect x and y
		if (mouseInTokenPane(event.motion.x, event.motion.y)) {
		  //tells TokenQueue to drop token, TQ will snap it and release it
		  queueOfTokens.snapActiveToken();
		}else{
		  //tells TQ to release token
		  queueOfTokens.releaseActiveToken();
		}
                
            }else if (event.type == SDL_MOUSEMOTION && mousePressedOnImage) {
                
                SDL_GetRelativeMouseState(&dx, &dy);
//                int xcoord = event.motion.x;
//                int ycoord = event.motion.y;
//                std::cout << "(" << xcoord << ", " << ycoord << ")" << std::endl;
                //std::cout << "Changed: " << x << ", " << y << std::endl;

                // Reapply image
                queueOfTokens.translateToken(dx, dy, screen);
            }
            updateScreen();
        }
    }
    
    
    return;
}
//****************************************************************************


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

//checks if mouse is in the lefthand pane that tokens can be dropped 
bool GameMaster::mouseInTokenPane(int x, int y) {
 if (x > tokenPane.x && y > tokenPane.y && x <= (tokenPane.x + tokenPane.w) && y <= (tokenPane.y + tokenPane.h)) {
    return true;
 }else{
   return false;
 }
}

void GameMaster::updateScreen() {
    //SDL method to update the screen
    // Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    //Call all update screen methods in game and token queue
    queueOfTokens.updateScreen(screen);
    //gameWorld.updateScreen(screen);
    
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
/*
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
*/
//-----------------------------------------------------------------------------
