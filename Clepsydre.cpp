#include "Clepsydre.h"

Clepsydre::Clepsydre(const int &delai)
{
    m_delai = (std::chrono::milliseconds)delai;
    m_debut = std::chrono::system_clock::now();
}

bool Clepsydre::check()
{
    std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_debut);
    if (elapsed >= m_delai)
    {
        m_debut = std::chrono::system_clock::now(); // Relancer le timer
        return true;
    }
    return false;
}
