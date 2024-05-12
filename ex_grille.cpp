// Exemple utilisation Grille
#include "Grille.h"

int main() 
{
    Grille grille(3, 10);   // Créer un tableau 2D

    grille.debug();

    grille.xy(0, 2) = 2;
    grille.debug();

    Grille* grille2 = new Grille(3, 3);
    for (int y=0; y < 3; y++) {
        for (int x=0; x < 3; x++) {
            grille2->xy(x, y) = x * y;
        }
    }
    grille2->debug();
    delete grille2;

    return 0;
}