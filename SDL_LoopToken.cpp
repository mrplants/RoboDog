/*
 * SDL_LoopToken.cpp
 *
 * Created by Maribeth E Rauh
 *
 * The visual component of a token the user puts into their code- specifically one that
 * corresponds to a loop or if statement
 * NOTE: This class will represent two different visual components (for and while loop)
 */

#include "SDL_LoopToken.h"

SDL_LoopToken::SDL_LoopToken(std::string ID) : SDL_Token(ID) {
	 if (!ID.compare("open_loop"))
        setSurface(loadImage("tokenImages/openLoopToken.jpg")); //load the file for open_loop token element
     if (!ID.compare("close_loop"))
        setSurface(tokenSurface = loadImage("tokenImages/closeLoopToken.jpg")); //load the file for close_loop token element
}
