#include <iostream>
#include <stdlib.h>

#include "Grille.h"
#include "Population.h"
#include "Config.h"
#include "GameOfLife.h"


void game_loop(Config config)
{
    Population population(config);
    population.initRandom(config.getRandomAlea());

    GameOfLife game(config, &population);

    while (game.getState() != GAME_QUIT) {

        game.traiter_evenements();
        if (game.getState() == GAME_QUIT) {
            break;
        }

        if (population.attendre_generation()) {
            game.clearScreen();
            game.draw();
            population.evoluer();
        }
    }
}


int main(int argc, char* argv[]) 
{
    Config config = Config(argc, argv);

    game_loop(config);
}