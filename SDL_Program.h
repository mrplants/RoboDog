//
//  SDL_Program.h
//  BASE CLASS for SDL components of Coding Game
//
//  Created by Maribeth Rauh on 3/29/13
//
//      This program is a **base class** for the SDL classes our coding game uses.  It provides the basic
//  SDL methods that are used by every SDL class such as init, clean_up, and load_image and data members
//  that are equally essential, such as the screen.
//  **Abstract so cannot be instantiated

#ifndef SDL_PROGRAM
#define SDL_PROGRAM

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

class SDL_Program {
public:
    SDL_Program();  //constructor
    
    TTF_Font *loadFont(std::string, int);  //takes single filename, opens and returns a font
    SDL_Surface *loadImage(std::string);   //takes single filename, loads image, optimizes it to screen and returns it
    SDL_Rect createRect(SDL_Surface *, int, int); //creates an SDL_Rect that corresponds to an image (SDL_Surface)
    SDL_Rect applySurface(int, int, SDL_Surface *, SDL_Rect, SDL_Surface *, SDL_Rect *); //blits image to destination at (x, y)
    
    //NOTE: update for new class heirarchy later...possibly make pure virtual here
    bool mouseOverImage(SDL_Rect, int, int); //checks if the mouse is located within the perimeter of the image
    
    virtual void cleanUp() = 0; //each derived class will implement this to free the surfaces they create

};

#endif /* defined SDL_PROGRAM */
