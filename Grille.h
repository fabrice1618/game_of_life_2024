#pragma once

#include <iostream>
#include <vector>

class Grille {
private:
    std::vector<int> m_data;
    int m_size_x;
    int m_size_y;

public:
    // Constructeur
    Grille(int size_x, int size_y);

    // Méthode pour accéder et modifier les éléments du tableau
    int& xy(int x, int y);

    // Affichage de la grille
    void debug();    
};


