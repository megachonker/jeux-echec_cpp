#pragma once
#include "echiquier.hh"
#include <string>

std::string couleur_to_str(Couleur ma_couleur);
class Jeu
{
    private:
        Couleur joueur;
        Echiquier mon_echiquier;
    public:
        void affiche();
        bool deplace(std::string const orig, std::string const dest);
        Couleur get_couleur();
        Jeu(/* args */);
        ~Jeu();
};