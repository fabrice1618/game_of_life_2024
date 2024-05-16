#pragma once

#include <chrono>
#include <thread>

class Clepsydre {
private:
    // Délai en millisecondes
    std::chrono::milliseconds m_delai;
    // Temps de démarrage du timer
    std::chrono::time_point<std::chrono::system_clock> m_debut;

public:
    // Constructeur avec délai
    Clepsydre(const int &delai);
    // Vérifier si le délai est dépassé et relancer le timer
    bool check();
};
