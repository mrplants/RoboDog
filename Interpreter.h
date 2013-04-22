//
//  Interpreter.h
//  project_interpretter
//
//  Created by Jon Gautsch on 3/26/13.
//  Copyright (c) 2013 Jon Gautsch. All rights reserved.
//

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
    
    Interpreter();                                          // Default constructor
    Interpreter(vector<int> program, vector<int> numTimes, vector<int> IDnums);   // Takes the program and params

    // This is the interpreter basically
    void parse( vector<vector<int> > user_program, GameWorld *world );
    
    // Prints the raw program and param codes constructed
    void printRaw();
    
private:
    
    v2int user_program;
    GameWorld *world;
    
};

#endif /* defined(__project_interpretter__Interpreter__) */
