/*
  Interpreter.h
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
 
  Interprets. The tokens.
  BAM.
  */

#ifndef __project_interpretter__Interpreter__
#define __project_interpretter__Interpreter__

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include "GameWorld.h"


using namespace std;

typedef vector<int> VecOfInt;
typedef vector<VecOfInt> v2int;

class Interpreter {
    
public:
    
	Interpreter(); // Default constructor

	// This is the interpreter basically
	void parse( vector<vector<int> > user_program, GameWorld *world );
    
	// Prints the raw program and param codes constructed
	void printRaw();
    
private:
	vector<vector<int> > user_program;
    
};

#endif /* defined(__project_interpretter__Interpreter__) */
