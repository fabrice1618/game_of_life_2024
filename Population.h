#pragma once
#include "Config.h"
#include "Grille.h"

class Population {
    private:
        int m_size_x = SIZE_X;
        int m_size_y = SIZE_Y;
        int m_generation_delay = GENERATION_DELAY;
        int m_population = 0;
        int m_generation = 0;
        int m_generation_start = 0;
        Grille* m_actuel = nullptr;
    public:
        Population(Config config);
        ~Population();
//        void setSizeX(int x);
//        void setSizeY(int y);
        int getSizeX();
        int getSizeY();
        int getXY(int x, int y);
//        void setGenerationDelay(int generationDelay);
        bool attendre_generation();
        void evoluer();
        void initRandom(int random_alea);
//        void dump();
};
