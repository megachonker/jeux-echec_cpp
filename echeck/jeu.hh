#pragma once
#include "echiquier.hh"
#include <string>
// #include "square.hh" // import enum

class Jeu
{
    private:
        Couleur joueur;
        Echiquier mon_echiquier;
    public:
        void affiche();
        bool deplace(std::string const orig, std::string const dest);

        Jeu(/* args */);
        // ~Jeu();
};