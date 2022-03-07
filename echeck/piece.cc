#include "piece.hh"
#include <iostream>
#include <string>
#include "square.hh"
using namespace std;

Square Piece::get_pos(){
    return position;
}

Piece::Piece(std::string nom, Couleur couleur,Square position): nom(nom),couleur(couleur),position(position){}

string Piece::to_string() const{    
return  string("\n")+
        "noms:      "+nom+"\n"+
        "position:  "+ position.to_string()+"\n"+
        "couleur:   "+(couleur==Blanc?"Blanc":"Noir");
}

void Piece::affiche() const{
    cout << nom ;   
}

Pion::Pion(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2659" :"\u265F",couleur,position),vierge(vierge)
{cout << to_string()<< endl;}

void Pion::deplace(Square dst){}


string Pion::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge:    "+(vierge==true?"Oui":"Non");
}
