#pragma once
// #include "piece.hh"
#include "echiquier.hh"
#include <string>

enum {blanc, noir};

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