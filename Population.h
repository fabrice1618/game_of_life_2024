#pragma once

#include "Config.h"
#include "Grille.h"

class Population {
    private:
        int m_size_x = SIZE_X;
        int m_size_y = SIZE_Y;
        int m_generation = 0;
        int m_generation_start = 0;
        Grille* m_actuel = nullptr;
    public:
        Population(Config config);
        ~Population();
        int getSizeX();
        int getSizeY();
        int getXY(int x, int y);
        void evoluer();
        void initRandom(int random_alea);
    private:
        int count_around(int cell_x, int cell_y);
        void next_state(Grille* future);
        int count_col(int col);
        int count_row(int row);
        void replace_grid(Grille* nouvelle);
        void copy_grid_offset(Grille* copie, int offset_x, int offset_y);
};
