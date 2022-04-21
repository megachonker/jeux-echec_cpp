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
        int     numero_tour;
        Square  deplacement[55][2];
        int check(struct mouvement);
        void errorhande(int errono);
        void end_turn();
        bool is_pat();
    public:
        erreurDeplacement rock(bool grand);
        void explain(enum erreurDeplacement errono);
        bool fin();
        void affiche();
        bool deplace(std::string const orig, std::string const dest);
        Couleur get_couleur();
        Jeu(/* args */);
        ~Jeu();
};