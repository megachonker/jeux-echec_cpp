#include "piece.hh"
#include <iostream>
#include <string>
using namespace std;


Piece::Piece(std::string nom, bool couleur): nom(nom),couleur(couleur)
{
    //incrémenter l'id de la piece ?
}

Pion::Pion(bool couleur) : Piece(couleur ? "\u2659" :"\u265F",couleur)
{
}

string Piece::to_string() const{
return  "uid:"+std::to_string(uid)+"\n"+
        "couleur:"+std::to_string(couleur)+"\n"+
        "noms:"+nom+"\n"+
        "position: "+ position.to_string();
}

void Piece::affiche() const{
    cout << nom << endl;   
}

