#include <getopt.h>
#include <cstdio>
#include <stdexcept>

#include "Config.h"

Config::Config(int argc, char *argv[])
{
    int c;

    while ((c = getopt(argc, argv, "hx:y:d:a:r:g:b:")) != -1)
    {
        switch (c) {
        case HELP_OPTION:
            // Print help message
            print_usage(argv[0]);
            exit(EXIT_SUCCESS);
        case SIZE_X_OPTION:
            m_size_x = atoi(optarg);
            if (m_size_x < 3 || m_size_x > 999) {
                throw std::out_of_range("Error: population size must be between 3 and 999");
            }
            break;
        case SIZE_Y_OPTION:
            m_size_y = atoi(optarg);
            if (m_size_y < 3 || m_size_y > 999) {
                throw std::out_of_range("Error: population size must be between 3 and 999");
            }
            break;
        case GENERATION_DELAY_OPTION:
            m_generation_delay = atoi(optarg);
            if (m_generation_delay < 0 || m_generation_delay > 999) {
                throw std::out_of_range("Error: generation delay must be between 0 and 999");
            }
            break;
        case RANDOM_ALEA_OPTION:
            m_random_alea = atoi(optarg);
            if (m_random_alea < 2 || m_random_alea > 100) {
                throw std::out_of_range("Error: random alea must be between 2 and 100");
            }
            break;
        case CELL_COLOR_R_OPTION:
            m_cell_color_r = atoi(optarg);
            if (m_cell_color_r < 0 || m_cell_color_r > 255) {
                throw std::out_of_range("Error: cell color must be between 0 and 255");
            }
            break;
        case CELL_COLOR_G_OPTION:
            m_cell_color_g = atoi(optarg);
            if (m_cell_color_g < 0 || m_cell_color_g > 255) {
                throw std::out_of_range("Error: cell color must be between 0 and 255");
            }
            break;
        case CELL_COLOR_B_OPTION:
            m_cell_color_b = atoi(optarg);
            if (m_cell_color_b < 0 || m_cell_color_b > 255) {
                throw std::out_of_range("Error: cell color must be between 0 and 255");
            }
            break;
        }
    }
}


void print_usage(char* executable)
{
    printf("Usage: %s [options]\n", executable);
    printf("-h\t\tShow this help message\n");
    printf("-x <value>\tSet population x (default: %d)\n", SIZE_X);
    printf("-y <value>\tSet population y (default: %d)\n", SIZE_Y);
    printf("-d <value>\tSet generation delay in milliseconds (default: %d)\n", GENERATION_DELAY);
    printf("-a <value>\tSet aléatoire vivante probability max (default: %d)\n", RANDOM_ALEA);
    printf("-r <value>\tSet cell color red (default: %d)\n", CELL_COLOR_R);
    printf("-g <value>\tSet cell color green (default: %d)\n", CELL_COLOR_G);
    printf("-b <value>\tSet cell color blue (default: %d)\n", CELL_COLOR_B);
}
