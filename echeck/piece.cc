#include "piece.hh"
#include <iostream>
#include <string>
#include "square.hh"
using namespace std;

Square Piece::get_pos(){
    return position;
}

Piece::Piece(std::string nom, Couleur couleur,Square position): nom(nom),couleur(couleur),position(position)
{
    //incrémenter l'id de la piece ?
}

Pion::Pion(Couleur couleur,Square position) : Piece(nom = couleur==Blanc ? "\u2659" :"\u265F",couleur,position)
{
    to_string();
}

void Pion::deplace(Square dst){
    
}

string Piece::to_string() const{
return  "uid:"+std::to_string(uid)+"\n"+
        "couleur:"+std::to_string(couleur)+"\n"+
        "noms:"+nom+"\n"+
        "position: "+ position.to_string();
}

void Piece::affiche() const{
    cout << nom ;   
}

