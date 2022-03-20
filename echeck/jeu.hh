#pragma once
#include "echiquier.hh"
#include "piece.hh"
#include "square.hh"
#include <string>

class Jeu
{
    private:
        bool resolut;
        bool cache_resolution; 
        bool en_echeque;
        Couleur joueur;
        Echiquier mon_echiquier;
        int check(struct mouvement);
        void errorhande(int errono);
    public:
        void explain(enum erreurDeplacement errono);
        bool fin();
        void affiche();
        bool deplace(std::string const orig, std::string const dest);
        Couleur get_couleur();
        Jeu(/* args */);
        ~Jeu();
};