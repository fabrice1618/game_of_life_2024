#include <ctime>
#include "Population.h"
#include "Config.h"


Population::Population(Config config)
{
    m_size_x = config.getSizeX();
    m_size_y = config.getSizeY();
    m_generation_delay = config.getGenerationDelay();
}

Population::~Population()
{
    // Libérer la grille utilisée
    delete m_actuel;
}

/*
void Population::setSizeX(int x)
{
    if (x < 3 || x > 999) {
      fprintf(stderr, "Error: population x must be between 3 and 999\n");
      exit(EXIT_FAILURE);
    }
    if (m_generation_start == 0) {
        m_size_x = x;
        //std::cout << "setSizeX " << m_size_x << std::endl;
    }    
}

void Population::setSizeY(int y)
{
    if (y < 3 || y > 999) {
      fprintf(stderr, "Error: population y must be between 3 and 999\n");
      exit(EXIT_FAILURE);
    }
    if (m_generation_start == 0) {
        m_size_y = y;
        //std::cout << "setSizeY " << m_size_y << std::endl;
    }    
}
*/

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

/*
void Population::setGenerationDelay(int generationDelay)
{
    if (generationDelay < 0 || generationDelay > 999) {
      fprintf(stderr, "Error: generation delay must be between 0 and 999\n");
      exit(EXIT_FAILURE);
    }
    m_generation_delay = generationDelay;
}
*/

bool Population::attendre_generation()
{
    clock_t now = std::clock() / 1000;

    if (
        (m_generation_start == 0) || 
        (now - m_generation_start > m_generation_delay)
        ) {
        m_generation_start = now;
        return true;
    }

    return false;
}

void Population::evoluer()
{
    m_generation++;
    std::cout << "Evolution " << m_generation << std::endl;
}

void Population::initRandom(int random_alea)
{
    if (m_actuel != nullptr) {
        delete m_actuel;
    }
    m_actuel = new Grille(m_size_x, m_size_y);

    // Initialiser le générateur de nombre pseudo-aléatoires.
    srand( time( NULL ) );

    for ( int y = 0; y < m_size_y; y++ ) {
        for ( int x = 0; x < m_size_x; x++ ) {
            if ((rand() % 100) < random_alea) {
                m_actuel->xy(x, y) = 1;
            }
            else {
                m_actuel->xy(x, y) = 0;
            }                
        }
    }
    //Population::attendre_generation();
}

/*
void Population::dump()
{
    // Afficher le contenu initial
    std::cout << "Contenu initial du tableau :" << std::endl;
    for (int i = 0; i < m_size_y; ++i) {
        for (int j = 0; j < m_size_x; ++j) {
            std::cout << m_actuel->xy(j, i) << " ";
        }
        std::cout << std::endl;
    }
}
*/

/*
int cell_count( int y, int x )
{
    int nb_vivante =    cell_grid[y-1][x-1] +
                        cell_grid[y-1][x] +
                        cell_grid[y-1][x+1] +
                        cell_grid[y][x-1] +
                        cell_grid[y][x+1] +
                        cell_grid[y+1][x-1] +
                        cell_grid[y+1][x] +
                        cell_grid[y+1][x+1] ;
    return(nb_vivante);
}

void next_state()
{
    int nb_autour;

    for (int y=0; y < size_y; y++) {
        for (int x=0; x < size_x; x++) {
            // Compter le nombre de celulles vivantes autour
            nb_autour = cell_count(y, x);

            if (cell_grid[y][x] == 1) {
                // Si la celulle etait vivante
                if (nb_autour == 2 || nb_autour == 3) {
                    next_grid[y][x] = 1;
                } else {
                    next_grid[y][x] = 0;
                }
            } else {
                // Si la celulle etait morte
                if (nb_autour == 3) {
                    next_grid[y][x] = 1;
                } else {
                    next_grid[y][x] = 0;
                }
            }
        }
    }
}
*/

/*
void copy_grid()
{
    for (int y=0; y < size_y; y++) {
        for (int x=0; x < size_x; x++) {
            cell_grid[y][x] = next_grid[y][x];
        }
    }
}
*/
