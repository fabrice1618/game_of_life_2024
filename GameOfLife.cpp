#include <SDL2/SDL.h>

#include "GameOfLife.h"

GameOfLife::GameOfLife(Config config, Population* population)
{
    m_population = population;
    m_cell_color_r = config.getCellColorR();
    m_cell_color_g = config.getCellColorG();
    m_cell_color_b = config.getCellColorB();

    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 )
        throw InitSDLException();

    // Création de la fenêtre
    m_window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_X, WINDOW_Y, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        throw InitSDLException();
    }

    // Création du renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        throw InitSDLException();
    }

    // pointeur gestionnaire clavier
    m_keystate = SDL_GetKeyboardState(NULL);

    m_state = GAME_PLAY;
}

GameOfLife::~GameOfLife()
{
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

enum game_state GameOfLife::getState()
{
    return m_state;
}

void GameOfLife::clearScreen()
{
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );
}

void GameOfLife::draw()
{
    SDL_Rect cell;

    //std::cout << "Draw window " << WINDOW_X << ", " << WINDOW_Y << std::endl;
    //std::cout << "Population " << m_population->getSizeX() << ", " << m_population->getSizeY() << std::endl;
    int cell_x = WINDOW_X / m_population->getSizeX();
    int cell_y = WINDOW_Y / m_population->getSizeY();
    int cell_zone = std::min(cell_x, cell_y);
    //std::cout << "Cell zone " << cell_x << ", " << cell_y << ": " << cell_zone << std::endl;
    int cell_padding = 0;
    if (cell_zone > 2) {
        cell_padding = 1;
    }
    //std::cout << "Cell padding " << cell_padding << std::endl;

    cell.w = cell_zone - cell_padding;
    cell.h = cell_zone - cell_padding;

    // Couleur des cellules
    SDL_SetRenderDrawColor( m_renderer, m_cell_color_r, m_cell_color_g, m_cell_color_b, 255 );

    // Dessiner la grille
    for ( int y = 0; y < m_population->getSizeY(); y++ ) {
        for ( int x = 0; x < m_population->getSizeX(); x++ ) {
            int val = m_population->getXY(x, y);
            //std::cout << "draw " << x << ", " << y << "= " << val;
            if (m_population->getXY(x, y) == 1) {
                cell.x = ( x * cell_zone ) + cell_padding;
                cell.y = ( y * cell_zone ) + cell_padding;
                //std::cout << " cell " << cell.x << ", " << cell.y;
                //std::cout << " w,h " << cell.w << ", " << cell.h;

                SDL_RenderFillRect( m_renderer, &cell );
            }
             //std::cout << std::endl;
        }
    }

    SDL_RenderPresent( m_renderer );
}


void GameOfLife::traiter_evenements()
{
    SDL_Event evenements;

    // Fermeture de la fenetre
    while ( SDL_PollEvent(&evenements) ) {
        if ((evenements.type==SDL_WINDOWEVENT) && (evenements.window.event == SDL_WINDOWEVENT_CLOSE)) {
            m_state = GAME_QUIT;
            break;
        }

        if (m_keystate[SDL_SCANCODE_ESCAPE]) {
            m_state = GAME_QUIT;
        }

    }
}