game: main.cpp InitSDLException.cpp InitSDLException.h Grille.cpp Grille.h Population.h Population.cpp Config.h Config.cpp GameOfLife.h GameOfLife.cpp
	g++ -o game main.cpp InitSDLException.cpp Grille.cpp Population.cpp Config.cpp GameOfLife.cpp -lSDL2

ex_grille: ex_grille.cpp Grille.cpp Grille.h
	g++ -o ex_grille ex_grille.cpp Grille.cpp

clean:
	rm game
	rm ex_grille