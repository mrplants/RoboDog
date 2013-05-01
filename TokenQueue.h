/*
  TokenQueue.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
  
  Allows for easy access to ordering tokens in the UI
  As tokens are added to the token-train, their pointers are inserted or added into the deque
  When the code is ready to be interpretted and run, this queue is dispatched to the interpreter and executed
  
  Composed classes:
    CodeToken - the individual token component
  */


#ifndef __Coding_Game__TokenQueue__
#define __Coding_Game__TokenQueue__

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "CodeToken.h"
#include "pthread.h"
#include "constants.h"


class TokenQueue
{
public:
	
#pragma mark -
#pragma Destructor and Constructor
	
	TokenQueue();
	//constructor
	
	~TokenQueue();
	//destructor. Deletes all tokens from memory
	
#pragma mark -
#pragma mark Methods About Changing the Queue
	
	void addTokenToEnd(CodeToken);
	//adds a token to the end of the tokenQueue
	
	void removeTokenAtIndex(int = 0);
	// removes the token at the specified index and deletes it from memory
	// when loop tokens are removed, their corresponding open or close token must be as well, since they are added pairwise, they should be removed that way.
	
	bool mouseOverToken(int, int);
	//checks if the mouse was clicked over an existing token or one in the library
	
	void newToken(std::string, int, int); //for actions
	//creates a new token, which is added to the end of the queue, and made the active token
	
#pragma mark -
#pragma mark Methods About Accessing the Queue
	
	CodeToken getTokenAtIndex(int = 0);
	//returns a pointer to the token at the specified index
	
	CodeToken operator[](int);
	const CodeToken operator[](int) const;

	std::vector<std::vector<int> > getInterpreterVector();
	
	void printQueue();
  
#pragma mark -
#pragma mark Methods About Manipulating Tokens on the Screen

	void translateActiveToken(int, int);
	//moves a token a relative amount, generally called when being dragged by the mouse
	
	void translateToken(CodeToken*, int, int);
	//moves a token a relative amount, generally called when being dragged by the mouse
	
	void snapActiveToken();
	//snaps the active token into place in the token pane and releases it
	
	void shiftTokensUp(int);
	//moves all tokens below the one inserted by one token's space up

	void shiftTokensDown(int);
	//moves all tokens below the one inserted by one token's space down

	void releaseActiveToken();
	//makes the token that is currently active no longer
	
	void updateScreen(SDL_Surface *);
	
private:
	std::deque<CodeToken> _tokenDeque;
	//will be returned to GameMaster upon request
	
	bool overTokenStack(int, int, int);
	//checks if the mouse is over certain portions of the token library
	
	CodeToken *activeTokenPtr;
	
};

#endif /* defined(__Coding_Game__TokenQueue__) */
