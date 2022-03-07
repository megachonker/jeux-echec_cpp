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


bool Pion::deplace(Square dst){
    int distance = dst.ligne-position.ligne;
    if (couleur==Noir)
        distance*=-1;

    cout << "distance "<<distance << endl;
    if (distance <= 0)
    {
        //deplacement_null
        return false;
    }
    
    if((purity==true && dst.ligne-position.ligne<=2)||(dst.ligne-position.ligne<=1)){
        return true;
    }
    return false;
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

Couleur Piece::get_couleur(){
    return couleur;
}

