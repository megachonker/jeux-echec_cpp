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


bool Pion::deplace(Square dst){
    int distance = dst.ligne-position.ligne;
    if (couleur==Noir)
        distance*=-1;

    cout << "distance "<<distance << endl;
    if (distance <= 0)
    {
        cout << "deplacement_null" << endl;
        return false;
    }
    
    if((vierge==true && dst.ligne-position.ligne<=2)||(dst.ligne-position.ligne<=1)){
        cout << "déplacement imposible" << endl;
        return true;
    }
    return false;
}
Pion::Pion(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2659" :"\u265F",couleur,position),vierge(vierge)
{cout << to_string()<< endl;}


string Pion::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge:    "+(vierge==true?"Oui":"Non");
}

Couleur Piece::get_couleur(){
    return couleur;
}

Pion::~Pion(){
    cout << "destructeur de pion" << endl;
    // delete this;
}