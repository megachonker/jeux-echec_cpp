#include "piece.hh"
#include <iostream>
#include <string>
#include "square.hh"
using namespace std;

Square Piece::get_pos(){
    return position;
}

Piece::Piece(std::string nom, Couleur couleur,Square position): nom(nom),couleur(couleur),position(position){}

bool Piece::deplace(Square dst){
    //le déplacement est possible ?
    if (check_dst(dst)==true)
    {
        //metre a jour
        cout << "old pose: " << position.to_string() << " newpos: " << dst.to_string() << endl;
        position=dst;
        return true;
    }
    return false;
}

string Piece::to_string() const{    
return  string("\n")+
        "noms:      "+nom+"\n"+
        "position:  "+ position.to_string()+"\n"+
        "couleur:   "+(couleur==Blanc?"Blanc":"Noir");
}

void Piece::affiche() const{
    cout << nom ;   
}
Couleur Piece::get_couleur(){
    return couleur;
}


//////////////
//  PION    //
//////////////

Pion::Pion(Couleur couleur,Square position,bool vierge) : Piece(couleur==Blanc ? "\u2659" :"\u265F",couleur,position),vierge(vierge)
{cout << to_string()<< endl;}

bool Pion::mangerdiag(Square dst) const{
    //bon ?
    if(dst.to_string()==Square(position.ligne+1,dst.colone+(couleur==Noir ? -1: 1)).to_string()
    || dst.to_string()==Square(position.ligne-1,dst.colone+(couleur==Noir ? -1: 1)).to_string())
        return true;
    return false;
}


bool Pion::check_dst(Square dst) const {
    // return true;
    int distance = dst.ligne-position.ligne;

    if (couleur==Noir)
        distance*=-1;

    //check si le pion avance
    if (distance <= 0)
    {
        cout << "check_dstment_null" << endl;
        return false;
    }

    if((vierge==true && distance<=2)||(distance<=1)||mangerdiag(dst)){
        return true;
    }
    
    cout << "déplacement imposible" << endl;
    return false;
}

string Pion::to_string() const{    
return  Piece::to_string()+"\n"+
        "vierge:    "+(vierge==true?"Oui":"Non");
}

//////////////
//  Tour    //
//////////////

Tour::Tour(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2656" :"\u265C",couleur,position){}

bool Tour::check_dst(Square dst) const  {

    //jeu verifie que la src est destination ne sont pas les meme
    if(position.colone == dst.colone){
        return true;
    }
    else if (position.ligne == dst.ligne)
    {
        return true;
    }
    return false;
}

//////////////
//  Fout    //
//////////////
 
Fou::Fou(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2657" :"\u265D",couleur,position){}

bool Fou::check_dst(Square dst) const {
    //check ratio de déplacement a 1
    if(((dst.colone-position.colone)/(dst.ligne-position.ligne))==1){
        return true;
    }
    return false;
}

//////////////////
//  Cavalier    //
//////////////////
 
Cavalier::Cavalier(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2658" :"\u265E",couleur,position){}

bool Cavalier::check_dst(Square dst) const {
    return
    Square(position.ligne+2,position.colone+1) == dst ||
    Square(position.ligne+2,position.colone-1) == dst ||
    Square(position.ligne-2,position.colone+1) == dst ||
    Square(position.ligne-2,position.colone-1) == dst ||
    Square(position.colone+2,position.ligne+1) == dst ||
    Square(position.colone+2,position.ligne-1) == dst ||
    Square(position.colone-2,position.ligne+1) == dst ||
    Square(position.colone-2,position.ligne-1) == dst;
}

//////////////
//  Dame    //
//////////////
 
Dame::Dame(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2655" :"\u265B",couleur,position){}

bool Dame::check_dst(Square dst) const {
    Fou F(couleur,position);
    Tour T(couleur,position);

    return  F.check_dst(dst)
        ||  T.check_dst(dst);
}

/////////////
//  Roi    //
/////////////

Roi::Roi(Couleur couleur,Square position) : Piece(couleur==Blanc ? "\u2654" :"\u265A",couleur,position){}

bool Roi::check_dst(Square dst) const {
    return
        Square(position.ligne+1,position.colone+1) == dst ||
        Square(position.ligne+1,position.colone-1) == dst ||
        Square(position.ligne-1,position.colone+1) == dst ||
        Square(position.ligne-1,position.colone-1) == dst;
}