#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <ctime>
#include <getopt.h>

#include "InitError.h"

// Options des options de la ligne de commande
#define HELP_OPTION          'h'
#define SIZE_X_OPTION        'x'
#define SIZE_Y_OPTION        'y'
#define CELL_ZONE_OPTION     'z'
#define CELL_SIZE_OPTION     's'
#define CELL_COLOR_R_OPTION  'r'
#define CELL_COLOR_G_OPTION  'g'
#define CELL_COLOR_B_OPTION  'b'
#define RANDOM_MAX_OPTION    'm'
#define RANDOM_LIFE_OPTION   'l'
#define CYCLE_DELAY_OPTION   'd'

// Valeurs par défaut des parametres
#define SIZE_X 100
#define SIZE_Y 50

#define CELL_ZONE 10
#define CELL_SIZE 8

/*
#define CELL_COLOR_R 255
#define CELL_COLOR_G 192
#define CELL_COLOR_B 203
*/
#define CELL_COLOR_R 18
#define CELL_COLOR_G 14
#define CELL_COLOR_B 252

#define RANDOM_MAX 25
#define RANDOM_LIFE 3

#define CYCLE_DELAY 500

enum game_state {
	GAME_PLAY,
	GAME_PAUSE,
	GAME_QUIT,
};

// Default values (can be overridden by command line arguments)
int size_x = SIZE_X;
int size_y = SIZE_Y;
int cell_zone = CELL_ZONE;
int cell_size = CELL_SIZE;
int cell_color_r = CELL_COLOR_R;
int cell_color_g = CELL_COLOR_G;
int cell_color_b = CELL_COLOR_B;
int random_max = RANDOM_MAX;
int random_life = RANDOM_LIFE;
int cycle_delay = CYCLE_DELAY; 

// Variables globales
char cell_grid[SIZE_Y][SIZE_X];
char next_grid[SIZE_Y][SIZE_X];


/*
Classe gérant l'affichage
*/

class SDL
{
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
public:
    SDL( Uint32 flags = 0 );
    virtual ~SDL();
    void draw();
};


SDL::SDL( Uint32 flags )
{
    int screen_w = size_x * cell_zone;
    int screen_h = size_y * cell_zone;

    if ( SDL_Init( flags ) != 0 )
        throw InitError();

    if ( SDL_CreateWindowAndRenderer( screen_w, screen_h, SDL_WINDOW_SHOWN,
                                      &m_window, &m_renderer ) != 0 )
        throw InitError();
}

SDL::~SDL()
{
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

void SDL::draw()
{
    SDL_Rect cell;
    int cell_gap = (cell_zone - cell_size) / 2;

    cell.w = cell_size;
    cell.h = cell_size;

    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );

    // Couleur des cellules
    SDL_SetRenderDrawColor( m_renderer, cell_color_r, cell_color_g, cell_color_b, 255 );

    // Dessiner la grille
    for ( int y = 0; y < size_y; y++ ) {
        for ( int x = 0; x < size_x; x++ ) {
            if (cell_grid[y][x] == 1) {
                cell.x = ( x * cell_zone ) + cell_gap;
                cell.y = ( y * cell_zone ) + cell_gap;

                SDL_RenderFillRect( m_renderer, &cell );
            }
        }
    }

    SDL_RenderPresent( m_renderer );
}


void grid_random()
{
    int alea;

    // On commence par initialiser le générateur de nombre pseudo-aléatoires.
    srand( time( NULL ) );

    for ( int y = 0; y < size_y; y++ ) {
        for ( int x = 0; x < size_x; x++ ) {
            alea = rand() % random_max;
            if (alea < random_life)
                cell_grid[y][x] = 1;
            else
                cell_grid[y][x] = 0;
        }
    }
}

int convert_x(int x)
{
    if (x<0) {
        x = x + SIZE_X;
    } else {
        x = x % SIZE_X;
    }

    return(x);
}

int convert_y(int y)
{
    if (y<0) {
        y = y + size_y;
    } else {
        y = y % size_y;
    }

    return(y);
}

