make: main

#Missing:
#TokenQueue/Token classes
#Interpreter (and its composed classes?)
#GameWorld and its composed classes

main: main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o CodeToken.o
	g++ main.o GameMaster.o TokenQueue.o SDL_Program.o SDL_Token.o CodeToken.o -o main -lSDL -lSDL_image -lSDL_ttf
    
main.o: main.cpp
	g++ -c main.cpp -lSDL -lSDL_image -lSDL_ttf
    
GameMaster.o: GameMaster.h  GameMaster.cpp TokenQueue.cpp SDL_Program.cpp constants.h
	g++ -c GameMaster.cpp TokenQueue.cpp SDL_Program.cpp -lSDL -lSDL_image -lSDL_ttf

SDL_Program.o: SDL_Program.cpp SDL_Program.h
	g++ -c SDL_Program.cpp -lSDL -lSDL_image -lSDL_ttf
    
SDL_Token.o: SDL_Token.cpp SDL_Token.h
	g++ -c SDL_Token.cpp -lSDL -lSDL_image -lSDL_ttf
    
#SDL_LoopToken.o: SDL_LoopToken.cpp SDL_LoopToken.h
#	g++ -c SDL_LoopToken.cpp -lSDL -lSDL_image -lSDL_ttf
    
TokenQueue.o: TokenQueue.cpp TokenQueue.h
	g++ -c TokenQueue.cpp -lSDL -lSDL_image

CodeToken.o: CodeToken.cpp CodeToken.h SDL_Token.o #SDL_LoopToken.o
	g++ -c CodeToken.cpp -lSDL -lSDL_image

#Interpreter.o: Interpreter.cpp Interpreter.h
#	g++ -c Interpreter.cpp
#
#GameWorld.o: GameWorld.cpp GameWorld.h
#	g++ -c GameWorld.cpp
#
#GameAnimation.o: GameAnimation.cpp GameAnimation.h
#	g++ -c GameAnimation.cpp
#
clean:
	rm -f *.o main