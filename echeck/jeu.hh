#pragma once
// #include "piece.hh"
#include "echiquier.hh"
#include <string>

enum {blanc, noir};

class Jeu
{
    private:
        bool joueur;
        Echiquier mon_echiquier;
    public:
        void affiche();
        bool deplace(std::string JSP, std::string const orig, std::string const dest);

        Jeu(/* args */);
        // ~Jeu();
};