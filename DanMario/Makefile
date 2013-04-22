all:	main

main:	main.o Timer.o Mario.o Background.o
	g++ main.o Timer.o Mario.o Background.o -o main -lSDL_image

Background.o:	Background.cpp Background.h Defines.h Externs.h
	g++ -c Background.cpp Background.h Defines.h Externs.h -lSDL_image

Timer.o: Timer.cpp Timer.h Defines.h Externs.h
	g++ -c Timer.cpp Timer.h Defines.h Externs.h -lSDL_image

Mario.o: Mario.cpp Mario.h Defines.h Externs.h
	g++ -c Mario.cpp Mario.h Defines.h Externs.h -lSDL_image

Main.o: Main.cpp Mario.h Background.h Timer.h Defines.h Externs.h
	g++ -c Main.cpp Mario.h Background.h Timer.h Defines.h Externs.h -lSDL_image

clean:
	rm -f *.o main