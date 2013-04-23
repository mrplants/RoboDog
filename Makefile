make: main

#Missing:
#TokenQueue/Token classes
#Interpreter (and its composed classes?)
#GameWorld and its composed classes

main: main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o CodeToken.o Interpreter.o GameAnimation.o
	g++ main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o CodeToken.o Interpreter.o GameAnimation.o -o main -lSDL -lSDL_image -lSDL_ttf
    
main.o: main.cpp GameMaster.o
	g++ -c main.cpp -lSDL -lSDL_image -lSDL_ttf
    
GameMaster.o: GameMaster.cpp GameMaster.h TokenQueue.o SDL_Program.o Interpreter.o constants.o GameWorld.o
	g++ -c GameMaster.cpp GameMaster.h TokenQueue.o SDL_Program.o Interpreter.o constants.o GameWorld.o constants.h GameWorld.h -lSDL -lSDL_image -lSDL_ttf

SDL_Program.o: SDL_Program.cpp SDL_Program.h
	g++ -c SDL_Program.cpp -lSDL -lSDL_image -lSDL_ttf
    
SDL_Token.o: SDL_Token.cpp SDL_Token.h
	g++ -c SDL_Token.cpp -lSDL -lSDL_image -lSDL_ttf
    
SDL_LoopToken.o: SDL_LoopToken.cpp
	g++ -c SDL_LoopToken.cpp -lSDL -lSDL_image -lSDL_ttf
    
TokenQueue.o: TokenQueue.cpp TokenQueue.h CodeToken.o
	g++ -c TokenQueue.cpp TokenQueue.h CodeToken.o -lSDL -lSDL_image

CodeToken.o: CodeToken.cpp CodeToken.h SDL_Token.o SDL_LoopToken.o
	g++ -c CodeToken.cpp CodeToken.h SDL_Token.o SDL_LoopToken.o -lSDL -lSDL_image

Interpreter.o: Interpreter.cpp Interpreter.h
	g++ -c Interpreter.cpp Interpreter.h -lSDL_image

GameWorld.o: GameWorld.cpp GameWorld.h GameAnimation.o GameMaster.o
	g++ -c GameWorld.cpp GameWorld.h GameAnimation.o GameMaster.o -lSDL_image

GameAnimation.o: GameAnimation.cpp GameAnimation.h GameMaster.o
	g++ -c GameAnimation.cpp GameAnimation.h GameMaster.o

GameStats.o: GameStats.cpp GameStats.h
	g++ -c GameStats.cpp

Mario.o: Mario.cpp Mario.h
	g++ -c Mario.cpp Mario.h -lSDL -lSDL_image

clean:
	rm -f *.o main
