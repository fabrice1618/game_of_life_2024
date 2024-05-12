#pragma once
#include <SDL2/SDL.h>

#include "InitSDLException.h"
#include "Population.h"
#include "Config.h"

#define WINDOW_X 800
#define WINDOW_Y 600

enum game_state {
    GAME_INIT,
	GAME_PLAY,
	GAME_QUIT,
};

class GameOfLife
{
    private:
        SDL_Window*   m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        const Uint8*  m_keystate = nullptr;
        enum game_state m_state = GAME_INIT;
        int m_cell_color_r;
        int m_cell_color_g;
        int m_cell_color_b;
        Population* m_population;
    public:
        GameOfLife(Config config, Population* population);
        virtual ~GameOfLife();
        void clearScreen();
        void draw();
        void traiter_evenements();
        enum game_state getState();
};
