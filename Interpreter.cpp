//
//  Interpreter.cpp
//  project_interpretter
//
//  Created by Jon Gautsch on 3/26/13.
//  Copyright (c) 2013 Jon Gautsch. All rights reserved.
//

#include "Interpreter.h"


Interpreter::Interpreter() {
    cout << "Interpreter initialized:\n\n";
    cout << "This is the wrong constructor though." << endl;
    
}


//Interpreter::Interpreter(vector<int> program_codes, vector<int> params_codes) {
Interpreter::Interpreter(vector<int> program_codes, vector<int> numTimes, vector<int> IDnums) {
    
    // This will resize the v2int to the appropriate size
    // This prevents seg fault when accessing locations
    
    // user_program.resize(program_codes.size());
    // for (int i = 0; i < program_codes.size(); i++) {
    //     user_program[i].resize(3);
    // }
    
    // //vector<int> temp = {0, 0};  // The little sets of two that will be pushed into the
    //                             // user program
    
    // for (int i = 0; i < program_codes.size(); i++) {
    //     user_program[i][0] = program_codes[i];
    //     user_program[i][1] = numTimes[i];
    //     user_program[i][2] = IDnums[i];
    // }
    
    // printRaw();
    // parse( user_program,  );
}


void Interpreter::printRaw() {
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




/***********************************/
// parse() function:
//  -
/***********************************/



//  Here is the numeric codes for the different commands of the "language" to be used in our game
//
//  1 - step
//  2 - jump
//  3 - turn
//  4 - kick
//  5 - open loop
//  6 - close loop


void Interpreter::parse( vector<vector<int> > program, GameWorld *world_pointer ) {
    
    
    // 'i' is the index in the program,
    
    // NOTE: When it recurses, its looping, and then moving forward, but when it loops, it actually
    //       needs to skip over the instructions its passing back to itself. Because otherwise
    //       they're executed an extra set of times.
    for ( int i = 0; i < program.size(); i++ ) {
        
        usleep(500000);
        
        switch (program[i][0]) {
            case 1:
                if (program[i][1] == 0) {
                    cout << "*step one space (0 entered)" << endl;
                } else {
                    for (int j = 0; j < program[i][1]; j++) {
                        cout << "step one space" << endl;
                        world_pointer->step();
                    }
                }
                break;
                
            case 2:
                if (program[i][1] == 0) {
                    cout << "*Jump once (0 entered)" << endl;
                } else {
                    for (int j = 0; j < program[i][1]; j++) {
                        cout << "Jump once" << endl;
                        world_pointer->jump();
                    }
                }
                break;
                
            case 3:
                if (program[i][1] == 0) {
                    cout << "*Turn around (0 entered)" << endl;
                } else {
                    for (int j = 0; j < program[i][1]; j++) {
                        cout << "Turn around" << endl;
                        world_pointer->turn();
                    }
                }
                break;
                
            case 4:
                if (program[i][1] == 0) {
                    cout << "*Kick once (0 entered)" << endl;
                } else {
                    for (int j = 0; j < program[i][1]; j++) {
                        cout << "Kick once" << endl;
                        world_pointer->kick();
                    }
                }
                break;
                
            // It's about to get recursive
                
            case 5: {
                cout << "{ Open loop }" << "  (should loop " << program[i][1] << " times)." << endl;

                // TODO: Refactor the following initialization lines to it's own function.
                // v2int recursed_program;
                vector<vector<int> > recursed_program;
                
                // Now find the length to the end of the loop
                int j = i;
                
                
                // While the program instruction code isn't a closing tag with the same IDnum as the
                // opening tag, increase the count of how many instructions are inside the "loop"
                while ( program[j][0] != 6 || program[j][2] != program[i][2] ) {
                    j++;
                }
                

                
                for (int k = i + 1; k <= j-1; k++) { // to get just the instructions between the instructions between the loop blocks at i and j
                    recursed_program.push_back(program[k]);
                }
                
                
                // Now, however many times is specified in the params, loop
                for (int k = 0; k < program[i][1]; k++) {
                    parse(recursed_program, world_pointer);
                }

                
                // Now that we've done the instructions inside the loop the appropriate number
                // of times, we need to increase the index to skip over them so that they're not
                // repeated an extra time
                i = j - 1;
                
                break;
            }
                
            case 6:
                cout << "{ Close loop }" << endl;
                break;
                
            default:
                break;
        }
    }
}
