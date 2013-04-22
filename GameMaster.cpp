/*
 GameMaster.cpp
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 Master Game Controller - links together all the game classes via composition
 
 */

#include "GameMaster.h"

GameMaster::GameMaster() : SDL_Program() 
{
    initializeSDL(); //sets up SDL systems, screen, and background

    //area where tokens will be dropped
    tokenPane.x = 0;
    tokenPane.y = 0;
    tokenPane.h = SCREEN_HEIGHT * TOKEN_PANE_PERCENT_H;
    tokenPane.w = SCREEN_WIDTH * TOKEN_PANE_PERCENT_W;
}

GameMaster::~GameMaster()
{
    cleanUp();
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
            std::cout << "event detected" << std::endl;
            if (event.type == SDL_QUIT) {   // If user clicks 'x' in top left corner
                quit = true;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) { // If mouse was pressed down

                #warning More implementation needed in here
                mousePressedOnImage = checkMousePositionOnPress(event.motion.x, event.motion.y);
                
                //Because this method gets the change in the mouse's position since the last time it was called,
		//calling it here removes the big jump
                SDL_GetRelativeMouseState(&dx, &dy);
		//std::cout << dx << ", " << dy << std::endl;
                
            } else if (event.type == SDL_MOUSEBUTTONUP) { // If the mouse button was released
                mousePressedOnImage = false;
		
		      if (mouseInTokenPane(event.motion.x, event.motion.y)) { //NOTE: may be incorrect x and y
		          //tells TokenQueue to drop token, TQ will snap it and release it
		          queueOfTokens.snapActiveToken();
		  
		      } else {
		          //tells TQ to delete the last token in the queue (the active token)
		          queueOfTokens.releaseActiveToken();
		      }
                
            } else if (event.type == SDL_MOUSEMOTION && mousePressedOnImage) { // If the user clicks and drags
                
                SDL_GetRelativeMouseState(&dx, &dy); //gets mouse's change in position since last time this was called
		// Reapply image
                queueOfTokens.translateActiveToken(dx, dy); //moves the token however much the mouse moved
		
		/*//debugging output
                int xcoord = event.motion.x;
                int ycoord = event.motion.y;
                std::cout << "(" << xcoord << ", " << ycoord << ")" << std::endl;
                std::cout << "Changed: " << x << ", " << y << std::endl;
		*/
                
            }
            updateScreen();
        }
    }
    
    
    return;
}
//****************************************************************************

//calls the appropriate functions depending on where the mouse clicked
bool GameMaster::checkMousePositionOnPress(int x, int y)
{
	//if ( mouseInTokenLibrary(event.motion.x, event.motion.y) ) {
	//	  queueOfTokens.newToken(); //create a new token in the queue
	//	  mousePressedOnImage = true;
	//should a token in the library or in the pane be handled in the same function and have TokenQueue figure it out underneath?
	/*}else */if ( queueOfTokens.mouseOverToken(x, y) ) {
		  //the token the mouse was over is now the active token and can be dragged
		  return true;
		  
	} else if (0 /*user presses a play button*/) {




          // 
          // This is where it goes down...
          // 
          // 
          // 
          // 
		  compileUserCode();
	}
	return false;
}


//-----------------------------------------------------------------------------
//      CompileUserCode() Function. 
//-----------------------------------------------------------------------------

void GameMaster::compileUserCode() {

    cout << "In the compileUserCodeFunction" << endl;
    interpreter.parse(queueOfTokens.getInterpreterVector(), &world);

}




//-----------------------------------------------------------------------------
//      Basic SDL Methods (init, clean up, update screen)
//-----------------------------------------------------------------------------

//Sets up the screen surface and physical window
bool GameMaster::initializeSDL(int width, int height, int bpp, std::string caption) 
{
    //std::cout << "in sdl init" << std::endl;
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
    
    //load background image
    background = loadImage("background.png"); //method inherited from SDL_Program
    if (background == NULL) std::cout << "ERR: Background could not be loaded\n" << std::endl;
    
    //If everything initialized fine
    return true;
}

//NOTE: only x, y, and destination should be passed in, possibly clip at lower level-
//		offset and source known by class being called on
//blits image to destination at (x, y)
//Parameters 1, 2: x and y coordinates where image will be blitted
//Parameter 3: image to be blitted
//Parameter 4: SDL_Rect associated with the surface being blitted
//Parameter 5: image being blitted onto
//Parameter 6: which clip of source to blit
/*
SDL_Rect applySurface(int x, int y, SDL_Surface *source, SDL_Rect offset, SDL_Surface *destination, SDL_Rect *clip) {
    offset.x+=x;
    offset.y+=y;
    
    SDL_BlitSurface( source, clip, destination, &offset );
    return offset;
}*/

//checks if mouse is in the lefthand pane that tokens can be dropped in 
bool GameMaster::mouseInTokenPane(int x, int y) {
 if (x > tokenPane.x && y > tokenPane.y && x <= (tokenPane.x + tokenPane.w) && y <= (tokenPane.y + tokenPane.h)) {
    return true;
 } else {
   return false;
 }
}

void GameMaster::updateScreen() 
{
    //Re-applies the background
    //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) ); //fills screen with white
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    SDL_BlitSurface(background, NULL, screen, &offset);
    
    //Call all update screen methods in game and token queue
    queueOfTokens.updateScreen(screen);
    //gameWorld.updateScreen(screen);
    
    //SDL_Flip must be called for images that have been applied to the screen to show up
    if (SDL_Flip(screen) == -1) std::cout << "ERR: Updating screen failed" << std::endl;
    return;
}

//Frees all of GameMaster's surfaces, and calls the clean up method of its composed classes
void GameMaster::cleanUp()
{
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
