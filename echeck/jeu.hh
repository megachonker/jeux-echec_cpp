#pragma once
#include "echiquier.hh"
#include "piece.hh"
#include "square.hh"
#include <string>

std::string couleur_to_str(Couleur ma_couleur);
class Jeu
{
    private:        
        Couleur joueur;
        Echiquier mon_echiquier;
        int check(mouvement);
        void errorhande(int errono);
    public:
        void affiche();
        bool deplace(std::string const orig, std::string const dest);
        Couleur get_couleur();
        Jeu(/* args */);
        ~Jeu();
};

struct mouvement
{
    Piece * piece;
    Square position_dst;
    bool &deplacement_aggressif;
    Couleur couleur;
};

enum erreurJeuCheck{
    OK,
    mauvaisecouleur,
    deplacement_sois_meme,
    checkdsterr
};