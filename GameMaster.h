/*
 GameMaster.h
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

 Master Game Controller - links together all the game classes via composition
 
 */

#ifndef GAME_MASTER
#define GAME_MASTER

/*
#include //Maribeth's classes
#include //Jon's classes
#include //Sean's classes
#include //Daniel's classes
*/

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

class GameMaster : public SDL_Program {

  public:
    GameMaster();
    ~GameMaster();
    
    void play(); //this starts the master game
    
  private:
    //show welcome screen
    //show high scores
    
    //Screen attributes
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_BPP = 32;
    SDL_Surface * screen; //screen or canvas all images are blit onto
    SDL_Surface * background; //whatever fills the whole screen's background
    
    //sets up the screen and the background, the last parametere is for the title of the window
    bool SDL_Init(int = SCREEN_WIDTH, int = SCREEN_HEIGHT, int = SCREEN_BPP, std::string = "Robodog");
    void updateScreen();
    virtual void cleanUp(); //implemented in this class
    
    //##### Snap Region Data Members/Methods #######//
    SDL_Rect snapRegion; //rectangle that defines the area an image will snap to
    SDL_Surface *snapImage; //visual representation of the snap region (probably not needed for final project)
    
    void setUpSnapRegion(int, int, int, int); //adds a rect to the screen that will  be used to snap tokens into place
    void applySnapRegion(SDL_Surface *); //adds a visual representation of the snap region to the screen
    SDL_Surface* createBlankSurface(Uint32 flags, int width, int height); //creates the blank surface applied to the screen by applySnapRegion
    //#############################################//
    
    //interpreter
    //token queue
    //game world

};

#endif // defined GAME_MASTER
