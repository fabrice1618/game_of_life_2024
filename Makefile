game: main.cpp InitError.cpp InitError.h
	g++ -o game main.cpp InitError.cpp -lSDL2

clean:
	rm game