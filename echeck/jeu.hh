#pragma once
// #include "piece.hh"
#include <string>
using namespace std;

enum {blanc, noir};

class Jeu
{
private:
    bool joueur;
public:
    void affiche();
    bool deplace(string JSP, string const orig, string const dest);

    Jeu(/* args */);
    // ~Jeu();
};