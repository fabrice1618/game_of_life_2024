#pragma once
#include <stdlib.h>

// Valeurs par défaut des parametres
#define SIZE_X 100
#define SIZE_Y 50
#define GENERATION_DELAY 500

#define CELL_COLOR_R 18
#define CELL_COLOR_G 14
#define CELL_COLOR_B 252

#define RANDOM_ALEA 25

// Options des options de la ligne de commande
#define HELP_OPTION 'h'
#define SIZE_X_OPTION 'x'
#define SIZE_Y_OPTION 'y'
#define GENERATION_DELAY_OPTION 'd'
#define RANDOM_ALEA_OPTION 'a'
#define CELL_COLOR_R_OPTION 'r'
#define CELL_COLOR_G_OPTION 'g'
#define CELL_COLOR_B_OPTION 'b'

void print_usage(char* executable);

class Config
{
private:
    int m_size_x = SIZE_X;
    int m_size_y = SIZE_Y;
    int m_generation_delay = GENERATION_DELAY;;
    int m_cell_color_r = CELL_COLOR_R;
    int m_cell_color_g = CELL_COLOR_G;
    int m_cell_color_b = CELL_COLOR_B;
    int m_random_alea = RANDOM_ALEA;

public:
    Config(int argc, char *argv[]);
    int getSizeX() { return m_size_x; };
    int getSizeY() { return m_size_y; };
    int getGenerationDelay() { return m_generation_delay; };
    int getCellColorR() { return m_cell_color_r; };
    int getCellColorG() { return m_cell_color_g; };
    int getCellColorB() { return m_cell_color_b; };
    int getRandomAlea() { return m_random_alea; };
};