int cell_count( int y, int x )
{
    int nb_vivante =    cell_grid[convert_y(y-1)][convert_x(x-1)] +
                        cell_grid[convert_y(y-1)][convert_x(x)] +
                        cell_grid[convert_y(y-1)][convert_x(x+1)] +
                        cell_grid[convert_y(y)][convert_x(x-1)] +
                        cell_grid[convert_y(y)][convert_x(x+1)] +
                        cell_grid[convert_y(y+1)][convert_x(x-1)] +
                        cell_grid[convert_y(y+1)][convert_x(x)] +
                        cell_grid[convert_y(y+1)][convert_x(x+1)] ;
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

void copy_grid()
{
    for (int y=0; y < size_y; y++) {
        for (int x=0; x < size_x; x++) {
            cell_grid[y][x] = next_grid[y][x];
        }
    }

}

int game_loop()
{
    SDL_Event evenements;
    enum game_state state = GAME_PLAY;

    try
    {
        SDL sdl( SDL_INIT_VIDEO | SDL_INIT_TIMER );
        grid_random();

        while (state != GAME_QUIT) {
        	// Fermeture de la fenetre
            while ( (state != GAME_QUIT) && SDL_PollEvent(&evenements) ) {
                if ((evenements.type==SDL_WINDOWEVENT) && (evenements.window.event == SDL_WINDOWEVENT_CLOSE))
                    state = GAME_QUIT;
            }

            if (state != GAME_QUIT) {
                sdl.draw();
                next_state();
                copy_grid();
                SDL_Delay( cycle_delay );
            }

        }

        return EXIT_SUCCESS;
    }
    catch ( const InitError & err )
    {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
    }

    return EXIT_FAILURE;
}

int main(int argc, char* argv[]) {
  int c;
  while ((c = getopt(argc, argv, "hx:y:z:s:r:g:b:m:l:d:")) != -1) {
    switch (c) {
      case HELP_OPTION:
        // Print help message
        printf("Usage: %s [options]\n", argv[0]);
        printf("-h\t\tShow this help message\n");
        printf("-x <value>\tSet grid width (default: %d)\n", SIZE_X);
        printf("-y <value>\tSet grid height (default: %d)\n", SIZE_Y);
        printf("-z <value>\tSet cell zone (default: %d)\n", CELL_ZONE);
        printf("-s <value>\tSet cell size (default: %d)\n", CELL_SIZE);
        printf("-r <value>\tSet cell color red (default: %d)\n", CELL_COLOR_R);
        printf("-g <value>\tSet cell color green (default: %d)\n", CELL_COLOR_G);
        printf("-b <value>\tSet cell color blue (default: %d)\n", CELL_COLOR_B);
        printf("-m <value>\tSet random spawn probability max (default: %d)\n", RANDOM_MAX);
        printf("-l <value>\tSet initial life value for cells (default: %d)\n", RANDOM_LIFE);
        printf("-d <value>\tSet cycle delay in milliseconds (default: %d)\n", CYCLE_DELAY);
        return 0;
      case SIZE_X_OPTION:
        size_x = atoi(optarg);
        break;
      case SIZE_Y_OPTION:
        size_y = atoi(optarg);
        break;
      case CELL_ZONE_OPTION:
        cell_zone = atoi(optarg);
        break;
      case CELL_SIZE_OPTION:
        cell_size = atoi(optarg);
        break;
      case CELL_COLOR_R_OPTION:
        cell_color_r = atoi(optarg);
        if (cell_color_r < 0 || cell_color_r > 255) {
          fprintf(stderr, "Error: cell color red must be between 0 and 255\n");
          return 1;
        }
        break;
      case CELL_COLOR_G_OPTION:
        cell_color_g = atoi(optarg);
        if (cell_color_g < 0 || cell_color_g > 255) {
          fprintf(stderr, "Error: cell color green must be between 0 and 255\n");
          return 1;
        }
        break;
      case CELL_COLOR_B_OPTION:
        cell_color_b = atoi(optarg);
        if (cell_color_b < 0 || cell_color_b > 255) {
          fprintf(stderr, "Error: cell color blue must be between 0 and 255\n");
          return 1;
        }
        break;
      case RANDOM_MAX_OPTION:
        random_max = atoi(optarg);
        if (random_max < 2 || random_max > 100) {
          fprintf(stderr, "Error: random max must be between 2 and 100\n");
          return 1;
        }
        break;
      case RANDOM_LIFE_OPTION:
        random_life = atoi(optarg);
        if (random_life < 0 || random_life > 99) {
          fprintf(stderr, "Error: random life must be between 0 and 99\n");
          return 1;
        }
        break;
      case CYCLE_DELAY_OPTION:
        cycle_delay = atoi(optarg);
        if (cycle_delay < 0 || cycle_delay > 500) {
          fprintf(stderr, "Error: cycle delay must be between 0 and 500\n");
          return 1;
        }
        break;

    }
  }

  game_loop();
}