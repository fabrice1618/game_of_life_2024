#include <ctime>
#include <cassert>
#include "Population.h"
#include "Config.h"

Population::Population(Config config)
{
    m_size_x = config.getSizeX();
    m_size_y = config.getSizeY();
    m_actuel = new Grille(m_size_x, m_size_y);
}

Population::~Population()
{
    // Libérer la grille utilisée
    delete m_actuel;
}

int Population::getSizeX()
{
    return m_size_x;
}

int Population::getSizeY()
{
    return m_size_y;
}

int Population::getXY(int x, int y)
{
    return (int)m_actuel->xy(x, y);
}

int Population::count_row(int row)
{
    int count = 0;

    for (int x = 0; x < m_size_x; x++) {
        count += getXY(x, row);
    }
    return count;
}

int Population::count_col(int col)
{
    int count = 0;

    for (int y = 0; y < m_size_y; y++) {
        count += getXY(col, y);
    }
    return count;
}

void Population::evoluer()
{
    m_generation++;

    // Vérifier si il faut agrandir la grille
    int new_size_x = m_size_x;
    int new_size_y = m_size_y;
    int offset_x = 0;
    int offset_y = 0;

    int growSizeX = std::min((int)m_size_x / 10, 1);
    int growSizeY = std::min((int)m_size_y / 10, 1);

    // growNorth
    if (count_row(0) > 0) {
        offset_y = growSizeY;
        new_size_y += growSizeY;
    }
    // growSouth
    if (count_row(m_size_y - 1) > 0) {
        new_size_y += growSizeY;
    }
    // growWest
    if (count_col(0) > 0) {
        offset_x = growSizeX;
        new_size_x += growSizeX;
    }
    // growEast
    if (count_col(m_size_x - 1) > 0) {
        new_size_x += growSizeX;
    }

    if (m_size_x != new_size_x || m_size_y != new_size_y) {
        Grille* resized = new Grille(new_size_x, new_size_y);
        copy_grid_offset(resized, offset_x, offset_y);

        // Remplacer la grille
        replace_grid(resized);
    }
    
    Grille* future = new Grille(m_size_x, m_size_y);
    next_state(future);

    // Remplacer la grille
    replace_grid(future);
}

void Population::replace_grid(Grille* nouvelle)
{
    delete m_actuel;
    m_actuel = nouvelle;
    m_size_x = nouvelle->getSizeX();
    m_size_y = nouvelle->getSizeY();
}

int Population::count_around(int cell_x, int cell_y)
{
    int nb_vivantes = 0;

    for (int y = cell_y-1; y <= cell_y+1; y++) {
        for (int x = cell_x-1; x <= cell_x+1; x++) {
            if (x < 0 || x > (m_size_x - 1) || y < 0 || y > (m_size_y - 1)) {
                continue;
            }
            if (x == cell_x && y == cell_y) {
                continue;
            }

            nb_vivantes += getXY(x, y);
        }
    }

    return(nb_vivantes);
}

void Population::next_state(Grille* future)
{
    int nb_autour;

    for (int y=0; y < getSizeY(); y++) {
        for (int x=0; x < getSizeX(); x++) {
            // Compter le nombre de celulles vivantes autour
            nb_autour = count_around(x, y);

            if (getXY(x, y) == 1) {
                // Si la celulle etait vivante
                if (nb_autour == 2 || nb_autour == 3) {
                    future->xy(x, y) = 1;
                }
            } else {
                // Si la celulle etait morte
                if (nb_autour == 3) {
                    future->xy(x, y) = 1;
                }
            }
        }
    }
}


void Population::initRandom(int random_alea)
{
    // Initialiser le générateur de nombre pseudo-aléatoires.
    srand(time(NULL));

    for (int y = 0; y < m_size_y; y++) {
        for (int x = 0; x < m_size_x; x++) {
            m_actuel->xy(x, y) = rand() % 100 < random_alea ? 1 : 0;
        }
    }
}

void Population::copy_grid_offset(Grille* copie, int offset_x, int offset_y)
{
    for (int y=0; y < m_size_y; y++) {
        for (int x=0; x < m_size_x; x++) {
            copie->xy(x + offset_x, y + offset_y) = getXY(x, y);
        }
    }
}
