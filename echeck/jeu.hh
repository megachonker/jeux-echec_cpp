#pragma once
// #include "piece.hh"
#include "echiquier.hh"
#include <string>
using namespace std;

enum {blanc, noir};

class Jeu
{
    private:
        bool joueur;
        Echiquier mon_echiquier;
    public:
        void affiche();
        bool deplace(string JSP, string const orig, string const dest);

        Jeu(/* args */);
        // ~Jeu();
};