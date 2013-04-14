/*
 * SDL_LoopToken.h
 * Subclassed from SDL_Token class
 *
 * Maribeth Rauh
 * 9 Apr 2013
 *
 * The visual component of a token the user puts into their code- specifically one that
 * corresponds to a loop or if statement
 * NOTE: This class represents two different visual components
 */

#ifndef SDL_LOOPTOKEN
#define SDL_LOOPTOKEN

#include <iostream>
#include <string>
#include "SDL_Token.h" //includes all SDL frameworks needed

class SDL_LoopToken : public SDL_Token {
  public:
    SDL_LoopToken(std::string, std::string); //parameters are ID ("if" or "loop") and subID for the action

    SDL_Rect getInnerSnapRegion(); //returns the snap region inside the loop where a conditional or action should snap
  
    //methods to enter and parse text
    void setInputBoxClicked(bool);
    void processKeyPressEvent(char); //ONLY CALL IF inputBoxClicked is true, 
    
    void cleanUp();
    
  private:
    //methods to set up inner snap region
    void setUpInnerSnapRegion(int, int, SDL_Surface *); //sets the the 
    void applyInnerSnapRegion(SDL_Surface *); //adds a visual representation of the snap region to the interface
    
    SDL_Rect innerSnapRegion; //area whose bounds will be checked to snap conditionals being dragged into the loop
    SDL_Surface *innerSnapReigonImage; //optional visual representation of the snap region
    
    bool inputBoxClicked;
    
    //SDL_Surface and associated rect are inherited from base class
};

#endif /* defined SDL_LOOPTOKEN */