/*
  Interpreter.cpp
  Sean T Fitzgerald, Jon T Gautsch, Daniel Y Tamaru, Maribeth E Rauh

  Final Project CSE 20212 Spring 2013
 
  Interprets. The tokens.
  BAM.
  */

#include "Interpreter.h"

Interpreter::Interpreter() {}

//prints out the contents of the vectors the interpreter was passed
void Interpreter::printRaw()
{
	for (int i = 0; i < user_program.size(); i++) {
		cout << "[ "
		<< user_program[i][0]
		<< ", "
		<< user_program[i][1]
		<< ", "
		<< user_program[i][2]
		<<  " ]"
		<< endl;
	}
}

//***********************************
// parse() function
//
//  Here is the numeric codes for the different commands of the "language" to be used in our game:
//
//  1 - step
//  2 - jump
//  3 - turn
//  4 - kick
//  5 - open loop
//  6 - close loop

void Interpreter::parse( vector<vector<int> > program, GameWorld *world_pointer )
{
	//printRaw();

	// 'i' is the index in the program,
    
	// NOTE: When it recurses, its looping, and then moving forward, but when it loops, it actually
	//       needs to skip over the instructions its passing back to itself. Because otherwise
	//       they're executed an extra set of times.
	for ( int i = 0; i < program.size(); i++ ) {
		usleep(250000);
        
		switch (program[i][0]) {
			case 1:
				world_pointer->step();
				break;
                
			case 2:
				world_pointer->jump();
				break;
                
			case 3:
				world_pointer->turn();
				break;
                
			case 4:
				world_pointer->kick();
				break;
                
			// It's about to get recursive
			case 5: {
				// TODO: Refactor the following initialization lines to it's own function.
				// v2int recursed_program;
				vector<vector<int> > recursed_program;
                
				// Now find the length to the end of the loop
				int j = i;
				while( program[j][0] != 6 || program[j][2] != program[i][2])
					 j++;

				if (j == program.size()) //this means there isn't an end loop in the program
					return;

				for (int k = i + 1; k <= j-1; k++) // to get just the instructions between the instructions between the loop blocks at i and j
					recursed_program.push_back(program[k]); 
                
				// Now, however many times is specified in the params, loop
				for (int k = 0; k < program[i][1]; k++)
					parse(recursed_program, world_pointer);

				// Now that we've done the instructions inside the loop the appropriate number
				// of times, we need to increase the index to skip over them so that they're not
				// repeated an extra time
				i = j - 1;
                
				break;
			}
                
			case 6:
				//cout << "{ Close loop }" << endl;
				break;
                
			default:
				break;
		}
	}
}
