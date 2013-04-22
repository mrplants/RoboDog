/*
 GameMaster.h
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
 
 Master Game Controller - links together all the game classes via composition
 
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

//library for C POSIX multithreading
#include "pthread.h"
//Base class for GameMaster.h
#include "SDL_Program.h"
//contains program-wide constants like screen size
#include "constants.h"

#include "TokenQueue.h"
#include "Interpreter.h"
#include "CodeToken.h"
#include "GameWorld.h"

class GameMaster : public SDL_Program {
    
public:
    GameMaster();
    ~GameMaster();
    
    void play(); //this starts the master game
    //sets up the screen and the background, the last parameter is for the title of the window
    bool initializeSDL(int = SCREEN_WIDTH, int = SCREEN_HEIGHT, int = SCREEN_BPP, std::string = "Robodog");

    void updateScreen();
    
private:
    //show welcome screen
    //show high scores
    
    SDL_Surface *screen; //screen or canvas all images are blit onto
    SDL_Surface *background; //whatever fills the whole screen's background
    
    
    //SDL_Rect applySurface(int, int, SDL_Surface *, SDL_Rect, SDL_Surface *, SDL_Rect *); //blits image to destination at (x, y)
    bool checkMousePositionOnPress(int, int);
    bool mouseInTokenPane(int, int);
    //bool mouseInTokenLibrary(int, int);
    virtual void cleanUp(); //implemented in this class
    
    //------------- Snap Region Data Members/Methods -------------
    SDL_Rect tokenPane; //area that user will drop tokens to write their code
    /*SDL_Rect snapRegion; //rectangle that defines the area an image will snap to
    SDL_Surface *snapImage; //visual representation of the snap region (probably not needed for final project)
    
    void setUpSnapRegion(int, int, int, int); //adds a rect to the screen that will  be used to snap tokens into place
    void applySnapRegion(SDL_Surface *); //adds a visual representation of the snap region to the screen
    SDL_Surface* createBlankSurface(Uint32 flags, int width, int height); //creates the blank surface applied to the screen by applySnapRegion
    *///------------------------------------------------------------
    
    void compileUserCode(); //called when user presses play, gets tokenQueue and gives it to the interpreter
    
    Interpreter interpreter;
    TokenQueue queueOfTokens;
    GameWorld gameWorld;
    
};

#endif // defined GAME_MASTER
