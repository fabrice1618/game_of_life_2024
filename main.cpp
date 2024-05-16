#include <iostream>
#include <stdlib.h>

#include "Population.h"
#include "Config.h"
#include "GameOfLife.h"
#include "Clepsydre.h"

int main(int argc, char* argv[]) 
{
    // Récupérer la configuration avec les arguments de ligne de commande
    Config config = Config(argc, argv);

    // Création de la population
    Population population(config);
    population.initRandom(config.getRandomAlea());

    GameOfLife game(config, &population);
    // Créer un timer pour les générations
    Clepsydre generation_timer = config.getGenerationDelay();

    do {
        if (generation_timer.check()) {
            game.clearScreen();
            game.draw();
            population.evoluer();
        }

        game.traiter_evenements();
    } while (game.getState() != GAME_QUIT);

}