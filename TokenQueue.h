//
//  TokenQueue.h
//  Coding Game
//
//  Created by Sean Fitzgerald on 3/26/13.
//  Copyright (c) 2013 ND. All rights reserved.
//

//This class introduces the possibility of teaching a simple API for multithreaded programming

//It also allows for easy access to ordering tokens in the UI. This is the only queue we need from start to finish
//As tokens are added to the token-train, their pointers are inserted or added into this queue.
//When the code is ready to be interpretted and run, this queue is dispatched to the interpreter and executed
//As the queue is being interpretted, this queue will know which blocks have been run, which are running, and which have yet to be run.
//It has API to control how fast to wait between dispatching tokens to the interpreter.
//The wait time can be increased or decreased even after dispatching to make a program slow down or speed up.
//*In the future, this queue will be able to rewind a queue back throught the interpreter (This, however, requires work from both the interpreter and the queue)
//When the queue has finished running and is dismissed from memory, it deletes all the tokens it has from memory as well to remove all memory leaks from the system.



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
#pragma mark Methods About Dispatching Code
		
	//now implemented in gameMaster
	/*
	void dispatchTokenQueueToInterpreter();
	//this calls the tokenQueue to start dispatching
	//NB: IF THE PROGRAM WAS DISPATCHED AND PAUSED, IT WILL NOT GO TO THE BEGINNING UNLESS REWOUND. IT WILL CONTINUE FROM THE LAST TOKEN DISPATCHED.
	
	void pauseDispatching();
	//temporarily pauses the dispatching of the program to the interpreter
	
	void stopDispatching();
	//stops dispatching tokens, closes the interpreter, and rewinds the queue
	
	void rewind();
	//rewind the tokenQueue so that the next call of dispatchQueueToInterpreter() will start dispatching from the first token
	
	void unDispatchTokenQueueFromInterpreter();
	//starts pulling tokens back through the interpreter to undo what they have done. Maybe an extra feature. Very cool to have...
	
	void setWaitTime(int = 0);
	//sets the time between token dispatches to the interpretter
	
	int getWaitTime();
	//gets the time between token dispatches to the interpretter
	
	bool tokensAreBeingDispatched();
	//returns whether or not there are processes happening
	*/
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
  
 	// std::deque<CodeToken> getTokenQueue();
	//returns the deque of CodeTokens as is
  
	// deque<deque<int>> getInterpreterQueue();
	// the getter for John's interpreter metadata

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
	
	//now implemented in gameMaster
	/*
	
	int _waitTime;
	//amount of time between token dispatches to the interpreter
	
	int _interpreterProcessingIndex;
	//keeps track of which token is currently being processed through the interpreter
	
	pthread_t _interpreterThread;
	//separate processing thread for the interpreter
		
	bool _threadIsRunning;
	
	void dispatchTokensToInterpreterInThread(std::deque<CodeToken>, pthread_t);
	
	void *runTokenInInterpretter(threadTokenDataStruct);
	*/
	
	CodeToken *activeTokenPtr;
	
};

#endif /* defined(__Coding_Game__TokenQueue__) */
