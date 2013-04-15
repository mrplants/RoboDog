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

SDL_LoopToken::SDL_LoopToken(std::string filename, std::string ID)
: SDL_Token(filename) {}
