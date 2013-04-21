all:	main

main:	Background.o
	g++ Background.o -o main -lSDL_image

Background.o:	Background.cpp
		g++ -c Background.cpp -lSDL_image

clean:
	rm -f *.o main