/*
 GameMaster.h
 
 Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

 Master Game Controller - links together all the game classes via composition
 
 */

#ifndef GAME_MASTER
#define GAME_MASTER

/*
#include "SDL_Program.h" //base class for GameMaster.h
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

class GameMaster {

  public:
    GameMaster();
    ~GameMaster();
    
    void play(); //this starts the master game
    void initSDLStuff(); //sets up the screen and the background
    
  private:
    //show welcome screen
    //show high scores

    SDL_Surface * screen; //screen or canvas all images are blit onto
    SDL_Surface * background; //whatever fills the whole screen's background
    SDL_Rect snapRegion; //rectangle that defines the area an image will snap to
    SDL_Surface *snapImage; //visual representation of the snap region (probably not needed for final project)
    
    void setUpSnapRegion(int, int, SDL_Surface *); //adds a rect to the screen that will  be used to snap tokens into place
    void applySnapRegion(SDL_Surface *); //adds a visual representation of the snap region to the screen
    SDL_Surface* createBlankSurface(Uint32 flags, int width, int height, const SDL_Surface* screen); //creates the blank surface applied to the screen by applySnapRegion

    //interpreter
    //token queue
    //game world

};

#endif // defined GAME_MASTER
