make: main

#Missing:
#TokenQueue/Token classes
#Interpreter (and its composed classes?)
#GameWorld and its composed classes

main: main.o GameMaster.o SDL_Program.o SDL_Token.o SDL_LoopToken.o
    g++ main.o GameMaster.o -o main -lSDL -lSDL_image -lSDL_ttf
    
main.o: main.cpp GameMaster.h SDL_Program.h SDL_Token.h SDL_LoopToken.h
    g++ -c main.cpp -lSDL -lSDL_image -lSDL_ttf
    
GameMaster.o: GameMaster.h GameMaster.cpp
    g++ -c GameMaster.cpp

SDL_Program.o: SDL_Program.cpp SDL_Program.h
    g++ -c SDL_Program.cpp
    
SDL_Token.o: SDL_Token.cpp SDL_Token.h
    g++ -c SDL_Token.cpp
    
SDL_LoopToken.o: SDL_LoopToken.cpp SDL_LoopToken.h
    g++ -c SDL_LoopToken.cpp
    
#TokenQueue.o: TokenQueue.cpp TokenQueue.h
#   g++ -c TokenQueue.cpp

#Token.o: Token.cpp Token.h
#   g++ -c Token.cpp

#Interpreter.o: Interpreter.cpp Interpreter.h
#   g++ -c Interpreter.cpp

#GameWorld.o: GameWorld.cpp GameWorld.h
#   g++ -c GameWorld.cpp

#GameAnimation.o: GameAnimation.cpp GameAnimation.h
#   g++ -c GameAnimation.cpp

clean:
    rm -f *.o main