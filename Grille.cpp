#include <iostream>
#include <vector>
#include "Grille.h"

// Constructeur
Grille::Grille(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {
    // Initialisation du tableau avec des valeurs à 0
    m_data.resize(m_size_x * m_size_y, 0);
}

// Méthode pour accéder et modifier les éléments du tableau
int& Grille::xy(int x, int y) {
    return m_data[x * m_size_y + y];
}

// Affichage de la grille
void Grille::debug()
{
    std::cout << "Dimensions : " << m_size_x << ", " << m_size_y << std::endl;
    std::cout << "Contenu :" << std::endl;
    for (int y = 0; y < m_size_y; y++) {
        for (int x = 0; x < m_size_x; x++) {
            std::cout << xy(x, y) << " ";
        }
        std::cout << std::endl;
    }
}

