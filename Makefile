make: main

main: main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o SDL_LoopToken.o CodeToken.o Interpreter.o GameAnimation.o Mario.o GameStats.o GameWorld.o
	g++ main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o CodeToken.o Interpreter.o GameAnimation.o GameWorld.o Mario.o GameStats.o SDL_LoopToken.o -o main -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
    
main.o: main.cpp
	g++ -c main.cpp
    
GameMaster.o: GameMaster.cpp GameMaster.h TokenQueue.o SDL_Program.o Interpreter.o GameWorld.o
	g++ -c GameMaster.cpp #-lSDL -lSDL_image 

SDL_Program.o: SDL_Program.cpp SDL_Program.h
	g++ -c SDL_Program.cpp #-lSDL -lSDL_image
    
SDL_Token.o: SDL_Token.cpp SDL_Token.h
	g++ -c SDL_Token.cpp #-lSDL -lSDL_image
    
SDL_LoopToken.o: SDL_LoopToken.cpp SDL_LoopToken.h
	g++ -c SDL_LoopToken.cpp -lSDL_ttf #-lSDL -lSDL_image
    
TokenQueue.o: TokenQueue.cpp TokenQueue.h
	g++ -c TokenQueue.cpp #-lSDL -lSDL_image

CodeToken.o: CodeToken.cpp CodeToken.h 
	g++ -c CodeToken.cpp

Interpreter.o: Interpreter.cpp Interpreter.h
	g++ -c Interpreter.cpp

GameWorld.o: GameWorld.cpp GameWorld.h
	g++ -c GameWorld.cpp #-lSDL -lSDL_image

GameAnimation.o: GameAnimation.cpp GameAnimation.h
	g++ -c GameAnimation.cpp #-lSDL -lSDL_image

GameStats.o: GameStats.cpp GameStats.h
	g++ -c GameStats.cpp

Mario.o: Mario.cpp Mario.h
	g++ -c Mario.cpp #-lSDL -lSDL_image

clean:
	rm -f *.o *.gch main *~
