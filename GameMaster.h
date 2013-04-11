//Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh
//master game controller - links together the game classes
//has the game classes composed into it

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

class GameMaster {

  public:
    GameMaster();
    ~GameMaster();
    
    void play(); //this starts the master game
    void initSDLStuff(); //sets up the screen and the background
    
  private:
    //show welcome screen
    //show high scores

    SDL_Surface * screen;
    SDL_Surface * background;

    //interpreter
    //token queue
    //game world

};
